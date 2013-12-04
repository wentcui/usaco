/*
ID: wentcui1
LANG: C++
TASK: pprime
*/

#include <iostream>
#include <cstdio>
using namespace std;
 
typedef long long int LL;
 
int isp(LL n) {
    if (n == 1) return 0;
    for (LL i = 2; i * i <= n; i++)
        if (!(n % i)) return 0;
    return 1;
}
 
int main() {
    int a, b;
    freopen("pprime.in", "r", stdin), freopen("pprime.out", "w", stdout);
    scanf("%d %d", &a, &b);
    for (LL n = 0; n < 10000; n++) {
        LL number = n, rem = 0, reverse = 0, pdrome, no_digits = 1;
        while (number != 0)
            reverse = reverse * 10 + number % 10, number /= 10 , no_digits *= 10;
        pdrome = n <= 9 ? n : (no_digits / 10) * n + reverse % (no_digits / 10);
 
        if (n == 10 && 11 >= a && 11 <= b) printf("%d\n", 11);  // 11 is the only even palindrome
        if (pdrome >= a && pdrome <= b && isp(pdrome)) printf("%lld\n", pdrome);
    }
    return 0;
}
