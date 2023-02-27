#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>

static constexpr std::size_t WIN{6}, TIE{3}, LOSS{};

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

std::size_t parse_outcome(const char c) {
  switch (c) {
    case 'X':
      return LOSS;
    case 'Y':
      return TIE;
    case 'Z':
      return WIN;
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

int main(const int, const char** argv) {
  std::ifstream input_file_stream{argv[1]};
  std::string row;
  std::size_t score{};

  while (std::getline(input_file_stream, row)) {
    const auto outcome{parse_outcome(row.back())};
    const auto opponent_move{parse_opponent_move(row.front())};

    score += outcome;
    std::size_t my_move_score{};
    std::size_t remaining_points{
      std::accumulate(
        std::cbegin(score_table),
        std::cend(score_table),
        0u,
        [](const auto sum, const auto& pair) {return sum + pair.second;})
    };

    my_move_score = score_table.at(opponent_move);
    if (outcome == TIE) {
      score += my_move_score;
      continue;
    } else {
      remaining_points -= my_move_score;
    }

    my_move_score = score_table.at(winning.at(opponent_move));
    if (outcome == LOSS) {
      score += my_move_score;
      continue;
    } else {
      remaining_points -= my_move_score;
    }

    score += remaining_points;
  }
  std::cout << score << '\n';
}
