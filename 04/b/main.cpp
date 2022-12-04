#include <charconv>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>

#include "utils.h"

using range = std::pair<std::size_t, std::size_t>;
using range_pair = std::pair<range, range>;

range parse_range(std::string_view s) {
  const auto dash_pos = s.find("-");
  const std::string start_s{s.substr(0, dash_pos)}, end_s{s.substr(dash_pos + 1)};
  std::size_t start{}, end{};
  std::from_chars(start_s.data(), start_s.data() + start_s.size(), start);
  std::from_chars(end_s.data(), end_s.data() + end_s.size(), end);
  return {start, end};
}

range_pair parse_ranges(std::string_view s) {
  const auto comma_pos = s.find(",");
  const std::string a{s.substr(0, comma_pos)}, b{s.substr(comma_pos + 1)};
  return {parse_range(a), parse_range(b)};
}

bool range_overlapped(const range_pair& rp) {
  const auto& [a, b] = rp;
  return a.first <= b.second && a.second >= b.first || b.first <= a.second && b.second >= a.first;
}

int main() {
  const auto data = utils::read_vector_from_file<std::string>("input.txt");
  const auto overlap_count = std::ranges::distance(data | std::views::transform(parse_ranges) | std::views::filter(range_overlapped));
  std::cout << overlap_count << '\n';
}
