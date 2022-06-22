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

test_sllist()
{
    echo "=== === === === ==="
    echo "|  Testing sllist |"
    echo "=== === === === ==="

    for test in $(ls sllist/in);
    do
        case $1 in
            "--check-memory-leaks")
                valgrind --track-origins=yes --leak-check=full ${BINDIR}/sllist_cli < sllist/in/${test} > tmp.${test}
                ;;
            *)
                ${BINDIR}/sllist_cli < sllist/in/${test} > tmp.${test}
                ;;
        esac
        TEST_RES=$(diff tmp.${test} sllist/expected/${test})

        if [[ ${TEST_RES} == "" ]]; then
            echo -e " - ${test} Passed"
        else
            echo -e " - ${test} Failed"
            echo "${TEST_RES}"
        fi
    done
}

test_stack()
{
    echo "=== === === === ==="
    echo "|  Testing stack  |"
    echo "=== === === === ==="

    for test in $(ls stack/in);
    do
        case $1 in
            "--check-memory-leaks")
                valgrind --track-origins=yes --leak-check=full ${BINDIR}/stack_cli < stack/in/${test} > tmp.${test}
                ;;
            *)
                ${BINDIR}/stack_cli < stack/in/${test} > tmp.${test}
                ;;
        esac
        TEST_RES=$(diff tmp.${test} stack/expected/${test})

        if [[ ${TEST_RES} == "" ]]; then
            echo -e " - ${test} Passed"
        else
            echo -e " - ${test} Failed"
            echo "${TEST_RES}"
        fi
    done
}

test_queue()
{
    echo "=== === === === ==="
    echo "|  Testing queue  |"
    echo "=== === === === ==="

    for test in $(ls queue/in);
    do
        case $1 in
            "--check-memory-leaks")
                valgrind --track-origins=yes --leak-check=full ${BINDIR}/queue_cli < queue/in/${test} > tmp.${test}
                ;;
            *)
                ${BINDIR}/queue_cli < queue/in/${test} > tmp.${test}
                ;;
        esac
        TEST_RES=$(diff tmp.${test} queue/expected/${test})

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
echo
test_sllist $1
echo
test_stack $1
echo
test_queue $1
cleanup
