#!/bin/bash

gcc send.c -o send
gcc receive.c -o receive
./send
./receive

good=`cat plik | aspell -d pl -a | tail -n +2 |grep '^*' |wc -l`
if [ $good = 1 ]
then
	echo "Wyraz poprawny po polsku"
else
	echo "Wyraz niepoprawny"
fi

rm plik
