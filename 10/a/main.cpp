#include <fstream>
#include <iostream>
#include <set>
#include <string>

#include "utils.h"

static const std::string ADDX{"addx"};
static const std::set<int> cycles{20, 60, 100, 140, 180, 220};

int main(const int, const char** argv) {
  int prev_add_instr{}, sum_signal_strength{}, x{1}, cycle_num{};
  std::string instr;
  std::ifstream input_file_stream{argv[1]};
  bool prev_instr_was_add{};
  const auto max_cycles = *std::max_element(std::cbegin(cycles), std::cend(cycles));

  while (cycle_num < max_cycles) {
    ++cycle_num;

    if (cycles.contains(cycle_num)) {
      sum_signal_strength += cycle_num * x;
    }

    if (prev_instr_was_add) {
      x += prev_add_instr;
      prev_instr_was_add = false;
      continue;
    }
    std::getline(input_file_stream, instr);

    prev_instr_was_add = instr.starts_with(ADDX);

    if (prev_instr_was_add) {
      prev_add_instr = std::stoi(instr.substr(instr.find(" ") + 1, std::string::npos));
    }
  }

  std::cout << sum_signal_strength << '\n';
}
