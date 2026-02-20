/*
    Priority Queue Process Scheduler
    --------------------------------
    A max-heap based priority queue that schedules processes
    based on their priority values. Higher priority = runs first.

    Supports: ADD, EXTRACT_MAX, CHANGE_PRIORITY, REMOVE, GET_PRIORITY

    Built from scratch using arrays (no STL containers) for my DSA course.
*/

#include <iostream>
#include <string>
using namespace std;

// struct to hold process info
struct Process {
    int id;
    int pr;  // priority value
};

// heap stored as an array + a position lookup table
Process heap[100005];
int position[100005];  // position[id] = index of process in the heap
int heapSize = 0;

// compares two processes - returns true if 'a' should be higher in the heap
// ties are broken by id (higher id = higher priority)
bool hasHigherPriority(Process a, Process b) {
    if (a.pr != b.pr)
        return a.pr > b.pr;
    return a.id > b.id;
}

// swaps two nodes in the heap and updates their positions
void swapNode(int i, int j) {
    position[heap[i].id] = j;
    position[heap[j].id] = i;
    
    Process temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

// bubble up - moves a node upward to maintain heap property
void heapifyUp(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (hasHigherPriority(heap[idx], heap[parent])) {
            swapNode(idx, parent);
            idx = parent;
        }
        else {
            break;
        }
    }
}

// sift down - moves a node downward to maintain heap property
void heapifyDown(int idx) {
    while (true) {
        int largest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        
        if (left < heapSize && hasHigherPriority(heap[left], heap[largest])) {
            largest = left;
        }
        if (right < heapSize && hasHigherPriority(heap[right], heap[largest])) {
            largest = right;
        }
        
        if (largest != idx) {
            swapNode(idx, largest);
            idx = largest;
        }
        else {
            break;
        }
    }
}

// inserts a new process into the priority queue
void add(int id, int p) {
    // skip if this id already exists
    if (position[id] != -1) {
        return;
    }
    
    Process newP;
    newP.id = id;
    newP.pr = p;
    
    heap[heapSize] = newP;
    position[id] = heapSize;
    heapSize++;
    
    heapifyUp(heapSize - 1);
}

// extracts and prints the highest priority process
void extractMax() {
    if (heapSize == 0) {
        cout << "EMPTY" << endl;
        return;
    }
    
    cout << heap[0].id << " " << heap[0].pr << endl;
    
    position[heap[0].id] = -1;
    
    if (heapSize > 1) {
        heap[0] = heap[heapSize - 1];
        position[heap[0].id] = 0;
        heapSize--;
        heapifyDown(0);
    }
    else {
        heapSize--;
    }
}

// updates the priority of an existing process
void changePriority(int id, int newP) {
    if (position[id] == -1) {
        return;
    }
    
    int idx = position[id];
    heap[idx].pr = newP;
    
    heapifyUp(idx);
    heapifyDown(position[id]);
}

// removes a process from the queue by its id
void removeProcess(int id) {
    if (position[id] == -1) {
        return;
    }
    
    int idx = position[id];
    
    if (idx < heapSize - 1) {
        swapNode(idx, heapSize - 1);
        position[id] = -1;
        heapSize--;
        heapifyUp(idx);
        heapifyDown(idx);
    }
    else {
        position[id] = -1;
        heapSize--;
    }
}

// looks up and prints the priority of a given process
void getPriority(int id) {
    if (position[id] == -1) {
        cout << "NOT FOUND" << endl;
    }
    else {
        cout << heap[position[id]].pr << endl;
    }
}

int main() {
    // initialize position array
    for (int i = 0; i < 100005; i++) {
        position[i] = -1;
    }
    
    int q;
    cin >> q;
    
    for (int i = 0; i < q; i++) {
        string cmd;
        cin >> cmd;
        
        if (cmd == "ADD") {
            int id, p;
            cin >> id >> p;
            add(id, p);
        }
        else if (cmd == "EXTRACT_MAX") {
            extractMax();
        }
        else if (cmd == "CHANGE_PRIORITY") {
            int id, p;
            cin >> id >> p;
            changePriority(id, p);
        }
        else if (cmd == "REMOVE") {
            int id;
            cin >> id;
            removeProcess(id);
        }
        else if (cmd == "GET_PRIORITY") {
            int id;
            cin >> id;
            getPriority(id);
        }
    }
    
    return 0;
}