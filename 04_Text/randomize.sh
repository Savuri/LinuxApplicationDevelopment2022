#!/bin/bash

sleep_time=0.01
if [ $# -ge 1 ]; then sleep_time=$1; fi

x=0
y=0
buf=()

while IFS= read -r line
do
    x=0
    while [ $x -lt ${#line} ]; 
    do
        buf+=("$y.$x.${line:x:1}")
        ((++x))
    done

    ((++y))
done

eof_y=$y
tput clear

for line in $(shuf -e "${buf[@]}")
do
    readarray -d "." -t carr <<< $line
    y=${carr[0]}
    x=${carr[1]}
    c=${carr[2]}

    tput cup $y $x
    echo -n $c

    if [ ! $c = ' ' ]; then
        sleep $sleep_time 
    fi;
done

tput cup $eof_y 0