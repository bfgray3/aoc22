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
    const auto cutoff = std::cbegin(r) + r.size() / 2;
    std::set<char> c1{std::cbegin(r), cutoff}, c2{cutoff, std::cend(r)}, c_intersection;

    std::set_intersection(
      std::cbegin(c1), std::cend(c1),
      std::cbegin(c2), std::cend(c2),
      std::inserter(c_intersection, std::begin(c_intersection))
    );

    priorities.push_back(priority(*std::cbegin(c_intersection)));
  }
  std::cout << std::accumulate(std::cbegin(priorities), std::cend(priorities), 0) << '\n';
}
