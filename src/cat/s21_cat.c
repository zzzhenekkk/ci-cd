// "Copyright 2023 Evgeniy Zlygostev"

#include "s21_cat.h"

int main(int argc, char **argv) {
  static flag flag;
  if (argc == 1) {
    cat_no_arg();
  } else {
    init_flags(&flag);
    check_flags(argc, argv, &flag);
    print(argc, argv, &flag);
  }
  return 0;
}

// если нет аргументов, то просто считываем с ввода, как в баш кат
void cat_no_arg() {
  char buf[4096];
  int fd = 2;
  int bytes_read = read(fd, buf, 4096);
  while (bytes_read > 0) {
    printf("%.*s", bytes_read, buf);
    bytes_read = read(fd, buf, 4096);
  }
}

void init_flags(flag *flag) {
  flag->n = 0;
  flag->s = 0;
  flag->e = 0;
  flag->b = 0;
  flag->T = 0;
  flag->t = 0;
  flag->v = 0;
}

struct option flags[] = {{"number-nonblank", no_argument, 0, 'b'},  // -b
                         {"E", no_argument, 0, 'E'},                // -E
                         {"e", no_argument, 0, 'e'},                // -e
                         {"number", no_argument, 0, 'n'},           // -n
                         {"squeeze-blank", no_argument, 0, 's'},    // -s
                         {"T", no_argument, 0, 'T'},                // -T
                         {"t", no_argument, 0, 't'},                // -t
                         {"v", no_argument, 0, 'v'},                // -v
                         {0, 0, 0, 0}};

void check_flags(int argc, char **argv, flag *flag) {
  int res = 0;
  opterr = 0;
  while ((res = getopt_long(argc, argv, "+beEnstTv", flags, 0)) != -1) {
    switch (res) {
      case 'b':
        flag->b = 1;  // Нумерует непустые строки
        break;
      case 'n':
        flag->n = 1;  // Нумерует все строки
        break;
      case 'E':
        flag->e = 1;  // Показывает символы конца строки
        break;
      case 'e':
        flag->e = 1;  // также отображает символы конца строки как $
        flag->v = 1;  // Показывает непечатаемые символы
        break;
      case 's':
        flag->s = 1;  // Сжимает несколько смежных пустых строк
        break;
      case 'v':
        flag->v = 1;  // Показывает непечатаемые символы кроме табуляции и конца
                      // строки
        break;
      case 't':
        flag->t = 1;  // Показывает непечатаемые символы плюс символ табуляции
        flag->v = 1;
        break;
      case 'T':
        flag->t = 1;  // Показывает символ табуляции
        break;
      case '?':
        dprintf(2, "%s: illegal option -- %s\n", argv[0] + 2,
                *((argv[optind - 1]) + 1) == '-' ? ((argv[optind - 1]) + 2)
                                                 : ((argv[optind - 1]) + 1));
        dprintf(2, "usage: %s [-belnstuv] [file ...]\n", argv[0] + 2);
        exit(1);
    }
  }
}

void print(int argc, char *argv[], const flag *flag) {
  int c = 0;

  for (int i = optind; i < argc;
       i++) {  // optind это указатель на на индекс в argv
    int empty_lines;
    int lines;
    int is_new_line;
    lines = 1;        // считает количество строк
    is_new_line = 1;  // начало строки
    empty_lines = 0;  // пустые строки
    FILE *file = fopen(argv[i], "r");
    if (file == NULL) {
      dprintf(2, "s21_cat: %s: No such file or directory\n", argv[i]);
      continue;
    }
    while ((c = fgetc(file)) != EOF) {
      // сжимает несколько смежных пустых строк
      if (flag->s) {  // -s
        if (c == '\n') {
          ++empty_lines;
          if (empty_lines > 2) {
            continue;
          }
        } else {
          empty_lines = 0;
        }
      }

      // нумерует все выходные строки
      if (flag->n && is_new_line && !flag->b) {
        printf("%6d\t", lines);
        ++lines;
        is_new_line = 0;
      }

      // нумерует только непустые строки
      if (flag->b && is_new_line && c != '\n') {
        printf("%6d\t", lines);
        ++lines;
        is_new_line = 0;
      }

      // отображает символы конца строки как $ плюс костыль для -b -e
      if (flag->e && c == '\n') {
        printf("$");
      }

      // отображает табы как ^I
      if (flag->t && c == '\t') {
        printf("^");
        c = 'I';
      }

      // Отображает непечатаемые символы в виде видимых символов,
      // за исключением табуляйций, новых строк.
      // Управляющие символы ASCII (восьмеричные 000-037 (0-31)) печатаются как
      // ^n, где n - соответствующий символ ASCII в восьмеричном диапазоне
      // 100-137
      //(@, A, B, C,..., X, Y, Z, [, \, ], ^ и _);
      // символ DEL 127 (восьмеричный 0177) печатается как ^?.
      if (flag->v && c != '\n' && c != '\t') {
        if (c >= 0 && c <= 31) {
          printf("^");
          c += 64;
        } else if (c == 127) {
          // Del = ^? ? = 63
          printf("^");
          c -= 64;
        }
      }

      if (c == '\n') is_new_line = 1;
      printf("%c", c);
    }
    fclose(file);
  }
}
