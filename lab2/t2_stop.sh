#!/bin/bash

sleep(40)
kill -SIGTERM $(cat daemon.pid)