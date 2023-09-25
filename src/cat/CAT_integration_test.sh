#!/bin/bash

BLUE='\033[34m'  # Код для синего цвета
RESET='\033[0m'  # Код для сброса цвета
YELLOW='\033[33m' # Код для желтого цвета
GREEN='\033[32m'  # Код для зеленого цвета
RED='\033[31m'  # Код для красного цвета

echo -e "Мы находимся в директории:"
pwd

echo -e "\nСодержимое директории:"
ls -l
 

echo -e "\nЧтобы запустить проверку, перечислите имена файлов (для завершения ввода введите 'q'):"

txt_names=()

while read -r txt_name && [[ "$txt_name" != 'q' ]]; do
    txt_names+=("$txt_name")
done

echo -e "\n${BLUE}Результат утилиты \"cat\" с без флага в терминале:${RESET}"

files=$(printf "%s " "${txt_names[@]}")
cat_result=$(cat $files)
echo "$cat_result"

echo -e "\n${YELLOW}Результат выполнения программы без флага:${RESET}"

program_result=$(./s21_cat $files)
echo "$program_result"

if [[ "$cat_result" == "$program_result" ]]; then
    echo -e "\nCOMPARE RESULT: ${GREEN}OK${RESET}"
else
    echo -e "\nCOMPARE RESULT: ${RED}FAIL${RESET}"
fi
echo -e "\n================================================================================"

echo -e "\n${BLUE}Результат утилиты \"cat\" с флагом -b в терминале:${RESET}"

files=$(printf "%s " "${txt_names[@]}")
cat_result=$(cat -b $files)
echo "$cat_result"

echo -e "\n${YELLOW}Результат выполнения программы с флагом -b :${RESET}"

program_result=$(./s21_cat -b $files)
echo "$program_result"

if [[ "$cat_result" == "$program_result" ]]; then
    echo -e "\nCOMPARE RESULT: ${GREEN}OK${RESET}"
else
    echo -e "\nCOMPARE RESULT: ${RED}FAIL${RESET}"
fi
echo -e "\n================================================================================"

echo -e "\n${BLUE}Результат утилиты \"cat\" с флагом -E в терминале:${RESET}"

files=$(printf "%s " "${txt_names[@]}")
cat_result=$(cat -E $files)
echo "$cat_result"

echo -e "\n${YELLOW}Результат выполнения программы с флагом -E:${RESET}"

program_result=$(./s21_cat -E $files)
echo "$program_result"

if [[ "$cat_result" == "$program_result" ]]; then
    echo -e "\nCOMPARE RESULT: ${GREEN}OK${RESET}"
else
    echo -e "\nCOMPARE RESULT: ${RED}FAIL${RESET}"
fi
echo -e "\n================================================================================"

echo -e "\n${BLUE}Результат утилиты \"cat\" с флагом -e в терминале:${RESET}"

files=$(printf "%s " "${txt_names[@]}")
cat_result=$(cat -e $files)
echo "$cat_result"

echo -e "\n${YELLOW}Результат выполнения программы с флагом -e :${RESET}"

program_result=$(./s21_cat -e $files)
echo "$program_result"

if [[ "$cat_result" == "$program_result" ]]; then
    echo -e "\nCOMPARE RESULT: ${GREEN}OK${RESET}"
else
    echo -e "\nCOMPARE RESULT: ${RED}FAIL${RESET}"
fi
echo -e "\n================================================================================"



echo -e "\n${BLUE}Результат утилиты \"cat\" с флагом -n в терминале:${RESET}"

files=$(printf "%s " "${txt_names[@]}")
cat_result=$(cat -n $files)
echo "$cat_result"

echo -e "\n${YELLOW}Результат выполнения программы с флагом -n :${RESET}"

program_result=$(./s21_cat -n $files)
echo "$program_result"

if [[ "$cat_result" == "$program_result" ]]; then
    echo -e "\nCOMPARE RESULT: ${GREEN}OK${RESET}"
else
    echo -e "\nCOMPARE RESULT: ${RED}FAIL${RESET}"
fi
echo -e "\n================================================================================"



echo -e "\n${BLUE}Результат утилиты \"cat\" с флагом -s в терминале:${RESET}"

files=$(printf "%s " "${txt_names[@]}")
cat_result=$(cat -s $files)
echo "$cat_result"

echo -e "\n${YELLOW}Результат выполнения программы с флагом -s :${RESET}"

program_result=$(./s21_cat -s $files)
echo "$program_result"

if [[ "$cat_result" == "$program_result" ]]; then
    echo -e "\nCOMPARE RESULT: ${GREEN}OK${RESET}"
else
    echo -e "\nCOMPARE RESULT: ${RED}FAIL${RESET}"
fi
echo -e "\n================================================================================"


echo -e "\n${BLUE}Результат утилиты \"cat\" с флагом -t в терминале:${RESET}"

files=$(printf "%s " "${txt_names[@]}")
cat_result=$(cat -t $files)
echo "$cat_result"

echo -e "\n${YELLOW}Результат выполнения программы с флагом -t :${RESET}"

program_result=$(./s21_cat -t $files)
echo "$program_result"

if [[ "$cat_result" == "$program_result" ]]; then
    echo -e "\nCOMPARE RESULT: ${GREEN}OK${RESET}"
else
    echo -e "\nCOMPARE RESULT: ${RED}FAIL${RESET}"
fi
echo -e "\n================================================================================"

echo -e "\n${BLUE}Результат утилиты \"cat\" с флагом -T в терминале:${RESET}"

files=$(printf "%s " "${txt_names[@]}")
cat_result=$(cat -t $files)
echo "$cat_result"

echo -e "\n${YELLOW}Результат выполнения программы с флагом -T :${RESET}"

program_result=$(./s21_cat -t $files)
echo "$program_result"

if [[ "$cat_result" == "$program_result" ]]; then
    echo -e "\nCOMPARE RESULT: ${GREEN}OK${RESET}"
else
    echo -e "\nCOMPARE RESULT: ${RED}FAIL${RESET}"
fi
echo -e "\n================================================================================"


echo -e "\n${BLUE}Результат утилиты \"cat\" с флагом -v в терминале:${RESET}"

files=$(printf "%s " "${txt_names[@]}")
cat_result=$(cat -v $files)
echo "$cat_result"

echo -e "\n${YELLOW}Результат выполнения программы с флагом -v :${RESET}"

program_result=$(./s21_cat -v $files)
echo "$program_result"

if [[ "$cat_result" == "$program_result" ]]; then
    echo -e "\nCOMPARE RESULT: ${GREEN}OK${RESET}"
else
    echo -e "\nCOMPARE RESULT: ${RED}FAIL${RESET}"
fi
echo -e "\n================================================================================"

number-nonblank


echo -e "\n${BLUE}Результат утилиты \"cat\" с флагом --number-nonblank в терминале:${RESET}"

files=$(printf "%s " "${txt_names[@]}")
cat_result=$(cat --number-nonblank $files)
echo "$cat_result"

echo -e "\n${YELLOW}Результат выполнения программы с флагом --number-nonblank :${RESET}"

program_result=$(./s21_cat --number-nonblank $files)
echo "$program_result"

if [[ "$cat_result" == "$program_result" ]]; then
    echo -e "\nCOMPARE RESULT: ${GREEN}OK${RESET}"
else
    echo -e "\nCOMPARE RESULT: ${RED}FAIL${RESET}"
fi
echo -e "\n================================================================================"


echo -e "\n${BLUE}Результат утилиты \"cat\" с флагом --number в терминале:${RESET}"

files=$(printf "%s " "${txt_names[@]}")
cat_result=$(cat --number $files)
echo "$cat_result"

echo -e "\n${YELLOW}Результат выполнения программы с флагом --number :${RESET}"

program_result=$(./s21_cat --number $files)
echo "$program_result"

if [[ "$cat_result" == "$program_result" ]]; then
    echo -e "\nCOMPARE RESULT: ${GREEN}OK${RESET}"
else
    echo -e "\nCOMPARE RESULT: ${RED}FAIL${RESET}"
fi
echo -e "\n================================================================================"


echo -e "\n${BLUE}Результат утилиты \"cat\" с флагом --squeeze-blank в терминале:${RESET}"

files=$(printf "%s " "${txt_names[@]}")
cat_result=$(cat --squeeze-blank $files)
echo "$cat_result"

echo -e "\n${YELLOW}Результат выполнения программы с флагом --squeeze-blank :${RESET}"

program_result=$(./s21_cat --squeeze-blank $files)
echo "$program_result"

if [[ "$cat_result" == "$program_result" ]]; then
    echo -e "\nCOMPARE RESULT: ${GREEN}OK${RESET}"
else
    echo -e "\nCOMPARE RESULT: ${RED}FAIL${RESET}"
fi
echo -e "\n================================================================================"
