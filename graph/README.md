# Graph Algorithms 📊

My implementations of graph algorithms for the DSA course. Trying to keep things clean and well-commented so I can actually understand them later lol.

## What's in here

### Cycle Detection (`cycle-detection.cpp`)

Finds all nodes that belong to a cycle in a **functional graph** (each node has exactly one outgoing edge).

**How it works:**
- Uses a topological-sort-like approach (Kahn's algorithm idea)
- First, peel off all the "leaf" nodes (in-degree = 0) layer by layer using BFS
- Whatever nodes are left standing at the end must be part of a cycle

**Complexity:**

| | Time | Space |
|---|---|---|
| Worst case | O(n) | O(n) |

**Example:**

```
Input:
5
2 3 1 5 5

Output:
3
1 2 3
```
Nodes 1 → 2 → 3 → 1 form a cycle, while nodes 4 and 5 don't.

## How to compile & run

```bash
g++ -o cycle-detection cycle-detection.cpp
./cycle-detection
```

Or on Windows:
```
g++ -o cycle-detection.exe cycle-detection.cpp
cycle-detection.exe
```

## Notes

- I used arrays instead of `vector` / `queue` from STL because it's faster for competitive-programming-style problems.
- Nodes are 1-indexed.
- If you have any suggestions or spot a bug feel free to open an issue!
