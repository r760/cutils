#!/bin/bash

cleanup()
{
    rm -f tmp.*
}

run_test()
{
    tput setaf 3
    echo "=== === === === ==="
    echo "|  Testing ${1} |"
    echo "=== === === === ==="
    tput sgr0

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
            tput setaf 2
            echo "Passed"
        else
            echo -en " - ${test} "
            tput setaf 1
            echo "Failed"
            echo "${TEST_RES}"
        fi
        tput sgr0
    done
    echo
}

BINDIR=../bin
run_test darray $1
run_test sllist $1
run_test stack $1
run_test queue $1
cleanup
