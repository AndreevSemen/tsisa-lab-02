// Copyright 2019 AndreevSemen semen.andreev00@mail.ru

#ifndef INCLUDE_RANDOM_SEARCH_HPP_
#define INCLUDE_RANDOM_SEARCH_HPP_

#include <random>
#include <cmath>
#include <stdexcept>

class RandomSearchResult {
    friend int main();
private:
    size_t _N;
    double _minimum;

public:
    RandomSearchResult(double q, double P);

    void CheckMinimum(double expectedMinimum);

    size_t GetN() const;
    double GetMinimum() const;
};

template < typename Func >
RandomSearchResult RandomSearch(Func func, double a, double b, double q, double P) {
    if (a >= b) throw std::runtime_error{
        "Left bound of interval should be lower than right"
    };

    std::random_device rd;
    std::mt19937_64 randomGenerator{rd()};

    RandomSearchResult result{q, P};

    double minimum = std::numeric_limits<double>::max();
    for (size_t i = 0; i <= result.GetN(); ++i) {
        // Randomize point in [0, 1]
        double x = double(randomGenerator())/std::mt19937_64::max();

        // Adjust scale of interval
        x = std::abs(b - a) * x + a;

        result.CheckMinimum(func(x));
    }

    return result;
}

#endif // INCLUDE_RANDOM_SEARCH_HPP_
