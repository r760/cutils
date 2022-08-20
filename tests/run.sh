#!/bin/bash

cleanup()
{
    rm -f tmp.*
}

green_font()
{
    tput setaf 2
}

yellow_font()
{
    tput setaf 3
}

red_font()
{
    tput setaf 1
}

reset_font()
{
    tput sgr0
}

run_test()
{
    yellow_font
    echo "=== === === === ==="
    echo "|  Testing ${1} |"
    echo "=== === === === ==="
    reset_font

    for test in $(ls ${1}/in);
    do
	case $2 in
	    "--check-memory-leaks")
		valgrind --track-origins=yes --leak-check=full ${BINDIR}/${1}_cli < ${1}/in/${test} > tmp.${test}
		;;
	    *)
		${BINDIR}/${1}_cli < ${1}/in/${test} > tmp.${test}
		;;
	esac
	TEST_RES=$(diff tmp.${test} ${1}/expected/${test})

	if [[ ${TEST_RES} == "" ]]; then
	    echo -en " - ${test} "
	    green_font
	    echo "Passed"
	else
	    echo -en " - ${test} "
	    red_font
	    echo "Failed"
	    echo "${TEST_RES}"
	fi
	reset_font
    done
    echo
}

BINDIR=../bin
run_test darray $1
run_test sllist $1
run_test stack $1
run_test queue $1
cleanup
