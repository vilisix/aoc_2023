#ifndef AOC1_H
#define AOC1_H

#include <cctype>
#include <vector>

class Solver1 {
public:
    static int SolvePart1 (const std::vector<std::string>& input) {
        int sum = 0;
        for (const auto & inputString : input) {
            size_t left = 0;
            size_t right = 0;
            for (int i = 0; i < inputString.size(); i++) {
                if (inputString[i] >= '0' && inputString[i] <= '9') {
                    left = i;
                    break;
                }
            }
            for (int i = inputString.size() - 1; i >= 0; i--) {
                if (inputString[i] >= '0' && inputString[i] <= '9') {
                    right = i;
                    break;
                }
            }
            const int decodedValue = (inputString[left] - '0') * 10 + (inputString[right] - '0');
            sum += decodedValue;
        }

        return sum;
    }

    static int SolvePart2 (const std::vector<std::string>& input) {
        const std::vector<std::string> strDigits = {"one","two","three","four","five","six","seven","eight","nine"};
        int sum = 0;
        for (const auto & str : input) {
            size_t left = 0;
            int leftDigit = 0;
            size_t right = 0;
            int rightDigit = 0;
            for (int i = 0; i < str.size(); i++) {
                if (str[i] >= '0' && str[i] <= '9') {
                    left = i;
                    leftDigit = (str[left] - '0');
                    break;
                }
            }
            for (int i = str.size() - 1; i >= 0; i--) {
                if (str[i] >= '0' && str[i] <= '9') {
                    right = i;
                    rightDigit = (str[right] - '0');
                    break;
                }
            }

            for (int i = 0; i < strDigits.size(); i++) {
                if (const size_t leftPos = str.find(strDigits[i]); leftPos != std::string::npos && leftPos < left) {
                    left = leftPos;
                    leftDigit = (i + 1);
                }

                if (const size_t rightPos = str.rfind(strDigits[i]); rightPos != std::string::npos && rightPos > right) {
                    right = rightPos;
                    rightDigit = (i + 1);
                }
            }
            const int decodedValue = leftDigit * 10 + rightDigit;
            sum += decodedValue;
        }

        return sum;
    }
};

#endif //AOC1_H
