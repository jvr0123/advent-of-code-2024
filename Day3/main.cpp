#include <algorithm>
#include <format>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

int parse_input(const std::string &input) {
  std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
  auto count{0};
  auto begin = std::sregex_iterator(input.begin(), input.end(), pattern);
  auto end = std::sregex_iterator();
  for (auto it = begin; it != end; ++it) {
    std::smatch match = *it;
    // std::cout << std::format("{} and {}", match.str(1), match.str(2)) <<
    // '\n';
    try {
      count += std::stoi(match[1]) * std::stoi(match[2]);
    } catch (const std::exception &e) {
      continue;
    }
  }
  return count;
}

int parse_input_with_toggles(const std::string &input) {
  std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))");
  bool parse_expr{true};
  auto count{0};
  auto begin = std::sregex_iterator(input.begin(), input.end(), pattern);
  auto end = std::sregex_iterator();
  for (auto it = begin; it != end; ++it) {
    std::smatch match = *it;
    if (match[0].str() == "do()") {
      parse_expr = true;
      continue;
    } else if (match[0].str() == "don't()") {
      parse_expr = false;
      continue;
    }
    try {
      count += parse_expr
                   ? std::stoi(match[1].str()) * std::stoi(match[2].str())
                   : 0;
    } catch (const std::exception &e) {
      continue;
    }
}
return count;
}

int main() {
  std::fstream input("input");
  std::string line{};
  auto count1{0}, count2{0};

  while (std::getline(input, line)) {
    count1 += parse_input(line);
    count2 += parse_input_with_toggles(line);
  }
  std::cout << std::format("{} : {}", "Part 1:", count1) << '\n';
  std::cout << std::format("{} : {}", "Part 2:", count2) << '\n';
  std::cout << std::format("Sample input: {}",
                           parse_input("xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+"
                                       "mul(32,64]then(mul(11,8)mul(8,5))"))
            << '\n';
  std::cout << std::format("Sample input: {}",
                           parse_input_with_toggles(
                               "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64]"
                               "(mul(11,8)undo()?mul(8,5))"))
            << '\n';
}