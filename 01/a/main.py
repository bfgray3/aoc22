import sys

with open(sys.argv[1]) as f:
    cals = [line.strip() for line in f]

max_elf_cals = current_elf_cals = 0

for cal in cals:
    if cal == "":
        if current_elf_cals > max_elf_cals:
            max_elf_cals = current_elf_cals
        current_elf_cals = 0
    else:
        current_elf_cals += int(cal)

print(max_elf_cals)
