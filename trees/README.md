# Trees

My tree data structure implementations for the DSA course.

## AVL Tree

An AVL tree is a self-balancing binary search tree. After every insertion or deletion, it checks the **balance factor** of each node and does rotations to keep the tree balanced. This guarantees O(log n) time for search, insert, and delete.

### What it does

The program reads queries from standard input and supports these commands:

| Command | Description |
|---------|-------------|
| `INSERT x` | Insert value `x` into the tree |
| `DELETE x` | Delete value `x` from the tree |
| `KTH k` | Print the k-th smallest element |
| `RANK x` | Print the rank of `x` (its position in sorted order) |
| `COUNT l r` | Print how many elements fall in the range [l, r] |

### How it works

Each node stores its height and the size of its subtree (`cnt`). The subtree size is what makes the order-statistic queries (KTH, RANK, COUNT) possible without having to traverse the whole tree.

There are 4 rotation cases to handle when the tree gets unbalanced:
- **Left Left** — single right rotation
- **Right Right** — single left rotation
- **Left Right** — left rotation on left child, then right rotation
- **Right Left** — right rotation on right child, then left rotation

For deletion, when a node has two children, I replace it with its inorder successor (the smallest node in the right subtree) and then delete that successor.

### Example

```
7
INSERT 10
INSERT 20
INSERT 5
INSERT 3
RANK 10
KTH 2
COUNT 3 15
```

Output:
```
3
5
3
```

### How to compile and run

```bash
g++ -o avl avl-tree.cpp
./avl < input.txt
```

### Complexity

| Operation | Time |
|-----------|------|
| Insert | O(log n) |
| Delete | O(log n) |
| KTH | O(log n) |
| RANK | O(log n) |
| COUNT | O(log n) |

Space complexity is O(n) for storing the tree nodes.