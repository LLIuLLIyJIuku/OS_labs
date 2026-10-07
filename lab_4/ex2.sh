#!/bin/bash
gcc ex2.c -o ex2 || exit 1

for n in 3 5; do
    echo "===== n = $n ====="
    ./ex2 "$n" &
    pid=$!
    for i in $(seq 1 $((n + 1))); do
        echo "--- pstree after ~$(( (i - 1) * 5 + 1 ))s ---"
        sleep 1
        pstree -p "$pid"
        sleep 4
    done
    wait
done
