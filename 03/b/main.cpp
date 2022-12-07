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
    std::cbegin(s1), std::cend(s1),
    std::cbegin(s2), std::cend(s2),
    std::inserter(intersect, std::begin(intersect))
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
        std::cbegin(group_rucksacks),
        std::cend(group_rucksacks),
        std::back_inserter(group_item_sets),
        [](const std::string& s) {return char_set{std::cbegin(s), std::cend(s)};}
      );
      char_set common_items = std::reduce(
        std::cbegin(group_item_sets) + 1,
        std::cend(group_item_sets),
        *std::cbegin(group_item_sets),
        intersect
      );
      priorities.push_back(priority(*std::cbegin(common_items)));
      group_rucksacks.clear();
    }
    if (group_index == rucksacks.size()) {
      break;
    }
    group_rucksacks.emplace_back(rucksacks.at(group_index));
  }
  std::cout << std::accumulate(std::cbegin(priorities), std::cend(priorities), 0) << '\n';
}
