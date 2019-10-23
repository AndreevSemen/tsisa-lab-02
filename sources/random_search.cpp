// Copyright 2019 AndreevSemen semen.andreev00@mail.ru

#include <random_search.hpp>

RandomSearchResult::RandomSearchResult(double q, double P)
  : _N{static_cast<size_t>(std::log(1 - P)/std::log(1 - q))}
  , _minimum{std::numeric_limits<double>::max()}
{}

size_t RandomSearchResult::GetN() const {
    return _N;
}

double RandomSearchResult::GetMinimum() const {
    return _minimum;
}

void RandomSearchResult::CheckMinimum(double expectedMinimum) {
    if (expectedMinimum < _minimum) {
        _minimum = expectedMinimum;
    }
}
