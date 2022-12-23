#include <algorithm>
#include <cctype>
#include <functional>
#include <map>  // TODO: unordered_map??
#include <memory>
#include <optional>
#include <string>

#include "utils.h"

using op_function = std::function<int(int, int)>;

struct monkey {
  monkey(const std::string& input) {
    if (std::any_of(std::cbegin(input), std::cend(input), ::isdigit)) {
      // this is right
      number = std::stoi(input.substr(input.find(' ') + 1, std::string::npos));
    } else {
      // this is right
      op = parse_op(input.at(input.find_first_of("+-*/", 1u)));
    }
  }

  monkey() = delete;
  monkey(const monkey&) = delete;
  monkey(monkey&&) = delete;

  static op_function parse_op(const char op_char) {
    switch (op_char) {
      case '+':
        return std::plus<int>{};
      case '-':
        return std::minus<int>{};
      case '*':
        return std::multiplies<int>{};
      case '/':
        return std::divides<int>{};
      default:
        throw "bad input";
    }
  }

  void add_dependencies(std::shared_ptr<monkey> first, std::shared_ptr<monkey> second) {
    lhs = first;
    rhs = second;
  }

  int get_number() const {
    //return number.value_or(op(lhs->get_number(), rhs->get_number()));
    if (number) {
      return number.value();
    }
    return op(lhs->get_number(), rhs->get_number());
  }

  private:
  std::shared_ptr<monkey> lhs, rhs;
  op_function op{std::plus<int>{}};  // TODO: optional??
  std::optional<int> number;
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
  std::cout << "done adding monkeys\n";
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
