#!/bin/bash
source subs.profile

echo "$$" > daemon.pid

while true; do
./t1.sh *.txt
sleep 10
done