#!/usr/bin/env bash

set -eu

# TODO: get arguments for which days/parts to run

make -s clean

function test_one {
  local f=$1
  local correct_answer=$2
  echo 'this is f'
  echo $f


  local extension="${f##*.}"

  case $extension in
    cpp)
      #make -s day="$d" part=$p
      #local ans=$("./$d/$p/aocmain" "$input_file")
      return
      ;;
    py)
      local ans=$(python3 "$f" "$input_file")
      ;;
    go)
      local ans=$(/usr/local/go/bin/go run "$f" "$input_file")  # TODO: cleanup which executable
      ;;
    sh)
      local ans=$(bash "$f" "$input_file")
      ;;
    R)
      local ans=$(Rscript "$f" "$input_file")
      ;;
    *)
      echo "UNKNOWN FILE: $f"
      continue
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
      test_one "$f" "$correct_answer"
    done
  done
done
