#include <fstream>
#include <iostream>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <unordered_set>
#include <vector>

using frequency_update = int;

std::vector<frequency_update> readFrequencyUpdates();
int calculateFrequency(const std::vector<frequency_update> &updates);
int findDuplicateFrequency(const std::vector<frequency_update> &updates);

int main() {
  const auto frequencyUpdates = readFrequencyUpdates();
  std::cout << "Part 1: " << calculateFrequency(frequencyUpdates) << '\n';
  std::cout << "Part 2: " << findDuplicateFrequency(frequencyUpdates) << '\n';
}

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

int findDuplicateFrequency(const std::vector<frequency_update> &updates) {
  std::unordered_set<int> frequencies;

  int frequency = 0;
  auto update = updates.cbegin();
  while (frequencies.count(frequency) == 0) {
    frequencies.emplace(frequency);
    frequency += *update;

    ++update;
    if (update == updates.cend()) {
      update = updates.cbegin();
    }
  }

  return frequency;
}
