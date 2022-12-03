#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <set>
#include <string>
#include <vector>

#include "utils.h"

static constexpr std::size_t group_size{3};
static constexpr char num_letters{26}, upper_start{65}, upper_end{upper_start + num_letters - 1}, lower_start{97}, lower_end{lower_start + num_letters - 1};

char priority(const char c) {
  if (c >= lower_start && c <= lower_end) {
    return c - lower_start + 1;
  } else if (c >= upper_start && c <= upper_end) {
    return c - upper_start + 1 + num_letters;
  } else {
    throw "bad input";
  }
}

std::set<char> intersect(const std::set<char>& s1, const std::set<char>& s2) {
  std::set<char> intersect;
  std::set_intersection(
    s1.cbegin(), s1.cend(),
    s2.cbegin(), s2.cend(),
    std::inserter(intersect, intersect.begin())
  );
  return intersect;
}

int main() {
  auto rucksacks = utils::read_vector_from_file<std::string>("input.txt");
  std::vector<char> priorities;
  std::vector<std::string> group_rucksacks;
  std::size_t group_index{};

  for (std::size_t group_index{}; ; ++group_index) {
    if (group_index && !(group_index % group_size)) {
      std::vector<std::set<char>> group_item_sets;
      std::transform(
        group_rucksacks.cbegin(),
        group_rucksacks.cend(),
        std::back_inserter(group_item_sets),
        [](const std::string& s) {return std::set<char>{s.cbegin(), s.cend()};}
      );
      std::set<char> common_items = std::reduce(
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
  // FIXME: last time through doesn't end up in the vector
  std::cout << std::accumulate(priorities.cbegin(), priorities.cend(), 0) << '\n';
}
