# Переменная для цели
TARGET = s21_cat
CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
LFLAGS=#-fsanitize=address -g

# Имена которые оканчиваются на .c, wildcar - все те файлы, которые удовлятворяют маске
SRC = $(wildcard *.c)
# Имена всех объектных файлов (*.o), так как они не существуют до компиляции, 
#мы подставим из имен с исходным кодом (.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
##############################################

all: clean $(TARGET)

# то что требуется получить target : то что необходимо чтобы получить то что слева
$(TARGET) : $(OBJ)
	$(CC) $(LFLAGS) $(FLAGS) $(OBJ) -o $(TARGET)


%.o : %.c
	$(CC) $(LFLAGS) $(FLAGS) -c $< -o $@
# $< подставляется то что справа от цели, то есть все обьектные
# $@ подставляется то что стоит в целе

style:
	clang-format -n *.c *.h

stylecor:
	clang-format -google-style -i *.c *.h

.PHONY: clean
# PHONY нужна чтобы указать что там не будет файла clean
clean : 
	rm -rf $(TARGET) *.o
	rm -rf CPPLINT.cfg
# удаляем MyProject и все файлы с .o
# Параметр ‘-f‘ в команде rm принудительно удаляет файлы независимо от их прав доступа,
# а также игнорирует несуществующие файлы.
# параметром ‘-r‘ рекурсивно удалит все файлы и подкаталогов в родительской директории.
test : $(TARGET)
	bash test_cat.sh

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h