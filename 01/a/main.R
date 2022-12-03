cals <- readLines("input.txt")

max_elf_cals <- current_elf_cals <- 0

for (cal in cals) {
  if (identical(cal, "")) {
    if (current_elf_cals > max_elf_cals) {
      max_elf_cals <- current_elf_cals
    }
      current_elf_cals <- 0
  } else {
    current_elf_cals <- current_elf_cals + as.integer(cal)
  }
}

print(max_elf_cals)
