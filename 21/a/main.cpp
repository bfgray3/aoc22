#include <algorithm>
#include <cctype>
#include <functional>
#include <map>  // TODO: unordered_map??
#include <memory>
#include <optional>
#include <string>

#include "utils.h"

using op_function = std::function<long long(long long, long long)>;

struct monkey {
  monkey(const std::string& input) {
    if (std::any_of(std::cbegin(input), std::cend(input), ::isdigit)) {
      number = std::stoi(input.substr(input.find(' ') + 1u, std::string::npos));
    } else {
      op = parse_op(input.at(input.find_first_of("+-*/", 1u)));
    }
  }

  monkey() = delete;
  monkey(const monkey&) = delete;
  monkey(monkey&&) = delete;

  static op_function parse_op(const char op_char) {
    switch (op_char) {
      case '+':
        return std::plus<long long>{};
      case '-':
        return std::minus<long long>{};
      case '*':
        return std::multiplies<long long>{};
      case '/':
        return std::divides<long long>{};
      default:
        throw "bad input";
    }
  }

  void add_dependencies(std::shared_ptr<monkey> first, std::shared_ptr<monkey> second) {
    lhs = first;
    rhs = second;
  }

  long long get_number() const {
    //return number.value_or(op(lhs->get_number(), rhs->get_number()));
    if (number) {
      return number.value();
    }
    return op(lhs->get_number(), rhs->get_number());
  }

  private:
  std::shared_ptr<monkey> lhs, rhs;
  op_function op{std::plus<long long>{}};  // TODO: optional??
  std::optional<long long> number;
};


int main(const int, const char** argv) {
  std::map<std::string, std::shared_ptr<monkey>> monkeys;
  std::string name, row;
  std::ifstream input_file_stream{argv[1]};
  std::vector<std::string> rows;

  while (std::getline(input_file_stream, row)) {
    rows.push_back(row);
  }

  for (const auto& row: rows) {
    name = row.substr(0, row.find(':')); // this is right
    if (monkeys.find(name) == std::end(monkeys)) {
      monkeys.emplace(name, std::make_shared<monkey>(row));
    }
  }

  for (const auto& row: rows) {
    if (!std::any_of(std::cbegin(row), std::cend(row), ::isdigit)) {
      std::cout << "adding deps for: " << row.substr(0, row.find(':')) << '\n';
      std::cout << "lhs: " << monkeys.at(row.substr(6, 4)) << "rhs: " << monkeys.at(row.substr(13, std::string::npos)) << '\n';
      monkeys.at(row.substr(0, row.find(':')))->add_dependencies(monkeys.at(row.substr(6, 4)), monkeys.at(row.substr(13, std::string::npos)));
    }
  }

  std::cout << "almost done\n";
  std::cout << monkeys.at("root")->get_number() << '\n';
}
