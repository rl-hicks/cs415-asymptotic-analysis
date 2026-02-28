//
// Created by levi on 2/25/2026.
//

#include "Exponentiation.h"


long long Exponentiation::decreaseByOne(int a, int n,  long long &count) {

    if (n == 0) {
        return 1;
    }
    int subproblem = decreaseByOne(a, n-1, count);
    count++;
    return a * subproblem;

}

long long Exponentiation::decreaseByConstantFactor(int a, int n,  long long &count) {

    if (n==0) {
        return 1;
    }
    if ((n % 2) == 0) {
        int result = decreaseByConstantFactor(a, n/2, count);
        count++;
        return result * result;
    }
    int result = decreaseByConstantFactor(a, (n-1)/2, count);
    count+=2;
    return a * result * result;
}

long long Exponentiation::divideAndConquer(int a, int n, long long &count) {

    if (n == 0) {
        return 1;
    }
    if ((n % 2) == 0) {
        const int r1 = divideAndConquer(a, n/2, count);
        const int r2 = divideAndConquer(a, n/2, count);
        count++;
        return r1 * r2;
    }

    const int r1 = divideAndConquer(a, (n-1)/2, count);
    const int r2 = divideAndConquer(a, (n-1)/2, count);
    count+=2;
    return a * r1 * r2;

}
