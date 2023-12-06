#pragma once
#include <sstream>
#include <vector>

class Solver5 {
public:
    struct Range {
        size_t left;
        size_t right;
    };

    struct RangeMap {
        Range dst;
        Range src;
    };

    struct TranslationMap {
        std::vector<RangeMap> ranges;
    };

    struct Almanac {
        std::vector<size_t> seeds;

        std::vector<TranslationMap> translations;
    };

    static Almanac ReadInput (const std::vector<std::string>& input) {
        Almanac result;
        uint translatorIdx = 0;

        if (const size_t colonPos = input[0].find(':'); colonPos != std::string::npos) {
            std::string seedsStr = input[0].substr(colonPos + 1);
            std::istringstream seedIss(seedsStr);
            while(seedIss.good()) {
                size_t seedNum;
                seedIss >> seedNum;
                result.seeds.push_back(seedNum);
            }
        }

        for (size_t i = 3; i < input.size(); i++) {
            if (input[i].empty()) {
                i++;
                translatorIdx++;
            } else {
                if (result.translations.size() == translatorIdx) {
                    result.translations.emplace_back();
                }
                size_t dst, src, len;
                std::istringstream iss(input[i]);
                iss >> dst >> src >> len;
                RangeMap rMap {{dst, dst + len - 1},{src, src + len - 1}};
                result.translations[translatorIdx].ranges.push_back(rMap);
            }
        }
        return result;
    }

    static size_t SolvePart1 (const std::vector<std::string>& input) {
        size_t result = 0;

        const auto almanac = ReadInput(input);
        auto dataToProcess = almanac.seeds;

        for (const auto & translation : almanac.translations) {
            for (size_t& data_to_process : dataToProcess) {
                for (const auto & range : translation.ranges) {
                    if (data_to_process >= range.src.left && data_to_process <= range.src.right) {
                        data_to_process = data_to_process - range.src.left + range.dst.left;
                        break;
                    }
                }
            }
        }

        if (const auto min = std::min_element(dataToProcess.begin(), dataToProcess.end()); min != dataToProcess.end()) {
            result = *min;
        }
        return result;
    }

    static size_t SolvePart2 (const std::vector<std::string>& input) {
        size_t result = 0;

        return result;
    }
};
