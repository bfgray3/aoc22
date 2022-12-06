#include <charconv>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <regex>
#include <stack>
#include <string>
#include <vector>

int main() {
  std::size_t num_stacks;
  std::ifstream input_file_stream{"input.txt"};
  std::string row;
  std::vector<std::string> stack_rows, move_rows;

  while (std::getline(input_file_stream, row)) {
    if (row.empty()) {
      break;
    }
    stack_rows.push_back(row);
  }

  while (std::getline(input_file_stream, row)) {
    move_rows.push_back(row);
  }

  std::string bottom_row = stack_rows.cend()[-2];
  num_stacks = std::count(bottom_row.cbegin(), bottom_row.cend(), '[');

  std::vector<std::stack<char>> stacks(num_stacks);

  std::vector<std::vector<char>> parsed_rows(stack_rows.size() - 1);

  auto raw_row_length{stack_rows.front().length()};

  for (std::size_t i{}; i < parsed_rows.size(); ++i) {
    for (std::size_t j{1}; j < raw_row_length; j += 4) {
        parsed_rows.at(i).push_back(stack_rows.at(i).at(j));
    }
  }

  for (std::size_t row{parsed_rows.size()}; row-- > 0;) {
    for (std::size_t column{}; column < num_stacks; ++column) {
      const auto& c = parsed_rows.at(row).at(column);
      if (c != ' ') {
        stacks.at(column).push(c);
      }
    }
  }

  std::size_t count, from, to;
  const std::regex re{"move ([0-9]+) from ([0-9]+) to ([0-9]+)"};

  for (const auto& move: move_rows) {
    std::smatch m;
    std::regex_search(move, m, re);

    std::from_chars(m.str(1).data(), m.str(1).data() + m.str(1).size(), count);
    std::from_chars(m.str(2).data(), m.str(2).data() + m.str(2).size(), from);
    std::from_chars(m.str(3).data(), m.str(3).data() + m.str(3).size(), to);

    for (std::size_t i{}; i < count; ++i) {
      stacks.at(to - 1).push(stacks.at(from - 1).top());
      stacks.at(from - 1).pop();
    }
  }

  for (const auto& s: stacks) {
    std::cout << s.top();
  }
  std::cout << '\n';
}
