#pragma once
#include <map>
#include <set>

class Solver3 {
public:
    static std::vector<std::vector<char>> GetInputMatrix(const std::vector<std::string>& input) {
        std::vector<std::vector<char>> result;

        for (const auto & inputStr : input) {
            std::vector<char> row;
            for (char inputChar : inputStr) {
                row.push_back(inputChar);
            }
            row.push_back('.');
            result.push_back(row);
        }

        return result;
    }

    inline static std::vector<std::pair<int,int>> directions = {
            {-1,-1},{-1,0},{-1,1},
            {0,-1},{0,1},
            {1,-1},{1,0},{1,1}
        };

    static bool isAdjacentToSymbol(const size_t row, const size_t col, std::vector<std::vector<char>>& matrix) {
        bool result = false;

        for (const auto & [rowOffset, colOffset] : directions) {
            const auto newRow = row + rowOffset;
            const auto newCol = col + colOffset;
            if (newRow < 0 || newRow >= matrix.size()) continue;
            if (newCol < 0 || newCol >= matrix[0].size()) continue;

            if (matrix[newRow][newCol] != '.'
                && (matrix[newRow][newCol] < '0'
                    || matrix[newRow][newCol] > '9')) {
                return true;
            }
        }
        return result;
    }

    static std::vector<size_t> getAdjacentSymbols(const char symbol, const size_t row, const size_t col, std::vector<std::vector<char>>& matrix) {
        std::vector<size_t> result;

        for (const auto & [rowOffset, colOffset] : directions) {
            const auto newRow = row + rowOffset;
            const auto newCol = col + colOffset;
            if (newRow < 0 || newRow >= matrix.size()) continue;
            if (newCol < 0 || newCol >= matrix[0].size()) continue;

            if (matrix[newRow][newCol] == symbol) {
                result.push_back(newRow * matrix[0].size() + newCol);
            }
        }
        return result;
    }

    static size_t SolvePart1 (const std::vector<std::string>& input) {
        size_t result = 0;
        auto matrix = GetInputMatrix(input);
        for (int i = 0; i < matrix.size(); i++) {
            size_t num = 0;
            bool isPart = false;
            for (int j = 0; j < matrix[i].size(); j++) {
                if (matrix[i][j] >= '0' && matrix[i][j] <= '9') {
                    num *= 10;
                    num += matrix[i][j] - '0';
                    isPart |= isAdjacentToSymbol(i,j,matrix);
                } else {
                    if (isPart) {
                        result += num;
                    }
                    isPart = false;
                    num = 0;
                }
            }
        }

        return result;
    }

    static size_t SolvePart2 (const std::vector<std::string>& input) {
        std::map<size_t, std::pair<size_t, size_t>> gears;
        size_t result = 0;
        auto matrix = GetInputMatrix(input);
        for (int i = 0; i < matrix.size(); i++) {
            size_t num = 0;
            std::set<size_t> neighbourGears;
            for (int j = 0; j < matrix[i].size(); j++) {
                if (matrix[i][j] >= '0' && matrix[i][j] <= '9') {
                    num *= 10;
                    num += matrix[i][j] - '0';
                    for (size_t adjacent_symbol : getAdjacentSymbols('*', i, j, matrix)) {
                        neighbourGears.insert(adjacent_symbol);
                    }
                } else {
                    for (size_t neighbour_gear : neighbourGears) {
                        if (gears[neighbour_gear].first == 0) {
                            gears[neighbour_gear].second = 1;
                        }
                        gears[neighbour_gear].first++;
                        gears[neighbour_gear].second *= num;
                    }
                    neighbourGears.clear();
                    num = 0;
                }
            }
        }

        for (const auto & [gearIdx, gearData] : gears) {
            if (gearData.first > 1) {
                result += gearData.second;
            }
        }

        return result;
    }
};
