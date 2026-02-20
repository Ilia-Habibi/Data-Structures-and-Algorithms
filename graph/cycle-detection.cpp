/*
 * Cycle Detection in a Functional Graph
 * --------------------------------------
 * This program finds all nodes that are part of a cycle in a functional graph.
 * A functional graph is a directed graph where each node has exactly one outgoing edge.
 *
 * The idea:
 *   - Every node points to exactly one other node (like a "follow" relationship).
 *   - We want to find which nodes are sitting inside a cycle.
 *   - Nodes that are NOT in any cycle will have an in-degree that eventually
 *     drops to 0 when we peel them off (like topological sort / Kahn's algorithm).
 *   - Whatever is left after peeling = the cycle nodes!
 *
 * Algorithm (basically topological sort):
 *   1. Count in-degrees for every node.
 *   2. Push all nodes with in-degree 0 into a queue (they can't be in a cycle).
 *   3. Process the queue: for each removed node, decrease the in-degree of the
 *      node it points to. If that node's in-degree hits 0, push it too.
 *   4. After the BFS, any node still with in-degree > 0 is part of a cycle.
 *
 * Input:
 *   - First line: n (number of nodes, 1-indexed)
 *   - Second line: n integers, where a[i] is the node that node i points to
 *
 * Output:
 *   - First line: count of nodes in cycles
 *   - Second line: the nodes that are in cycles (space-separated)
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <iostream>
using namespace std;

const int MAXN = 100005;

int a[MAXN];        // a[i] = the node that node i points to
int count_in[MAXN]; // in-degree of each node
int q[MAXN];        // our queue (implemented with a simple array)
int result[MAXN];   // stores the nodes that are part of a cycle

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    // read the edges and count in-degrees
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        count_in[a[i]]++;
    }

    // --- Kahn's-style BFS to remove non-cycle nodes ---
    int head = 0; // front of queue
    int tail = 0; // back of queue

    // start by adding all nodes with 0 in-degree (definitely not in a cycle)
    for (int i = 1; i <= n; i++) {
        if (count_in[i] == 0) {
            q[tail] = i;
            tail++;
        }
    }

    // process the queue
    while (head < tail) {
        int current = q[head];
        head++;

        int idol = a[current]; // the node 'current' points to
        count_in[idol]--;

        // if idol's in-degree dropped to 0, it's also not in a cycle
        if (count_in[idol] == 0) {
            q[tail] = idol;
            tail++;
        }
    }

    // --- collect nodes that are still in a cycle (in-degree > 0) ---
    int result_count = 0;
    for (int i = 1; i <= n; i++) {
        if (count_in[i] > 0) {
            result[result_count] = i;
            result_count++;
        }
    }

    // output
    cout << result_count << endl;

    for (int i = 0; i < result_count; i++) {
        cout << result[i];
        if (i < result_count - 1) {
            cout << " ";
        }
    }
    cout << endl;

    return 0;
}