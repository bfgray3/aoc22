#include <charconv>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

int main(const int, const char** argv) {
  std::size_t max_elf_cals{}, current_elf_cals{}, cal_num{};
  std::ifstream input_file_stream{argv[1]};
  std::string cal;

  while (std::getline(input_file_stream, cal)) {
    if (cal.empty()) {
      if (current_elf_cals > max_elf_cals) {
        max_elf_cals = current_elf_cals;
      }
      current_elf_cals = 0;
    } else {
      std::from_chars(cal.data(), cal.data() + cal.size(), cal_num);
      current_elf_cals += cal_num;
    }
  }

  std::cout << max_elf_cals << '\n';
}
