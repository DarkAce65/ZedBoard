#!/bin/sh
./CombineFiles.sh tmp.txt $1 $2

wc tmp.txt

rm tmp.txt
