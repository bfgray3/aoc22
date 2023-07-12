#!/usr/bin/env bash

set -eu

# TODO: get arguments for which days/parts to run

make -s clean

function test_one {
  local f correct_answer day part extension ans

  f=$1
  correct_answer=$2
  day=$3
  part=$4

  extension="${f##*.}"

  case $extension in
    cpp)
      make -s day="$day" part="$part"
      ans=$("./$d/$p/aocmain" "$input_file")
      ;;
    py)
      ans=$(python3 "$f" "$input_file")
      ;;
    go)
      ans=$(/usr/local/go/bin/go run "$f" "$input_file")  # TODO: cleanup which executable
      ;;
    sh)
      ans=$(bash "$f" "$input_file")
      ;;
    R)
      ans=$(Rscript "$f" "$input_file")
      ;;
    *)
      echo "UNKNOWN FILE: $f"
      return
      ;;
  esac

  if [[ "$ans" = "$correct_answer" ]]
  then
    echo "day $d part $p correct: $extension"
  else
    echo "day $d part $p incorrect: $extension; got $ans and expected $correct_answer" >&2
    exit 1
  fi
}


for d in [0-9]*
do
  input_file="./$d/input.txt"
  for p in a b
  do
    if [[ ! -d "$d/$p" ]]
    then
      continue
    fi
    correct_answer=$(jq -r ".ans$d.$p" answers.json)
    for f in "$d/$p"/*
    do
      test_one "$f" "$correct_answer" "$d" "$p"
    done
  done
done
