#include "random.h"
#include <random>
#include <utility>

// Рандобное число от `lo` до `hi`
int rand_int(int lo, int hi)
{
    if (lo == hi) return lo;
    if (lo > hi) std::swap(lo, hi);

    static thread_local std::mt19937 rng{ [] {
        std::random_device rd;
        std::seed_seq seed{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
        return std::mt19937(seed);
    }() };

    std::uniform_int_distribution<int> dist(lo, hi);
    return dist(rng);
}