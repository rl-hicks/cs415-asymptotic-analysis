// task1.h
// CS415 Project 01a - Task 1 (Fibonacci + Euclid GCD)
// Declarations only. Implement in task1.cpp

#ifndef TASK1_H
#define TASK1_H

#include <cstdint>
#include <utility>
#include <vector>

// Results for Fib(k) with counted additions.
struct FibResult {
    std::int64_t value = 0;      // Fib(k)
    std::int64_t addCount = 0;   // Number of additions performed by the recursive algorithm
};

// Results for gcd(m,n) with counted modulo operations.
struct GcdResult {
    std::int64_t value = 0;      // gcd(m, n)
    std::int64_t modCount = 0;   // Number of modulo divisions (%) performed
};


FibResult fib_count(int k);

// Generate scatter data for Task 1a:
// Returns vector of (k, A(k)) where A(k) is additions count for recursive Fib(k).
std::vector<std::pair<int, std::int64_t>> task1a_scatter_data(int kMin, int kMax);

GcdResult gcd_count(std::int64_t m, std::int64_t n);

// Fast iterative Fibonacci generator for scatter mode.
// Returns F[0..maxK] (size maxK+1).
std::vector<std::int64_t> fib_iter_list(int maxK);

// Generate scatter data for Task 1b (worst-case Euclid using consecutive Fibonacci numbers):
// For each k in [kMin..kMax], set n = Fib(k), m = Fib(k+1).
// Returns vector of (n, D(n)) where D(n) is modulo count for gcd(Fib(k+1), Fib(k)).
std::vector<std::pair<std::int64_t, std::int64_t>> task1b_scatter_data(int kMin, int kMax);

#endif // TASK1_H