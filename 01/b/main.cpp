#include <charconv>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <string>

static constexpr std::size_t NUM_TOP_ELVES{3};

int main(const int, const char** argv) {
  std::size_t current_elf_cals{}, cal_num{}, tot{};
  std::ifstream input_file_stream{argv[1]};
  std::string cal;
  std::priority_queue<std::size_t, std::vector<std::size_t>, std::greater<std::size_t>> topn;

  while (std::getline(input_file_stream, cal)) {
    if (cal.empty()) {
      if (topn.size() < NUM_TOP_ELVES) {
        topn.push(current_elf_cals);
      } else if (topn.top() < current_elf_cals) {
        topn.pop();
        topn.push(current_elf_cals);
      }
      current_elf_cals = 0;
    } else {
      std::from_chars(cal.data(), cal.data() + cal.size(), cal_num);
      current_elf_cals += cal_num;
    }
  }

  while (!topn.empty()) {
    tot += topn.top();
    topn.pop();
  }

  std::cout << tot << '\n';
}
