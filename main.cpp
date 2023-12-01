#include <fstream>
#include <iostream>

#include "aoc1/aoc1.h"

std::vector<std::string> readInput(const std::string& inputPath) {
    std::ifstream inputFile(inputPath);
    std::vector<std::string> input;

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << inputPath << std::endl;
        return input;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        input.push_back(line);
    }

    inputFile.close();
    return input;
}

int main() {
    const auto input = readInput("./../aoc1/input");

    std::cout << "1: " << Solver1::SolvePart1(input) << std::endl;
    std::cout << "2: " << Solver1::SolvePart2(input) << std::endl;

    return 0;
}
