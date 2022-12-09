#include <cstddef>
#include <fstream>
#include <iostream>
#include <set>
#include <string>

const static std::size_t MARKER_LENGTH{4};

int main(const int, const char** argv) {
  std::ifstream input_file_stream{argv[1]};
  std::string data;
  std::getline(input_file_stream, data);
  std::size_t index{MARKER_LENGTH};
  std::set<char> s;
  const std::string::const_iterator beg{std::cbegin(data)};
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
