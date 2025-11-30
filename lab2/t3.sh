#!/bin/bash

while IFS= read -r line; do
    echo "$line" > tmp1
    ./t1.sh tmp1
    cat tmp1
    rm tmp1
done