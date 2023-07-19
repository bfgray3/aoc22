#!/usr/bin/env bash

set -eu

make -s clean

function test_part {
  local day part input_file correct_answer f

  day=$1
  part=$2

  input_file="./$day/input.txt"

  if [[ ! -d "$day/$part" ]]
  then
    return
  fi

  correct_answer=$(jq -r ".ans$day.$part" answers.json)

  for f in "$day/$part"/*
  do
    test_one "$f" "$correct_answer"
  done
}

function test_one {
  local f correct_answer extension ans
  # TODO: make input_file local too

  f=$1
  correct_answer=$2

  #echo "****f: $f"

  extension="${f##*.}"

  case $extension in
    cpp)
      make -s path="$f"  # TODO: clean this up to take just the directory so we don't need day and part
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
      echo "UNKNOWN FILE: $f" >&2
      return
      ;;
  esac

  if [[ "$ans" = "$correct_answer" ]]
  then
    # FIXME: d/p not available anymore
    echo "day $d part $p correct: $extension"
  else
    # FIXME: d/p not available anymore
    echo "day $d part $p incorrect: $extension; got $ans and expected $correct_answer" >&2
    exit 1
  fi
}


if [[ $# -eq 1 ]]
then
  test_one file answer
elif [[ $# -eq 0 ]]
then
  for d in [0-9]*
  do
    for p in a b
    do
      test_part "$d" "$p"
    done
  done
else
  echo "Usage: ./test.sh [dd{a,b}]" >&2
  exit 1
fi
