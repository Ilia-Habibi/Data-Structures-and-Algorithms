/*
 * =============================================================================
 *  Parenthesis Checker — matching & validating parentheses in a string
 * =============================================================================
 *
 *  What this does:
 *    - Reads a string of parentheses (e.g., "(())()")
 *    - Checks if every '(' has a matching ')'
 *    - If valid, prints each matched pair with their 1-based positions
 *    - If invalid (unmatched parens), prints -1
 *
 *  How it works:
 *    - We use a stack to keep track of the positions of unmatched '(' characters
 *    - When we see a ')', we pop the most recent '(' — they're a match!
 *    - If the stack is empty when we see ')' or non-empty at the end → invalid
 *
 *  Time complexity:  O(n) — single pass through the string
 *  Space complexity: O(n) — stack + matches vector in the worst case
 *
 *  Example:
 *    Input:  "(())()"
 *    Output:
 *      2 3      (inner pair)
 *      1 4      (outer pair)
 *      5 6      (second pair)
 * =============================================================================
 */

#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

int main() {
    string s;
    cin >> s;

    stack<int> open_indices;            // stores positions of unmatched '(' so far
    vector<pair<int, int>> matches;     // stores matched pairs (open_pos, close_pos)
    bool is_valid = true;

    for (int i = 0; i < s.length(); i++) {
        int current_pos = i + 1;  // using 1-based indexing for output

        if (s[i] == '(') {
            // found an opening paren — push its position, we'll match it later
            open_indices.push(current_pos);
        } 
        else if (s[i] == ')') {
            if (open_indices.empty()) {
                // closing paren with no matching opener — invalid!
                is_valid = false;
                break; 
            } else {
                // match this ')' with the most recent unmatched '('
                int open_pos = open_indices.top();
                open_indices.pop();
                matches.push_back({open_pos, current_pos});
            }
        }
        // any other character is just ignored
    }

    // if we still have unmatched '(' on the stack, it's also invalid
    if (!is_valid || !open_indices.empty()) {
        cout << -1 << endl;
    } 
    else {
        // print all matched pairs
        for (int i = 0; i < matches.size(); i++) {
            cout << matches[i].first << " " << matches[i].second << endl;
        }
    }

    return 0;
}