#!/usr/bin/env bash

max_elf_cals=0
current_elf_cals=0


while read -r cal
do
  if [[ -z $cal ]]
  then
    if [[ $current_elf_cals -gt $max_elf_cals ]]
    then
      max_elf_cals=$current_elf_cals
    fi
    current_elf_cals=0
  else
    ((current_elf_cals+=cal))
  fi
done < input.txt

echo $max_elf_cals
