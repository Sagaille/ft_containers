#! /bin/bash

RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
HONEY="\e[38;5;214m"
BOLD="\033[1m"
RESET="\033[0m"

echo
printf $HONEY
printf   "__      ________ _____ _______ ____  _____  \n"
printf   "\ \    / /  ____/ ____|__   __/ __ \|  __ \ \n"
printf   " \ \  / /| |__ | |       | | | |  | | |__) |\n"
printf   "  \ \/ / |  __|| |       | | | |  | |  _  / \n"
printf   "   \  /  | |___| |____   | | | |__| | | \ \ \n"
printf   "    \/   |______\_____|  |_|  \____/|_|  \_\\n"$RESET

echo
echo



# compile vector with ft::vector
clang++ -Wall -Wextra -Werror -g -std=c++98 vector.cpp -D NAMESPACE=ft -D FT=1 -o vector.ft.out
if [[ $? != 0 ]]
then
    printf $RED"compilation error vector.ft.out\n"$RESET
    exit 1
fi

# compile vector with std::vector
clang++ -Wall -Wextra -Werror -g -std=c++98 vector.cpp -D NAMESPACE=std -D FT=0 -o vector.std.out
if [[ $? != 0 ]]
then
    printf $RED"compilation error vector.std.out\n"$RESET
    exit 1
fi

# run vector.ft.out and save output to vector.ft.output
printf $YELLOW"running vector.ft.out...\n"$RESET
if [[ $1 = "-v" ]]
then
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.out ./vector.ft.out
	tail -9 valgrind.out
else
    START_TIME=$(perl -MTime::HiRes -e 'printf("%.0f\n",Time::HiRes::time()*1000)')
    ./vector.ft.out
    END_TIME=$(perl -MTime::HiRes -e 'printf("%.0f\n",Time::HiRes::time()*1000)')
    echo "elapsed time ft: $(($END_TIME - $START_TIME)) ms"
fi

# run vector.std.out and save output to vector.std.output
printf $YELLOW"running vector.std.out...\n"$RESET
START_TIME=$(perl -MTime::HiRes -e 'printf("%.0f\n",Time::HiRes::time()*1000)')
./vector.std.out
END_TIME=$(perl -MTime::HiRes -e 'printf("%.0f\n",Time::HiRes::time()*1000)')
echo "elapsed time std: $(($END_TIME - $START_TIME)) ms"

# # compare ft::vector output to std::vector output
printf $YELLOW"comparing ft::vector to std::vector output...\n\n"$RESET
diff --text output.ft.out output.std.out > diff.out
if [[ $? = 0 ]]
then
    printf $GREEN"no differences found\n"$RESET
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