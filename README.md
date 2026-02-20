# 📚 Data Structures and Algorithms

A collection of classic data structure and algorithm implementations in **C++** and **Python**, built from scratch as part of my university coursework and personal practice.

## 🗂️ Contents

| Topic | Implementation | Language | Complexity |
|-------|---------------|----------|------------|
| **Doubly Linked List** | Student record management with insert/delete operations | C++ | O(n) |
| **Stack** | Parenthesis matching & Expression evaluation (Infix ↔ Postfix ↔ Prefix) | C++ | O(n) |
| **AVL Tree** | Self-balancing BST with Insert, Delete, Rank, K-th smallest | C++ | O(log n) |
| **Max-Heap / Priority Queue** | Process scheduler with dynamic priority management | C++ | O(log n) |
| **Cycle Detection** | Topological sort-based cycle detection in directed graphs | C++ | O(n) |
| **Triangle Counting** | Brute-force O(n²) and optimized O(n) approaches | C++ | O(n) |
| **FFT** | Fast Fourier Transform (Cooley-Tukey) | Python | O(n log n) |

## 🔧 How to Build & Run

```bash
# Compile any C++ file
g++ -std=c++17 -O2 -o output <filename>.cpp
./output

# Run Python files
python3 fft.py
```

## 📌 Highlights

- **AVL Tree**: Full implementation with augmented node counts for order-statistics queries (rank, k-th smallest, range count)
- **Expression Evaluator**: Template-based stack with complete infix-to-postfix/prefix conversion and evaluation
- **Priority Queue**: Array-based max-heap with O(1) lookup using position mapping

## 📄 License

MIT License