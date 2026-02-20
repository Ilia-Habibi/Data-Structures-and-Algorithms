# Heap

My implementations of heap-based data structures for the DSA course.

## Priority Queue Process Scheduler

**File:** `priority-queue-scheduler.cpp`

A process scheduler built on top of a **max-heap**. Each process has an ID and a priority, and the scheduler always picks the one with the highest priority first.

I implemented the whole thing from scratch using arrays — no `priority_queue` from STL or anything like that.

### How it works

- The heap is stored in a simple array (0-indexed)
- There's also a `position[]` array that maps each process ID to its index in the heap, so lookups and updates are fast
- Parent of node `i` → `(i - 1) / 2`
- Left child → `2*i + 1`, Right child → `2*i + 2`

### Supported Commands

| Command | Description |
|---------|-------------|
| `ADD id priority` | Adds a new process (ignored if id already exists) |
| `EXTRACT_MAX` | Removes and prints the highest priority process |
| `CHANGE_PRIORITY id newPriority` | Updates the priority of a process |
| `REMOVE id` | Removes a process by its id |
| `GET_PRIORITY id` | Prints the current priority of a process |

### Example

```
Input:
6
ADD 1 5
ADD 2 10
ADD 3 7
EXTRACT_MAX
GET_PRIORITY 3
REMOVE 3

Output:
2 10
7
```

### Complexity

| Operation | Time |
|-----------|------|
| Add | O(log n) |
| Extract Max | O(log n) |
| Change Priority | O(log n) |
| Remove | O(log n) |
| Get Priority | O(1) |

The `position[]` array is what makes `CHANGE_PRIORITY`, `REMOVE`, and `GET_PRIORITY` efficient — without it you'd have to search the whole heap every time.

### Compile & Run

```bash
g++ priority-queue-scheduler.cpp -o scheduler
./scheduler
```

### Notes

- Tie-breaking: if two processes have the same priority, the one with the higher ID goes first (just a design choice)
- Max heap size is hardcoded to `100005` — should be more than enough for the assignments we get
- I didn't use STL containers on purpose since the whole point was to understand how heaps actually work under the hood