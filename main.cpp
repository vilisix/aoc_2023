#include <fstream>
#include <iostream>

#include "aoc4/aoc4.h"

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
    const auto input = readInput("./../aoc4/input");

    std::cout << "1: " << Solver4::SolvePart1(input) << std::endl;
    std::cout << "2: " << Solver4::SolvePart2(input) << std::endl;

    return 0;
}
