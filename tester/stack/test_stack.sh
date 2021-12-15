#! /bin/bash

RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
HONEY="\e[38;5;214m"
BOLD="\033[1m"
RESET="\033[0m"

echo
printf $HONEY
printf	"     _____ _______       _____ _  __\n"
printf	"    / ____|__   __|/\   / ____| |/ /\n"
printf	"   | (___    | |  /  \ | |    | ' / \n"
printf	"    \___ \   | | / /\ \| |    |  <  \n"
printf	"    ____) |  | |/ ____ \ |____| . \ \n"
printf	"   |_____/   |_/_/    \_\_____|_|\_\\n"$RED
echo
echo


# compile vector with ft::vector
clang++ -Wall -Wextra -Werror -g -std=c++98 stack.cpp -D NAMESPACE=ft -D FT=1 -o stack.ft.out
if [[ $? != 0 ]]
then
    printf $RED"compilation error stack.ft.out\n"$RESET
    exit 1
fi

# compile vector with std::vector
clang++ -Wall -Wextra -Werror -g -std=c++98 stack.cpp -D NAMESPACE=std -D FT=0 -o stack.std.out
if [[ $? != 0 ]]
then
    printf $RED"compilation error stack.std.out\n"$RESET
    exit 1
fi
printf $YELLOW"running main.ft.out...\n"$RESET
if [[ $1 = "-v" ]]
then
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.out ./stack.ft.out;
	tail 9 valgrind.out
else
    START_TIME=$(perl -MTime::HiRes -e 'printf("%.0f\n",Time::HiRes::time()*1000)')
    ./stack.ft.out
    END_TIME=$(perl -MTime::HiRes -e 'printf("%.0f\n",Time::HiRes::time()*1000)')
    echo "elapsed time ft: $(($END_TIME - $START_TIME)) ms"
fi

# run main.std.out and save output to main.std.output
printf $YELLOW"running main.std.out...\n"$RESET
START_TIME=$(perl -MTime::HiRes -e 'printf("%.0f\n",Time::HiRes::time()*1000)')
./stack.std.out
END_TIME=$(perl -MTime::HiRes -e 'printf("%.0f\n",Time::HiRes::time()*1000)')
echo "elapsed time std: $(($END_TIME - $START_TIME)) ms"

diff --text output.ft.out output.std.out > diff.out
if [[ $? = 0 ]]
then
    printf $GREEN"no differences found\n"$RESET
    # cat output.ft.out
else
    printf $YELLOW"differences found:\n"$RESET
    printf $YELLOW"------------------\n"$RESET
    cat -e diff.out
fi

echo
read -r -p "Do you want to remove out files ? [y/N] " response
if [[ "$response" =~ ^([yY][eE][sS]|[yY])$ ]]
then
	rm -rf *.dSYM *.out
fi
clear
echo