#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <set>
#include <string>
#include <vector>

#include "utils.h"

char priority(const char c) {
  if (c >= 'a' && c <= 'z') {
    return c - 'a' + 1;
  } else if (c >= 'A' && c <= 'Z') {
    return c - 2 * 'A' + 'Z' + 2;
  } else {
    throw "bad input";
  }
}

int main() {
  auto rucksacks = utils::read_vector_from_file<std::string>("input.txt");

  std::vector<char> priorities;

  for (const auto& r: rucksacks) {
    auto cutoff = r.cbegin() + r.size() / 2;
    std::set<char> c1{r.cbegin(), cutoff}, c2{cutoff, r.cend()}, c_union;

    std::set_intersection(
      c1.cbegin(), c1.cend(),
      c2.cbegin(), c2.cend(),
      std::inserter(c_union, c_union.begin())
    );

    priorities.push_back(priority(*c_union.cbegin()));
  }
  std::cout << std::accumulate(priorities.cbegin(), priorities.cend(), 0) << '\n';
}
