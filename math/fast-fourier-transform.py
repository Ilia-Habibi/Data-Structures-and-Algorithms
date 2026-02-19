"""
Fast Fourier Transform (FFT) implementation using the Cooley-Tukey algorithm.
This is a recursive divide-and-conquer approach that computes the DFT in O(n log n).

written for my Data Structures course mini project :)
"""

import math
import cmath


def next_power_of_2(n):
    """
    Finds the smallest power of 2 that is >= n.
    We need this because FFT only works correctly when the input size is a power of 2.
    e.g. 5 -> 8, 7 -> 8, 8 -> 8
    """
    power = 1
    while power < n:
        power *= 2
    return power


def pad_to_power_of_2(v):
    """
    Pads the input list with zeros until its length is a power of 2.
    This is called 'zero-padding' and it doesn't change the result,
    it just makes the array size compatible with our FFT algorithm.
    """
    target = next_power_of_2(len(v))
    # add zeros at the end if needed
    while len(v) < target:
        v.append(complex(0, 0))


def FFT(v):
    """
    Computes the Fast Fourier Transform of the list v (in-place).
    Uses the Cooley-Tukey algorithm which splits the array into
    even-indexed and odd-indexed elements, recursively computes FFT
    on both halves, and then combines them using the butterfly operation.

    the input list v gets modified directly (thats why we dont return anything).
    n must be a power of 2 — use pad_to_power_of_2() before calling this!
    """
    n = len(v)

    # base case: a single element is already its own FFT
    if n == 1:
        return

    # split into even and odd indexed elements
    even = []
    odd = []
    for i in range(n // 2):
        even.append(v[i * 2])
        odd.append(v[i * 2 + 1])

    # recursively compute FFT on both halves
    FFT(even)
    FFT(odd)

    # angle for the nth root of unity
    ang = 2 * math.pi / n

    # w starts at 1 and gets multiplied by wn each iteration
    # wn is the primitive nth root of unity: e^(2*pi*i/n)
    w = complex(1)
    wn = cmath.exp(complex(0, ang))

    # butterfly operation — combine the two halves
    for i in range(n // 2):
        v[i] = even[i] + w * odd[i]
        v[i + n // 2] = even[i] - w * odd[i]
        w *= wn


def main():
    """
    Reads complex numbers from input, runs FFT on them, and prints the result.
    First line: n (how many complex numbers)
    Next n lines: real and imaginary parts separated by space
    """
    n = int(input())
    v = []
    for i in range(n):
        x, y = map(float, input().split())
        v.append(complex(x, y))

    # pad input to the nearest power of 2 so FFT works correctly
    pad_to_power_of_2(v)

    FFT(v)

    # print the results
    for i in range(len(v)):
        print(v[i])


if __name__ == "__main__":
    main()