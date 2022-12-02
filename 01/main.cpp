#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  std::size_t max_elf_cals{}, current_elf_cals{}, cal_num;
  std::ifstream input_file_stream{"input.txt"};
  std::string cal;

  while (std::getline(input_file_stream, cal)) {
    if (cal == "") {
      if (current_elf_cals > max_elf_cals) {
        max_elf_cals = current_elf_cals;
      }
      current_elf_cals = 0;
    } else {
      std::stringstream cal_stream{cal};
      cal_stream >> cal_num;
      current_elf_cals += cal_num;
    }
  }

  std::cout << max_elf_cals << '\n';
}
