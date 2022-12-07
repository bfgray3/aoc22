cals <- readLines("../input.txt")

max_elf_cals <- current_elf_cals <- 0L

for (cal in cals) {
  if (identical(cal, "")) {
    if (current_elf_cals > max_elf_cals) {
      max_elf_cals <- current_elf_cals
    }
      current_elf_cals <- 0L
  } else {
    current_elf_cals <- current_elf_cals + as.integer(cal)
  }
}

cat(max_elf_cals, "\n")
