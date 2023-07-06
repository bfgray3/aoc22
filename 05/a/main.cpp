#include <charconv>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <ranges>
#include <regex>
#include <stack>
#include <string>
#include <utility>
#include <vector>

int main(const int, const char** argv) {
  std::size_t count{}, from{}, to{};
  std::ifstream input_file_stream{argv[1]};
  std::string row;
  std::vector<std::string> stack_rows, move_rows;
  const std::regex re{"^move ([0-9]+) from ([0-9]+) to ([0-9]+)$"};

  while (std::getline(input_file_stream, row)) {
    if (row.empty()) {
      break;
    }
    stack_rows.push_back(row);
  }

  while (std::getline(input_file_stream, row)) {
    move_rows.push_back(row);
  }

  const auto& bottom_row{*(std::cend(stack_rows) - 2)};
  const auto num_stacks{std::count(std::cbegin(bottom_row), std::cend(bottom_row), '[')};
  const auto raw_row_length{stack_rows.front().length()};

  std::vector<std::stack<char>> stacks(num_stacks);
  std::vector<std::vector<char>> parsed_rows(stack_rows.size() - 1);

  for (std::size_t i{}; i < parsed_rows.size(); ++i) {
    for (std::size_t j{1}; j < raw_row_length; j += 4) {
        parsed_rows.at(i).push_back(stack_rows.at(i).at(j));
    }
  }

  for (auto& r : std::ranges::views::reverse(parsed_rows)) {
    for (std::size_t column{}; std::cmp_less(column, num_stacks); ++column) {
      const auto& c{r.at(column)};
      if (c != ' ') {
        stacks.at(column).push(c);
      }
    }
  }

  for (const auto& move : move_rows) {
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

  for (const auto& s : stacks) {
    std::cout << s.top();
  }
  std::cout << '\n';
}
