#include "utils.h"

// test with  make clean && make day=01 && ./main <<< "1 2 3"

int main() {
  auto v2 = read_vector_from_stdin<int>();
  write_vector_to_file(v2, "asdf");
  auto v3 = read_vector_from_file<int>("asdf");
  write_vector_to_stdout(v3);
}
