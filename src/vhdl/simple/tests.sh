#!/bin/sh

./test.sh coverage coverage.gpeg coverage.txt
./test.sh json json.gpeg json.txt
./test.sh complexjson json.gpeg complexjson.txt
