/*
 * Triangle Counting — Optimized approach
 *
 * Same problem as the brute force version: given perimeter n, count
 * how many distinct triangles (a <= b <= c) with integer sides exist.
 *
 * The trick here:
 *   instead of looping over both a and b, we only loop over a.
 *   for each a, we figure out the valid range [min_b, max_b] using math:
 *     - since a <= b <= c and a + b + c = n, a can go up to n/3
 *     - b must be at least a (so a <= b)
 *     - b must also satisfy a + b > c  =>  b > n/2 - a  =>  b >= n/2 + 1 - a
 *     - b can be at most (n - a) / 2 (so that b <= c)
 *   then the number of valid b values is just max_b - min_b + 1.
 *
 * Time complexity: O(n) — way faster than brute force!
 * (we use long long because n can be large and count might overflow int)
 *
 * written for my DSA course :)
 */

#include <iostream>
#include <algorithm> 
using namespace std;

int main() {
    long long n;
    cin >> n;
    long long count = 0;

    // a only needs to go up to n/3 because a <= b <= c
    for (long long a = 1; a <= n / 3; a++) {
        // b must be >= a and also satisfy triangle inequality (a + b > c)
        long long min_b = max(a, (n / 2) + 1 - a);
        // b can be at most (n-a)/2 to keep b <= c
        long long max_b = (n - a) / 2;
        if (max_b >= min_b) {
            count += (max_b - min_b + 1);
        }
    }

    cout << count << endl;

    return 0;
}