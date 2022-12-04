#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <numeric>
#include <set>
#include <string>
#include <vector>

#include "utils.h"

using char_set = std::set<char>;

static constexpr std::size_t GROUP_SIZE{3};

char priority(const char c) {
  if (c >= 'a' && c <= 'z') {
    return c - 'a' + 1;
  } else if (c >= 'A' && c <= 'Z') {
    return c - 2 * 'A' + 'Z' + 2;
  } else {
    throw "bad input";
  }
}

char_set intersect(const char_set& s1, const char_set& s2) {
  char_set intersect;
  std::set_intersection(
    s1.cbegin(), s1.cend(),
    s2.cbegin(), s2.cend(),
    std::inserter(intersect, intersect.begin())
  );
  return intersect;
}

int main() {
  const auto rucksacks = utils::read_vector_from_file<std::string>("input.txt");
  std::vector<char> priorities;
  std::vector<std::string> group_rucksacks;

  for (std::size_t group_index{}; ; ++group_index) {
    if (group_index && !(group_index % GROUP_SIZE)) {
      std::vector<char_set> group_item_sets;
      std::transform(
        group_rucksacks.cbegin(),
        group_rucksacks.cend(),
        std::back_inserter(group_item_sets),
        [](const std::string& s) {return char_set{s.cbegin(), s.cend()};}
      );
      char_set common_items = std::reduce(
        group_item_sets.cbegin() + 1,
        group_item_sets.cend(),
        *group_item_sets.cbegin(),
        intersect
      );
      priorities.push_back(priority(*common_items.cbegin()));
      group_rucksacks.clear();
    }
    if (group_index == rucksacks.size()) {
      break;
    }
    group_rucksacks.emplace_back(rucksacks.at(group_index));
  }
  std::cout << std::accumulate(priorities.cbegin(), priorities.cend(), 0) << '\n';
}
