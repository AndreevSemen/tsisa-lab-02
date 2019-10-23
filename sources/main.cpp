// Copyright 2019 AndreevSemen semen.andreev00@mail.ru

#include <iostream>
#include <fstream>
#include <iomanip>

#include <random_search.hpp>

struct QPIntervals {
public:
    double QBegin;
    double QEnd;
    double QStep;

    double PBegin;
    double PEnd;
    double PStep;
};

template <typename Logger, typename ResultField >
void LogRandomSearchResults(Logger& logger, ResultField field, const QPIntervals& intervals,
                            const std::vector<std::vector<RandomSearchResult>>& results);

double UnimodalFunction(double x);
double MultimodalFunction(double);

int main() {
    double a = -2;
    double b = 0;

    QPIntervals intervals{
        0.005,
        0.105,
        0.005,

        0.9,
        1,
        0.01
    };

    std::ofstream file("./unimodal_results.txt", std::ios::trunc);
    file << "--Unimodal function:" << std::endl << std::endl;

    std::vector<std::vector<RandomSearchResult>> results;
    for (double q = intervals.QBegin; q < intervals.QEnd; q += intervals.QStep) {
        std::vector<RandomSearchResult> row;
        for (double P = intervals.PBegin; P < intervals.PEnd; P += intervals.PStep) {

            row.emplace_back(RandomSearch(UnimodalFunction, a, b, q, P));
        }

        results.emplace_back(std::move(row));
    }

    file << "----N" << std::endl;
    LogRandomSearchResults(file, &RandomSearchResult::GetN, intervals, results);

    file << "----Minimum" << std::endl;
    LogRandomSearchResults(file, &RandomSearchResult::GetMinimum, intervals, results);

    file.close();


    file = std::ofstream{"./multimodal_results.txt", std::ios::trunc};
    file << "--Multimodal function:" << std::endl << std::endl;

    results.clear();
    for (double q = intervals.QBegin; q < intervals.QEnd; q += intervals.QStep) {
        std::vector<RandomSearchResult> row;
        for (double P = intervals.PBegin; P < intervals.PEnd; P += intervals.PStep) {

            row.emplace_back(RandomSearch(MultimodalFunction, a, b, q, P));
        }

        results.emplace_back(std::move(row));
    }

    file << "----N" << std::endl;
    LogRandomSearchResults(file, &RandomSearchResult::GetN, intervals, results);

    file << "----Minimum" << std::endl;
    LogRandomSearchResults(file, &RandomSearchResult::GetMinimum, intervals, results);

    file.close();

    return 0;
}

template <typename Logger, typename ResultField >
void LogRandomSearchResults(Logger& logger, ResultField method, const QPIntervals& intervals,
                            const std::vector<std::vector<RandomSearchResult>>& results) {
    const size_t cellSize = 7;

    logger << "|" << std::setw(cellSize) << "q/P";
    for (double P = intervals.PBegin; P < intervals.PEnd; P += intervals.PStep) {
        logger << "|" << std::setw(cellSize) << P;
    }
    logger << "|" << std::endl;

    auto resultRowIter = results.begin();
    for (double q = intervals.QBegin; q < intervals.QEnd; q += intervals.QStep) {
        auto resultColumnIter = resultRowIter->begin();

        logger << "|" << std::setw(cellSize) << q;
        for (const auto& result : *resultRowIter) {
            double x = (result.*method)();
            logger << "|" << std::setw(cellSize) << std::setprecision(4) << x;
        }

        logger << "|" << std::endl;
        ++resultRowIter;
    }
}

double UnimodalFunction(double x) {
    return std::cos(x)*std::tanh(x);
}

double MultimodalFunction(double x) {
    return UnimodalFunction(x)*std::sin(5*x);
}
