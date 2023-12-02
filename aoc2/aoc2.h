#pragma once
#include <sstream>

class Solver2 {
public:
    struct Game {
        size_t gameIndex;
        std::vector<std::pair<size_t, std::string>> colorOccurrence;
    };

    static Game ParseGame(const std::string& input) {
        Game game;

        if (size_t colonPos = input.find(':'); colonPos != std::string::npos) {
            game.gameIndex = std::stoull(input.substr(5, colonPos - 5));

            std::string colorsStr = input.substr(colonPos + 1);
            std::istringstream iss(colorsStr);
            std::string colorOccurrenceStr;

            while (std::getline(iss, colorOccurrenceStr, ';')) {
                std::istringstream turnIss(colorOccurrenceStr);
                std::string colorOccurence;
                while (std::getline(turnIss, colorOccurence, ',')) {
                    int count;
                    std::string colorName;
                    std::istringstream colorIss(colorOccurence);
                    colorIss >> count >> colorName;

                    game.colorOccurrence.emplace_back(count, colorName);
                }

            }
        }

        return game;
    }

    static size_t SolvePart1 (const std::vector<std::string>& input) {
        size_t sum = 0;
        for (const auto & inputStr : input) {
            auto [gameIndex, colorOccurrence] = ParseGame(inputStr);
            bool gameIsPossible = true;
            for (const auto & [amount, color] : colorOccurrence) {
                if (color == "red" && amount > 12) gameIsPossible = false;
                if (color == "green" && amount > 13) gameIsPossible = false;
                if (color == "blue" && amount > 14) gameIsPossible = false;
            }
            if (gameIsPossible) {
                sum += gameIndex;
            }
        }
        return sum;
    }

    static size_t SolvePart2 (const std::vector<std::string>& input) {
        size_t sum = 0;
        for (const auto & inputStr : input) {
            auto [gameIndex, colorOccurrence] = ParseGame(inputStr);
            size_t maxRed = 0;
            size_t maxGreen = 0;
            size_t maxBlue = 0;
            for (const auto & [amount, color] : colorOccurrence) {
                if (color == "red") maxRed = std::max(amount, maxRed);
                if (color == "green") maxGreen = std::max(amount, maxGreen);
                if (color == "blue") maxBlue = std::max(amount, maxBlue);
            }
            const size_t gamePower = maxRed * maxGreen * maxBlue;
            sum += gamePower;
        }
        return sum;
    }
};