#include <fstream>
#include <iostream>

#include "aoc3/aoc3.h"

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
    const auto input = readInput("./../aoc3/input");

    std::cout << "1: " << Solver3::SolvePart1(input) << std::endl;
    std::cout << "2: " << Solver3::SolvePart2(input) << std::endl;

    return 0;
}
