#!/bin/bash

TMP_OUTPUT="test"
TIMEOUT_T=5
LOG="/dev/null"
NUM_TASKS="$(ls -l | grep "^d" | wc -l)"

function print_task_header {
    echo "======== Task $1 ========"
}

function print_total {
    echo "TOTAL: $1"
}

function print_status {
    echo "Test$1..................$2"
}

function verify_test {
    TEST_NR="$1"
    TEST_INPUT_PATH="$INPUT_DIR/test$TEST_NR.in"
    TEST_OUTPUT_PATH="$OUTPUT_DIR/test$TEST_NR.ref"

    timeout $TIMEOUT_T $PROGRAM < "$TEST_INPUT_PATH" > "$TMP_OUTPUT"
    diff "$TEST_OUTPUT_PATH" "$TMP_OUTPUT" &> "$LOG"

    if [ $? -eq 0 ]; then
        print_status $TEST_NR "PASSED"
        TOTAL=$((TOTAL + $INC))
    else
        print_status $TEST_NR "FAILED"
    fi

    rm "$TMP_OUTPUT"
}

function verify_task {
    TOTAL=0
    INPUT_DIR="./$1/input"
    OUTPUT_DIR="./$1/output"
    PROGRAM="./task$1"
    NUM_TESTS="$(ls -1 $INPUT_DIR/ | wc -l)"
    INC="$((100 / $NUM_TESTS))"

    print_task_header $1

    for nr in $(seq 0 $((NUM_TESTS - 1))); do
        verify_test "$nr"
    done

    print_total $TOTAL
}

make

for task in $(seq 1 $NUM_TASKS); do
    verify_task $task
done

make clean
