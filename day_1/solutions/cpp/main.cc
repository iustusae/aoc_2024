#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>
std::vector<std::string> split(const std::string &str,
                               const std::string &delimiter) {
  std::string s{str};
  std::vector<std::string> tokens;
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    tokens.push_back(token);
    s.erase(0, pos + delimiter.length());
  }
  tokens.push_back(s);

  return tokens;
}
auto part_1(const std::string &path) {
  std::ifstream stream(path);
  std::string line{};

  std::vector<int> rhs{};
  std::vector<int> lhs{};

  lhs.reserve(1000); // we got 1k lines
  rhs.reserve(1000);

  const std::string delimiter = "   ";
  while (std::getline(stream, line)) {
    if (line.empty())
      continue;
    auto splitt = split(line, delimiter);
    assert(splitt.size() == 2);
    lhs.push_back(std::stoi(splitt.at(0)));
    rhs.push_back(std::stoi(splitt.at(1)));
  }

  assert(lhs.size() == rhs.size());

  std::sort(std::begin(lhs), std::end(lhs));
  std::sort(std::begin(rhs), std::end(rhs));

  std::vector<int> distances{};
  distances.reserve(1000);

  for (std::ptrdiff_t i = 0; i < std::size(lhs); ++i) {
    distances.emplace_back(std::abs(lhs.at(i) - rhs.at(i)));
  }
  return std::accumulate(std::begin(distances), std::end(distances), 0);
}

auto part_2(const std::string &path) {
  std::ifstream stream(path);
  std::string line{};

  std::vector<int> rhs{};
  std::vector<int> lhs{};

  lhs.reserve(1000);
  rhs.reserve(1000);

  std::unordered_map<int, int> hist{};
  hist.reserve(1000);

  const std::string delimiter = "   ";
  while (std::getline(stream, line)) {
    if (line.empty())
      continue;
    auto splitt = split(line, delimiter);
    assert(splitt.size() == 2);
    lhs.push_back(std::stoi(splitt.at(0)));
    rhs.push_back(std::stoi(splitt.at(1)));
  }

  assert(lhs.size() == rhs.size());

  for (const int &i : lhs) {
    hist.insert({i, 0});
  }

  for (const int &i : rhs) {
    if (hist.find(i) == hist.end()) {
      continue;
    } else {
      ++hist[i];
    }
  }
  int total = 0;
  for (const int &i : lhs) {
    total += (i * hist.at(i));
  }
  return total;
}

int main() {
  const std::string path{"../input.txt"};
  const std::string dummy{"../dummy.txt"};

  std::cout << part_2(path);
}
