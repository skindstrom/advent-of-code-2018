#include <fstream>
#include <iostream>
#include <range/v3/numeric/accumulate.hpp>
#include <vector>

using frequency_update = int;

std::vector<frequency_update> readFrequencyUpdates();
int calculateFrequency(const std::vector<frequency_update> &updates);

int main() { std::cout << calculateFrequency(readFrequencyUpdates()) << '\n'; }

std::vector<frequency_update> readFrequencyUpdates() {
  std::vector<frequency_update> numbers;

  std::ifstream file("input.txt");
  int number;
  while (file >> number) {
    numbers.emplace_back(number);
  }

  return numbers;
}

int calculateFrequency(const std::vector<frequency_update> &updates) {
  return ranges::accumulate(updates, 0);
}
