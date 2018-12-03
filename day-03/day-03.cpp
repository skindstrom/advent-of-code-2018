#include <fstream>
#include <iostream>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <string>
#include <vector>

using BoxId = std::string;

struct Claim {
  BoxId id{};
  int startX{}, startY{};
  int sizeX{}, sizeY{};
};

std::vector<Claim> readClaims();
int overlappingClaimsCount(const std::vector<Claim> &claims);

int main() {
  std::cout << "Part 1: " << overlappingClaimsCount(readClaims()) << '\n';
}

std::vector<Claim> readClaims() {
  std::vector<Claim> claims;
  int stage = 0;

  std::ifstream file("input.txt");

  Claim claim;
  std::string val;
  while (file >> val) {
    switch (stage) {
    case 0:
      claim.id = val.substr(1);
      break;
    case 1:
      // ignore
      break;
    case 2:
      claim.startX = std::stoi(val.substr(0, val.find(',')));
      claim.startY = std::stoi(val.substr(val.find(',') + 1, val.find(':')));
      break;
    case 3:
      claim.sizeX = std::stoi(val.substr(0, val.find('x')));
      claim.sizeY = std::stoi(val.substr(val.find('x') + 1));
      break;
    default:
      std::cerr << "Invalid stage" << '\n';
    }

    ++stage;
    if (stage == 4) {
      stage = 0;
      claims.emplace_back(claim);
    }
  }

  return claims;
}

int overlappingClaimsCount(const std::vector<Claim> &claims) {
  std::vector<int> counts(1000 * 1000);

  ranges::for_each(claims, [&counts](const Claim &claim) {
    for (int x = claim.startX; x < claim.startX + claim.sizeX; ++x) {
      for (int y = claim.startY; y < claim.startY + claim.sizeY; ++y) {
        ++counts.at(x * 1000 + y);
      }
    }
  });

  return ranges::accumulate(counts, 0,
                            [](const int totalCount, const int count) {
                              if (count <= 1) {
                                return totalCount;
                              }
                              return totalCount + 1;
                            });
}
