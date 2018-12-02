#include <fstream>
#include <iostream>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <unordered_map>
#include <vector>

using BoxId = std::string;
using Letter = char;

std::vector<BoxId> readBoxIds();
int checksum(const std::vector<BoxId> &);
bool hasTwoEqualLetters(const BoxId &);
bool hasThreeEqualLetters(const BoxId &);
bool hasEqualLettersCount(const BoxId &, int);

int main() { std::cout << "Part 1: " << checksum(readBoxIds()) << '\n'; }

std::vector<BoxId> readBoxIds() {
  std::vector<BoxId> boxIds;

  std::ifstream file("input.txt");
  BoxId boxId;
  while (file >> boxId) {
    boxIds.emplace_back(boxId);
  }

  return boxIds;
}

int checksum(const std::vector<BoxId> &ids) {
  int twos = 0;
  int threes = 0;

  ranges::for_each(ids, [&twos, &threes](const BoxId &id) {
    if (hasTwoEqualLetters(id)) {
      ++twos;
    }
    if (hasThreeEqualLetters(id)) {
      ++threes;
    }
  });

  return twos * threes;
}

bool hasTwoEqualLetters(const BoxId &id) { return hasEqualLettersCount(id, 2); }
bool hasThreeEqualLetters(const BoxId &id) {
  return hasEqualLettersCount(id, 3);
}

bool hasEqualLettersCount(const BoxId &id, int requestedCount) {
  std::unordered_map<Letter, int> letterCount;

  ranges::for_each(id,
                   [&letterCount](Letter letter) { ++letterCount[letter]; });
  return ranges::any_of(
      letterCount, [requestedCount](std::pair<Letter, int> letterCountPair) {
        return letterCountPair.second == requestedCount;
      });
}
