#!/bin/bash

source secret.profile


for file in $@; do 
    for sub in "${!SUBS[@]}"; do
        sed -e "s/{$sub}/${SUBS[$sub]}/" $file > tmp
        mv tmp $file
    done
done