# Linked List

Hey! This folder contains my linked list implementation for my **Data Structures and Algorithms** course at university.

## What's in here?

### 📄 `doubly-linked-list.cpp`

A **Doubly Linked List** implementation in C++ that manages student records. Each node in the list stores a `Student` object and has pointers to both the next and previous nodes — so we can traverse the list in both directions!

I used a student records system as a real-world use case to make things more interesting (instead of just storing plain integers lol).

#### Features

- **Insert** a student at the front, back, or after a specific student (by ID)
- **Delete** a student from the front, back, or after a specific student (by ID)
- **Query / Filter** students based on GPA:
  - All grade A students (GPA ≥ 17 in total + both semesters)
  - Students with grade A only in total GPA (but not all semesters)
  - Conditional / probation students (GPA < 12 in any semester)
- **Print** the full list of students

#### How it works

The list maintains two pointers — `head` and `tail` — so that insertions and deletions at both ends run in **O(1)** time. Operations that require searching by student ID take **O(n)** in the worst case since we need to walk through the list.

```
 nullptr <-- [Mona] <--> [Amir] <--> [Mohammad] <--> [Sara] <--> [Aryan] <--> [Mehrad] --> nullptr
              head                                                               tail
```

#### Time Complexity

| Operation          | Time Complexity |
| ------------------ | --------------- |
| Insert front/back  | O(1)            |
| Insert after (ID)  | O(n)            |
| Delete front/back  | O(1)            |
| Delete after (ID)  | O(n)            |
| Search / Filter    | O(n)            |
| Print all          | O(n)            |

#### Space Complexity

**O(n)** — where n is the number of students stored in the list.

## How to compile and run

Make sure you have a C++ compiler installed (like g++), then:

```bash
g++ doubly-linked-list.cpp -o doubly-linked-list
./doubly-linked-list
```

Or on Windows:

```powershell
g++ doubly-linked-list.cpp -o doubly-linked-list.exe
.\doubly-linked-list.exe
```

## Sample Output

```
--- Full Student List ---
ID: 9900 | Name: Mona Zare | Total: 19.5 | S1: 19.5 | S2: 19.5
ID: 9901 | Name: Amir Khodaei | Total: 18.5 | S1: 18 | S2: 19
ID: 9905 | Name: Mohammad Zafari | Total: 11 | S1: 10 | S2: 12
ID: 9902 | Name: Sara Mehrabi | Total: 16 | S1: 15.4 | S2: 16.6
ID: 9903 | Name: Aryan Samin | Total: 17.2 | S1: 16 | S2: 18.4
ID: 9904 | Name: Mehrad Rahimi | Total: 13 | S1: 11.5 | S2: 14.5
-------------------------

--- Students with All 'A' Grades (Total, S1, S2 >= 17) ---
ID: 9900 | Name: Mona Zare | Total: 19.5 | S1: 19.5 | S2: 19.5
ID: 9901 | Name: Amir Khodaei | Total: 18.5 | S1: 18 | S2: 19

--- Students with Only Total Grade 'A' (Total >= 17) ---
ID: 9903 | Name: Aryan Samin | Total: 17.2 | S1: 16 | S2: 18.4

--- Conditional Students (GPA < 12 in at least one semester) ---
ID: 9905 | Name: Mohammad Zafari | Total: 11 | S1: 10 | S2: 12
ID: 9904 | Name: Mehrad Rahimi | Total: 13 | S1: 11.5 | S2: 14.5
```

## What I learned

- How doubly linked lists differ from singly linked lists (the `prev` pointer is a game changer for deletions!)
- Managing `head` and `tail` pointers and keeping them in sync
- How to handle edge cases (empty list, single node, deleting head/tail)
- Memory management with `new` and `delete` in C++ — gotta avoid those memory leaks!

---

*Part of my [Data Structures and Algorithms](../) coursework.*
