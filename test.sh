#!/usr/bin/env bash

set -eu

make -s clean

for d in [0-9]*
do
  input_file="./$d/input.txt"
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
          ans=$("./$d/$p/aocmain" "$input_file")
          ;;
        py)
          ans=$(python3 "$f" "$input_file")
          ;;
        go)
          ans=$(go run "$f" "$input_file")
          ;;
        sh)
          ans=$(bash "$f" "$input_file")
          ;;
        R)
          ans=$(Rscript "$f" "$input_file")
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
