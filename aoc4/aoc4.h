#pragma once
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

class Solver4 {
public:
    struct ScratchCard {
        int index = 0;
        std::set<size_t> winningNumbers;
        std::vector<size_t> playerNumbers;
    };

    static std::vector<ScratchCard> ParseInput (const std::vector<std::string>& input) {
        std::vector<ScratchCard> result;

        for (const auto & inputStr : input) {
            ScratchCard card;
            if (const size_t colonPos = inputStr.find(':'); colonPos != std::string::npos) {
                card.index = std::stoi(inputStr.substr(5, colonPos - 5));
                std::string cardStr = inputStr.substr(colonPos + 1);
                if (const size_t linePos = cardStr.find('|'); linePos != std::string::npos) {
                    std::string winningNumbers = cardStr.substr(0, linePos - 1);
                    std::string playerNumbers = cardStr.substr(linePos + 1);

                    std::istringstream winningIss(winningNumbers);
                    while (winningIss.good()) {
                        size_t num;
                        winningIss >> num;
                        card.winningNumbers.insert(num);
                    }

                    std::istringstream playerIss(playerNumbers);
                    while (playerIss.good()) {
                        size_t num;
                        playerIss >> num;
                        card.playerNumbers.push_back(num);
                    }
                }
            }
            result.push_back(card);
        }
        return result;
    }

    static size_t SolvePart1 (const std::vector<std::string>& input) {
        size_t result = 0;

        const auto cards = ParseInput(input);
        for (const auto & [index, winningNumbers, playerNumbers] : cards) {
            size_t cardScore = 0;
            for (size_t player_number : playerNumbers) {
                if (auto found = winningNumbers.find(player_number); found != winningNumbers.end()) {
                    if (cardScore == 0) {
                        cardScore = 1;
                    } else {
                        cardScore *= 2;
                    }
                }
            }
            result += cardScore;
        }
        return result;
    }

    static size_t SolvePart2 (const std::vector<std::string>& input) {
        size_t result = 0;
        std::unordered_map<int, int> cardsCount;

        const auto cards = ParseInput(input);
        for (const auto & [index, winningNumbers, playerNumbers] : cards) {
            cardsCount[index]++;
            size_t cardScore = 0;
            for (size_t player_number : playerNumbers) {
                if (auto found = winningNumbers.find(player_number); found != winningNumbers.end()) {
                    cardScore++;
                }
            }

            for(int i = 0; i < cardScore; i++) {
                cardsCount[index + i + 1] += cardsCount[index];
            }

            result += cardsCount[index];
        }

        return result;
    }
};
