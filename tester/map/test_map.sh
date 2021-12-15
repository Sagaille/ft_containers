#! /bin/bash

RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
HONEY="\e[38;5;214m"
BOLD="\033[1m"
RESET="\033[0m"
echo
printf $HONEY
printf			" __  __          _____  \n"
printf 			"|  \/  |   /\   |  __ \ \n"
printf 			"| \  / |  /  \  | |__) |\n"
printf 			"| |\/| | / /\ \ |  ___/ \n"
printf 			"| |  | |/ ____ \| |     \n"
printf 			"|_|  |_/_/    \_\_|	\n"$RESET
echo
echo
# compile map with ft::map
clang++ -Wall -Wextra -Werror -g -std=c++98 map.cpp -D NAMESPACE=ft -D FT=1 -o map.ft.out
if [[ $? != 0 ]]
then
    printf $RED"compilation error map.ft.out\n"$RESET
    exit 1
fi

# compile map with std::map
clang++ -Wall -Wextra -Werror -g -std=c++98 map.cpp -D NAMESPACE=std -D FT=0 -o map.std.out
if [[ $? != 0 ]]
then
    printf $RED"compilation error map.std.out\n"$RESET
    exit 1
fi

# run map.ft.out and save output to map.ft.output
printf $YELLOW"running map.ft.out...\n"$RESET
if [[ $1 = "-v" ]]
then
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.out ./map.ft.out
	tail -9 valgrind.out
else
    START_TIME=$(perl -MTime::HiRes -e 'printf("%.0f\n",Time::HiRes::time()*1000)')
    ./map.ft.out
    END_TIME=$(perl -MTime::HiRes -e 'printf("%.0f\n",Time::HiRes::time()*1000)')
    echo "elapsed time ft: $(($END_TIME - $START_TIME)) ms"
fi

# run map.std.out and save output to map.std.output
printf $YELLOW"running map.std.out...\n"$RESET
START_TIME=$(perl -MTime::HiRes -e 'printf("%.0f\n",Time::HiRes::time()*1000)')
./map.std.out
END_TIME=$(perl -MTime::HiRes -e 'printf("%.0f\n",Time::HiRes::time()*1000)')
echo "elapsed time std: $(($END_TIME - $START_TIME)) ms"

# compare ft::map output to std::map output
printf $YELLOW"comparing ft::map to std::map output...\n\n"$RESET
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