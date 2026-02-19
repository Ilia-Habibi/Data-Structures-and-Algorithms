# Math

some math-related algorithms and problems I implemented for my DSA course.

---

## Fast Fourier Transform (FFT)

**File:** `fast-fourier-transform.py`

an implementation of the Cooley-Tukey FFT algorithm in Python. it computes the Discrete Fourier Transform (DFT) of a sequence in $O(n \log n)$ time instead of the naive $O(n^2)$.

the algorithm works by recursively splitting the input into even and odd indexed elements, computing FFT on both halves, and combining them with the butterfly operation. input size has to be a power of 2 so we zero-pad it if needed.

**Input format:**
- first line: `n` (number of complex numbers)
- next `n` lines: real and imaginary parts separated by space

**Example:**
```
4
1 0
2 0
3 0
4 0
```

---

## Triangle Counting

given a perimeter `n`, count how many distinct triangles with integer side lengths exist. sides are `a <= b <= c` and they must satisfy `a + b + c = n` and the triangle inequality `a + b > c`.

I did this in two ways:

### Brute Force

**File:** `triangle-counting-bruteforce.cpp`

the straightforward approach — just loop through all possible values of `a` and `b`, compute `c = n - a - b`, and check if it forms a valid triangle. simple but runs in $O(n^2)$ which gets slow for large inputs.

### Optimized

**File:** `triangle-counting-optimized.cpp`

instead of trying every `(a, b)` pair, I figured out the math to calculate the valid range of `b` for each `a` directly. this way we only need one loop over `a` (which goes up to `n/3`), making it $O(n)$. also uses `long long` so it handles bigger numbers without overflow.

**Input format (for both):**
- a single integer `n` (the perimeter)

**Example:**
```
12
```
**Output:**
```
3
```
(the triangles are: 2,4,6 — wait no lol, 2+4 = 6 that's not valid. the actual ones for n=12 are: (2,4,6) nope... ok let me think... (1,5,6) no, (2,5,5) yes, (3,4,5) yes, (4,4,4) yes — so 3 is correct!)

---

## How to run

**Python (FFT):**
```bash
python fast-fourier-transform.py
```

**C++ (Triangle counting):**
```bash
g++ triangle-counting-bruteforce.cpp -o bruteforce
./bruteforce

g++ triangle-counting-optimized.cpp -o optimized
./optimized
```
