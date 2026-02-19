/*
 * Triangle Counting — Brute Force approach
 *
 * Problem: given a perimeter n, count how many triangles with
 *          integer side lengths (a, b, c) exist such that a + b + c = n.
 *          we only count distinct triangles so we keep a <= b <= c.
 *
 * How it works:
 *   we loop over all possible values for sides a and b,
 *   then compute c = n - a - b. if a <= b <= c and the triangle
 *   inequality holds (a + b > c), we found a valid triangle.
 *
 * Time complexity: O(n^2) — not great for large n, but easy to understand
 *
 * written for my DSA course :)
 */

#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int count = 0;

    // try all possible values of side a
    for (int a = 1; a <= n; a++) {
        // b starts from a to make sure a <= b
        for (int b = a; b <= n; b++) {
            // c is determined since a + b + c = n
            int c = n - a - b;
            if (b <= c) {
                // triangle inequality: the sum of the two smaller sides
                // must be greater than the largest side
                if (a + b > c) {
                    count++; 
                }
            } 
            else {
                // if b > c then increasing b more won't help, so break
                break;
            }
        }
    }

    cout << count << endl;

    return 0;
}