#!/usr/bin/env bash

set -eu

make -s clean

for d in [0-9]*
do
  for p in a b
  do
    make -s day="$d" part=$p
    ans=$("./$d/$p/aocmain" "./$d/input.txt")
    if [[ $(jq -r ".ans$d.$p" answers.json) = "$ans" ]]
    then
      echo "day $d part $p correct"
    else
      echo "day $d part $p incorrect" >&2
      exit 1
    fi
  done
done
