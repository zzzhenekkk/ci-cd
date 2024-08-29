#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_
#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 8192

typedef struct {
  int e;  // For regex
  int i;  // Ignores case
  int v;  // Inverts result of searching
  int c;  // Number of lines where searching string is found
  int l;  // Number of files where searching string is found
  int n;  // Line number in the output of the searched string
  int h;  // Doesn't show files where searching string is found
  int s;  // Doesn't show messages about files that weren't found or couldn't be
          // read
  int f;  // Gets regular expressions from file (needs arguments)
  int o;  // Shows only searched string without full line

  long long int string_count;
  int match_lines_count;
  int match_files_count;
  int empty_lines;
  int file_s;
  int e_count;

  char search_expres[BUFFSIZE];
} flagss;

// void init_options(flagss * flag);
void check_flags(int argc, char **argv, flagss *flag);
void open_file(int argc, char **argv, flagss *flag);
void flag_e(flagss *flag);
void flag_f(char *argv[], flagss *flag);
void search_and_print(char *argv[], FILE *file, flagss *flag, int optindi);
void is_it_files(int argc, char **argv, flagss *flag);
extern int optind, opterr, optopt;

#endif  // SRC_GREP_S21_GREP_H_
