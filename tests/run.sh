#!/bin/bash

cleanup()
{
    rm -f tmp.*
}

test_darray()
{
    echo "=== === === === ==="
    echo "|  Testing darray |"
    echo "=== === === === ==="

    for test in $(ls darray/in);
    do
        case $1 in 
            "--check-memory-leaks")
                valgrind --track-origins=yes --leak-check=full ${BINDIR}/darray_cli < darray/in/${test} > tmp.${test}
                ;;
            *)
                ${BINDIR}/darray_cli < darray/in/${test} > tmp.${test}
                ;;
        esac
        TEST_RES=$(diff tmp.${test} darray/expected/${test})

        if [[ ${TEST_RES} == "" ]]; then
            echo -e " - ${test} Passed"
        else
            echo -e " - ${test} Failed"
            echo "${TEST_RES}"
        fi
    done
}

BINDIR=../bin
test_darray $1
cleanup
