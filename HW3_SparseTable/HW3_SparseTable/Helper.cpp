#include "Helper.h"

int findMin(int a, int b) {
    return a < b ? a : b;
}
int findMax(int a, int b) {
    return a > b ? a : b;
}
int findGCD(int a, int b) {
    if (b == 0) return a;
    return findGCD(b, a % b);
}