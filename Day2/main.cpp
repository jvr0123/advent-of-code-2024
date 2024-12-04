#include <algorithm>
#include <format>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

const auto k_min_diff{1};
const auto k_max_diff{3};

bool is_safe(const std::vector<int> &report, int ignore_idx) {
  auto is_increasing{false};
  auto first_comp{true};
  auto l{0}, r{1};
  while (r < report.size()) {
    if (l == ignore_idx) {
      ++l;
      continue;
    }
    if (r == ignore_idx || l == r) {
      ++r;
      continue;
    }
    if (first_comp) {
      is_increasing = report[l] < report[r];
      first_comp = false;
    }
    if (std::abs(report[l] - report[r]) > k_max_diff ||
        std::abs(report[l] - report[r]) < k_min_diff) {
      return false;
    }

    if ((report[l] > report[r] && is_increasing) ||
        (report[l] < report[r] && !is_increasing)) {
      return false;
    }
    ++r;
    ++l;
  }
  return true;
}

bool is_single_removal_safe(const std::vector<int> &report) {
  for (auto i{0}; i < report.size(); ++i) {
    if (is_safe(report, i)) {
      return true;
    }
  }
  return false;
}

int main() {
  std::fstream input("input");
  std::string line{};
  auto count1{0}, count2{0};

  while (std::getline(input, line)) {
    std::vector<int> reports{};
    std::istringstream iss(line);
    auto num{0};
    while (iss >> num) {
      reports.push_back(num);
    }
    count1 += is_safe(reports, -1) ? 1 : 0;
    count2 += is_single_removal_safe(reports) ? 1 : 0;
  }
  std::cout << std::format("{} : {}", "Part 1:", count1) << '\n';
  std::cout << std::format("{} : {}", "Part 1:", count2) << '\n';
}