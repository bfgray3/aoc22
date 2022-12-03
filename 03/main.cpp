#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <set>
#include <string>
#include <vector>

#include "utils.h"

static constexpr char num_letters{26}, upper_start{65}, upper_end{upper_start + num_letters - 1}, lower_start{97}, lower_end{lower_start + num_letters - 1};

char priority(const char& c) {
  if (c >= lower_start && c <= lower_end) {
    return c - lower_start + 1;
  } else if (c >= upper_start && c <= upper_end) {
    return c - upper_start + 1 + num_letters;
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
