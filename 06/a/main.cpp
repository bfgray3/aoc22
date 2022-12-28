#include <cstddef>
#include <fstream>
#include <iostream>
#include <set>
#include <string>

static constexpr std::size_t MARKER_LENGTH{4};

int main(const int, const char** argv) {
  std::ifstream input_file_stream{argv[1]};
  std::string data;
  std::getline(input_file_stream, data);
  auto index{MARKER_LENGTH};
  std::set<char> s;
  const auto beg{std::cbegin(data)};
  std::string::const_iterator end;

  for (; ; ++index) {
    end = beg + index;
    s = std::set<char>{end - MARKER_LENGTH, end};
    if (s.size() == MARKER_LENGTH) {
      break;
    }
  }

  std::cout << index << '\n';
}
