//
// Created by Daniel M Padilla on 2/20/26.
//
#include "task1.h"

FibResult fib_count(int k) {

    FibResult result;


    result.addCount = 0;

    if(k == 1){
        result.addCount = 0;
        result.value = 1;
        return result;
    }

    if(k == 0){
        result.addCount = 0;
        result.value = 0;
        return result;
    }



    FibResult left = fib_count(k -1);
    FibResult right = fib_count(k -2);
    result.value = left.value + right.value;
    result.addCount = left.addCount + right.addCount + 1;

    return result;
}

GcdResult gcd_count(std::int64_t m, std::int64_t n) {

    GcdResult result;
    result.value = 0;
    result.modCount = 0;

    while( n != 0){

        result.value = m % n;
        result.modCount++;
        m = n;
        n = result.value;


    }

    result.value = m;

    return result;
}


// Iterative Fibonacci list F[0..maxK]
std::vector<std::int64_t> fib_iter_list(int maxK) {
    std::vector<std::int64_t> F(maxK + 1, 0);
    if (maxK >= 1) F[1] = 1;
    for (int i = 2; i <= maxK; i++) {
        F[i] = F[i - 1] + F[i - 2];
    }
    return F;
}

// Task 1a scatter data: (k, A(k)) using recursive fib_count
std::vector<std::pair<int, std::int64_t>> task1a_scatter_data(int kMin, int kMax) {
    std::vector<std::pair<int, std::int64_t>> data;
    data.reserve(std::max(0, kMax - kMin + 1));

    for (int k = kMin; k <= kMax; k++) {
        FibResult r = fib_count(k);
        data.push_back({k, r.addCount});
    }
    return data;
}

// Task 1b scatter data: (n=Fib(k), D(n)) for gcd(Fib(k+1), Fib(k))
// Use iterative Fibonacci list for speed.
std::vector<std::pair<std::int64_t, std::int64_t>> task1b_scatter_data(int kMin, int kMax) {
    // Need up to Fib(kMax+1)
    auto F = fib_iter_list(kMax + 1);

    std::vector<std::pair<std::int64_t, std::int64_t>> data;
    data.reserve(std::max(0, kMax - kMin + 1));

    for (int k = kMin; k <= kMax; k++) {
        std::int64_t n = F[k];
        std::int64_t m = F[k + 1];

        GcdResult g = gcd_count(m, n);
        data.push_back({n, g.modCount});
    }
    return data;
}

