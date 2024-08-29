#!/bin/bash

scp cat/s21_cat turkeysndc@192.168.1.57:/usr/local/bin
# Проверка на наличие ошибок при копировании
if [ $? -ne 0 ]; then
	    echo "Ошибка при копировании файлов"
	        exit 1
fi
scp grep/s21_grep turkeysndc@192.168.1.57:/usr/local/bin
# Проверка на наличие ошибок при копировании
if [ $? -ne 0 ]; then
	    echo "Ошибка при копировании файлов"
	        exit 1
fi

ssh turkeysndc@192.168.1.57 ls -lah /usr/local/bin

# Проверка на наличие ошибок при перемещении
if [ $? -ne 0 ]; then
	    echo "Ошибка при перемещении файлов"
	        exit 1
fi

# Сообщение об успешной операции
echo "Файлы успешно скопированы/перемещены"

