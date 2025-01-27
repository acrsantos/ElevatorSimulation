#pragma once

#include <random>
namespace Util {
inline int generate_rand(int min, int max) {
    std::random_device rd{};
    std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };

    std::mt19937 mt{ ss };

    return std::uniform_int_distribution{ min, max }(mt);
}

};
