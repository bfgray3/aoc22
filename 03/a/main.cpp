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
  const auto rucksacks = utils::read_vector_from_file<std::string>("input.txt");

  std::vector<char> priorities;

  for (const auto& r: rucksacks) {
    const auto cutoff = r.cbegin() + r.size() / 2;
    std::set<char> c1{r.cbegin(), cutoff}, c2{cutoff, r.cend()}, c_intersection;

    std::set_intersection(
      c1.cbegin(), c1.cend(),
      c2.cbegin(), c2.cend(),
      std::inserter(c_intersection, c_intersection.begin())
    );

    priorities.push_back(priority(*c_intersection.cbegin()));
  }
  std::cout << std::accumulate(priorities.cbegin(), priorities.cend(), 0) << '\n';
}
