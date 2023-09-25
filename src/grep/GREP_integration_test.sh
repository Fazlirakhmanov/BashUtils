#!/bin/bash

BLUE='\033[34m'  # Код для синего цвета
RESET='\033[0m'  # Код для сброса цвета
YELLOW='\033[33m' # Код для желтого цвета
GREEN='\033[32m'  # Код для зеленого цвета
RED='\033[31m'  # Код для красного цвета

SUCCESS=0
FAIL=0
COUNTER=0
DIFF=""

my_grep=(
    "./s21_grep"
    )
original_grep=(
    "grep"
    )

flags=(
    "v"
    "c"
    "l"
    "n"
    "h"
    "o"
)

tests=(
"s test_files/test4.txt FLAGS"
"int s21_grep.c s21_grep.h Makefile FLAGS"
"-e for s21_grep.c FLAGS"
"s21_grep.c Makefile FLAGS -f test_files/test0_patternfile.txt"
)

manual=(
"-n somepattern test_files/test1.txt"
"-n if test_files/test1.txt test_files/test2.txt"
"-c -e /\ test_files/test1.txt"
"-n -e \} test_files/test1.txt"
"-ce int test_files/test1.txt test_files/test2.txt"
"-e int test_files/test1.txt"
"-nivh = test_files/test1.txt test_files/test2.txt"
"-e"
"-ie INT test_files/test4.txt"
"-echar test_files/test1.txt test_files/test2.txt"
"-ne = -e out test_files/test4.txt"
"-iv int test_files/test4.txt"
"-in int test_files/test4.txt"
"-c -l aboba test_files/test1.txt test_files/test4.txt"
"-v test_files/test1.txt -e ank"
"-noe ) test_files/test4.txt"
"-l for test_files/test1.txt test_files/test2.txt"
"-o -e void test_files/test3.txt"
"-e = -e out test_files/test4.txt"
"-noe ing -e as -e the -e not -e is test_files/test5.txt"
"-e ing -e as -e the -e not -e is test_files/test5.txt"
"-l for no_file.txt test_files/test2.txt"
"-e int -si no_file.txt s21_grep.c no_file2.txt s21_grep.h"
"-f test_files/test_3_grep.txt test_files/test4.txt"
"-si s21_grep.c -f non_existing.txt"

)

run_test() {
    param=$(echo "$@" | sed "s/FLAGS/$var/")
    "${my_grep[@]}" $param > "${my_grep[@]}".log
    "${original_grep[@]}" $param > "${original_grep[@]}".log
    DIFF="$(diff -s "${my_grep[@]}".log "${original_grep[@]}".log)"
    let "COUNTER++"
    if [ "$DIFF" == "Files "${my_grep[@]}".log and "${original_grep[@]}".log are identical" ]
    then
        let "SUCCESS++"
        echo -e "$COUNTER ${GREEN}OK${RESET}: $my_grep $param"
    else
        let "FAIL++"
        echo -e "$COUNTER ${RED}FAIL${RESET}: $my_grep $param"
    fi
    rm -f "${my_grep[@]}".log "${original_grep[@]}".log
}

echo "====================================================================="
echo "Manual test"
echo "====================================================================="
printf "\n"

for i in "${manual[@]}"
do
    var="-"
    run_test "$i"
done

printf "\n"
echo "====================================================================="
echo "Autotest: 1 flag"
echo "====================================================================="
printf "\n"

for var1 in "${flags[@]}"
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        run_test "$i"
    done
done
printf "\n"
echo "====================================================================="
echo "Autotest: 2 flags - separated"
echo "====================================================================="
printf "\n"

for var1 in "${flags[@]}"
do
    for var2 in "${flags[@]}"
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1 -$var2"
                run_test "$i"
            done
        fi
    done
done
printf "\n"
echo "====================================================================="
echo "Autotest: 3 flags - separated"
echo "====================================================================="
printf "\n"
for var1 in "${flags[@]}"
do
    for var2 in "${flags[@]}"
    do
        for var3 in "${flags[@]}"
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${tests[@]}"
                do
                    var="-$var1 -$var2 -$var3"
                    run_test "$i"
                done
            fi
        done
    done
done
printf "\n"
echo "====================================================================="
echo "Autotest: 4 flags - separated"
echo "====================================================================="
printf "\n"
for var1 in "${flags[@]}"
do
    for var2 in "${flags[@]}"
    do
        for var3 in "${flags[@]}"
        do
            for var4 in "${flags[@]}"
            do
                if [ $var1 != $var2 ] && [ $var2 != $var3 ] \
                && [ $var1 != $var3 ] && [ $var1 != $var4 ] \
                && [ $var2 != $var4 ] && [ $var3 != $var4 ]
                then
                    for i in "${tests[@]}"
                    do
                        var="-$var1 -$var2 -$var3 -$var4"
                        run_test "$i"
                    done
                fi
            done
        done
    done
done
printf "\n"
echo "====================================================================="
echo "Autotest: 2 flags - stucked"
echo "====================================================================="
printf "\n"

for var1 in "${flags[@]}"
do
    for var2 in "${flags[@]}"
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1$var2"
                run_test "$i"
            done
        fi
    done
done

printf "\n"
echo "====================================================================="
echo "Autotest: 3 flags - stucked"
echo "====================================================================="
printf "\n"

for var1 in "${flags[@]}"
do
    for var2 in "${flags[@]}"
    do
        for var3 in "${flags[@]}"
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${tests[@]}"
                do
                    var="-$var1$var2$var3"
                    run_test "$i"
                done
            fi
        done
    done
done
printf "\n"
echo "====================================================================="
echo "Autotest: 4 flags - stucked"
echo "====================================================================="
printf "\n"
for var1 in "${flags[@]}"
do
    for var2 in "${flags[@]}"
    do
        for var3 in "${flags[@]}"
        do
            for var4 in "${flags[@]}"
            do
                if [ $var1 != $var2 ] && [ $var2 != $var3 ] \
                && [ $var1 != $var3 ] && [ $var1 != $var4 ] \
                && [ $var2 != $var4 ] && [ $var3 != $var4 ]
                then
                    for i in "${tests[@]}"
                    do
                        var="-$var1$var2$var3$var4"
                        run_test "$i"
                    done
                fi
            done
        done
    done
done
printf "\n"
echo "FAIL: $FAIL"
echo "OK: $SUCCESS"
echo "TOTAL: $COUNTER"
printf "\n"
