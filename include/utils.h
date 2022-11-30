#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

// TODO: can use braced initialization?

template <typename T>
std::vector<T> read_vector_from_file(const std::string &filename) {
  std::ifstream is(filename);
  std::istream_iterator<T> start(is), end;
  return {start, end};
}

template <typename T>
void write_vector_to_file(const std::vector<T> &v,
                          const std::string &filename) {
  std::ofstream output_file(filename);
  std::ostream_iterator<T> output_iterator(output_file, "\n");
  std::copy(std::begin(v), std::end(v), output_iterator);
}

template <typename T> std::vector<T> read_vector_from_stdin() {
  std::istream_iterator<T> start(std::cin), end;
  return {start, end};
}

template <typename T> void write_vector_to_stdout(const std::vector<T> &v) {
  std::copy(std::begin(v), std::end(v),
            std::ostream_iterator<T>(std::cout, "\n"));
}
