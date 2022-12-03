#include <cstddef>
#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

static constexpr std::size_t NUM_TOP_ELVES{3};

int main() {
  std::size_t max_elf_cals{}, current_elf_cals{}, cal_num, tot{};
  std::ifstream input_file_stream{"01/input.txt"};
  std::string cal;
  std::stringstream cal_stream;
  std::priority_queue<std::size_t, std::vector<std::size_t>, std::greater<std::size_t>> topn;

  while (std::getline(input_file_stream, cal)) {
    if (cal == "") {
      if (topn.size() < NUM_TOP_ELVES) {
        topn.push(current_elf_cals);
      } else if (topn.top() < current_elf_cals) {
        topn.pop();
        topn.push(current_elf_cals);
      }
      current_elf_cals = 0;
    } else {
      cal_stream << cal;
      cal_stream >> cal_num;
      cal_stream.clear();
      current_elf_cals += cal_num;
    }
  }

  while (!topn.empty()) {
    tot += topn.top();
    topn.pop();
  }

  std::cout << tot << '\n';
}
