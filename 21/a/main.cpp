#include <algorithm>
#include <cctype>
#include <fstream>
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "utils.h"

using op_function = std::function<long long(long long, long long)>;

struct monkey {
  monkey(const std::string& input) {
    if (std::any_of(std::cbegin(input), std::cend(input), ::isdigit)) {
      number = std::stoll(input.substr(input.find(' ') + 1u, std::string::npos));
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
    // this segfaults. why?
    // return number.value_or(op(lhs->get_number(), rhs->get_number()));
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

std::string get_name_from_row(const std::string& r) {
  return r.substr(0u, r.find(':'));
}

std::tuple<std::string, std::string, std::string> get_name_and_deps_from_row(const std::string& r) {
  return {
    get_name_from_row(r),
    r.substr(r.find(' ') + 1u, 4u),
    r.substr(r.find_first_of("+-*/", 1u) + 2u, std::string::npos)
  };
}

int main(const int, const char** argv) {
  std::map<std::string, std::shared_ptr<monkey>> monkeys;
  std::string name, row;
  std::ifstream input_file_stream{argv[1]};
  std::vector<std::string> rows;

  while (std::getline(input_file_stream, row)) {
    rows.push_back(row);
  }

  for (const auto& row: rows) {
    name = get_name_from_row(row);
    if (monkeys.find(name) == std::end(monkeys)) {
      monkeys.emplace(name, std::make_shared<monkey>(row));
    }
  }

  for (const auto& row: rows) {
    if (!std::any_of(std::cbegin(row), std::cend(row), ::isdigit)) {
      auto [name, lhs, rhs] = get_name_and_deps_from_row(row);
      monkeys.at(name)->add_dependencies(monkeys.at(lhs), monkeys.at(rhs));
    }
  }

  std::cout << monkeys.at("root")->get_number() << '\n';
}
