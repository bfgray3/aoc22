#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

char parse_opponent_move(const char c) {
  switch (c) {
    case 'A':
      return 'R';
    case 'B':
      return 'P';
    case 'C':
      return 'S';
    default:
      throw "bad input";
  }
}

char parse_my_move(const char c) {
  switch (c) {
    case 'X':
      return 'R';
    case 'Y':
      return 'P';
    case 'Z':
      return 'S';
    default:
      throw "bad input";
  }
}

static const std::unordered_map<char, char> winning{
  {'R', 'S'},
  {'P', 'R'},
  {'S', 'P'}
};

static const std::unordered_map<char, std::size_t> score_table{
  {'R', 1},
  {'P', 2},
  {'S', 3}
};

static constexpr std::size_t WIN{6}, TIE{3}, LOSS{};

int main(const int, const char** argv) {
  std::ifstream input_file_stream{argv[1]};
  std::string row;
  std::size_t score{};

  while (std::getline(input_file_stream, row)) {
    const auto my_move{parse_my_move(row.back())};
    const auto opponent_move{parse_opponent_move(row.front())};

    score += score_table.at(my_move);

    if (my_move == opponent_move) {
      score += TIE;
    } else {
      score += winning.at(my_move) == opponent_move ? WIN : LOSS;
    }
  }
  std::cout << score << '\n';
}
