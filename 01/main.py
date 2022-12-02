with open("input.txt") as f:
    cals = [l.strip() for l in f]

max_elf_cals = current_elf_cals = 0

for cal in cals:
    if cal == "":
        if current_elf_cals > max_elf_cals:
            max_elf_cals = current_elf_cals
        current_elf_cals = 0
    else:
        current_elf_cals += int(cal)

print(max_elf_cals)
