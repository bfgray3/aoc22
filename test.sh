#!/usr/bin/env bash

set -eu

make -s clean

for d in [0-9]*
do
  for p in a b
  do
    if [[ ! -d "$d/$p" ]]
    then
      continue
    fi
    for f in "$d/$p"/*
    do
      extension="${f##*.}"
      case $extension in
        cpp)
          make -s day="$d" part=$p
          ans=$("./$d/$p/aocmain" "./$d/input.txt")
          ;;
        py)
          ans=$(python3 "$f" "./$d/input.txt")
          ;;
        go)
          ans=$(go run "$f" "./$d/input.txt")
          ;;
        sh)
          ans=$(bash "$f" "./$d/input.txt")
          ;;
        R)
          ans=$(Rscript "$f" "./$d/input.txt")
          ;;
        *)
          echo "UNKNOWN FILE: $f"
          continue
          ;;
      esac
      if [[ $(jq -r ".ans$d.$p" answers.json) = "$ans" ]]
      then
        echo "day $d part $p correct: $extension"
      else
        echo "day $d part $p incorrect: $extension" >&2
        exit 1
      fi
    done
  done
done
