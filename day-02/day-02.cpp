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

std::string
equalLettersInCorrectBoxIds(const std::pair<BoxId, BoxId> &correctBoxIds);
std::pair<BoxId, BoxId> findCorrectBoxIds(const std::vector<BoxId> &ids);
bool differsByOneCharacter(const BoxId &first, const BoxId &second);

int main() {
  std::cout << "Part 1: " << checksum(readBoxIds()) << '\n';
  std::cout << "Part 2: "
            << equalLettersInCorrectBoxIds(findCorrectBoxIds(readBoxIds()))
            << '\n';
}

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

std::string
equalLettersInCorrectBoxIds(const std::pair<BoxId, BoxId> &correctBoxIds) {
  std::string equalLetters;

  auto [first, second] = correctBoxIds;

  for (size_t i = 0; i < first.size(); ++i) {
    if (first[i] == second[i]) {
      equalLetters += first[i];
    }
  }

  return equalLetters;
}

std::pair<BoxId, BoxId> findCorrectBoxIds(const std::vector<BoxId> &ids) {
  std::pair<BoxId, BoxId> correctBoxIds;

  bool found = false;
  auto it = ids.cbegin();
  auto const end = ids.cend();

  while (!found && it != end) {
    const auto other = std::find_if(it, end, [&it](const BoxId &id) {
      return differsByOneCharacter(*it, id);
    });

    if (other != end) {
      correctBoxIds = std::make_pair(*it, *other);
      found = true;
    }

    ++it;
  }

  return correctBoxIds;
}

bool differsByOneCharacter(const BoxId &first, const BoxId &second) {
  const int letterCount = first.size();
  int notEqualCount = 0;
  int letterIndex = 0;

  while (notEqualCount <= 1 && letterIndex < letterCount) {
    if (first[letterIndex] != second[letterIndex]) {
      ++notEqualCount;
    }

    ++letterIndex;
  }

  return notEqualCount == 1;
}
