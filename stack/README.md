# Stack

A collection of stack-based problems that I implemented in C++ while studying data structures. These are some of my favorite examples of how a simple data structure like a stack can solve surprisingly complex problems.

---

## What's in here?

### 1. Expression Evaluator (`expression-evaluator.cpp`)

A full-featured expression evaluator that can:

- **Convert** infix expressions (like `(3+4)*5`) to **postfix** (Reverse Polish) and **prefix** (Polish) notation
- **Evaluate** both postfix and prefix expressions

#### Highlights

- Custom **linked-list-based stack** — no STL, built from scratch
- Implements the **Shunting-Yard algorithm** (by Dijkstra) for infix → postfix conversion
- Uses a clever **reverse-and-convert trick** for infix → prefix
- Handles **multi-digit numbers**, **operator precedence**, and **right-associative `^`** (exponentiation)
- Supports `+`, `-`, `*`, `/`, `^` operators and parentheses

#### Example

```
Input:   (3+4)*5

Postfix: 3 4 + 5 *
Prefix:  * + 3 4 5
Result:  35
```

#### Complexity

| Operation  | Time | Space |
|------------|------|-------|
| Conversion | O(n) | O(n)  |
| Evaluation | O(n) | O(n)  |

---

### 2. Parenthesis Checker (`parenthesis-checker.cpp`)

A simple but handy tool that:

- Checks if parentheses in a string are **balanced**
- If valid, outputs the **matched pairs** with their 1-based positions
- If invalid, outputs `-1`

#### Highlights

- Uses `std::stack` to track opening parentheses
- Clean single-pass algorithm
- Outputs positions of each matched `(` `)` pair — great for understanding nesting

#### Example

```
Input:  (())()

Output:
2 3
1 4
5 6
```

```
Input:  (()

Output:
-1
```

#### Complexity

| Operation | Time | Space |
|-----------|------|-------|
| Checking  | O(n) | O(n)  |

---

## How to compile & run

Make sure you have a C++ compiler installed (g++, clang++, MSVC, etc.).

```bash
# Expression Evaluator
g++ -o expression-evaluator expression-evaluator.cpp -std=c++17
./expression-evaluator

# Parenthesis Checker
g++ -o parenthesis-checker parenthesis-checker.cpp -std=c++17
./parenthesis-checker
```

---

## Concepts I learned

- How **stacks** work under the hood (linked list implementation)
- The **Shunting-Yard algorithm** and why postfix notation is useful
- Difference between **left-associative** and **right-associative** operators
- How compilers and calculators actually parse math expressions (it's all stacks!)
- Pattern matching with stacks (parenthesis balancing)

---

## What I'd like to add next

- [ ] Support for unary operators (like negative numbers: `-5+3`)
- [ ] Floating-point number support in the expression evaluator
- [ ] Extend the parenthesis checker to handle `{}`, `[]`, and `<>` too
- [ ] Infix expression evaluation directly (without converting first)

