#include <algorithm>
#include <format>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
  std::fstream input("input");
  std::string line{};
  std::vector<int> list1{};
  std::vector<int> list2{};
  std::unordered_map<int, int> list2_freq_map{};

  auto count1{0};
  auto count2{0};

  while (std::getline(input, line)) {
    std::istringstream iss(line);
    int num1;
    int num2;
    iss >> num1;
    iss >> num2;
    list1.push_back(num1);
    list2.push_back(num2);
  }
  std::sort(list1.begin(), list1.end());
  std::sort(list2.begin(), list2.end());

  std::for_each(list2.begin(), list2.end(),
                [&list2_freq_map](int val) { ++list2_freq_map[val]; });

  for (auto i{0}; i < list1.size(); ++i) {
    count1 += std::abs(list1[i] - list2[i]);
    count2 += list1[i] * list2_freq_map[list1[i]];
  }

  std::cout << std::format("{} : {}", "Part 1:", count1) << '\n';
  std::cout << std::format("{} : {}", "Part 2:", count2) << '\n';
}