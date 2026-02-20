/*
 * =============================================================================
 *  Expression Evaluator — Infix, Postfix & Prefix conversion + evaluation
 * =============================================================================
 *
 *  What this does:
 *    - Converts infix expressions (the normal math we write) to postfix & prefix
 *    - Evaluates postfix and prefix expressions
 *    - Handles multi-digit numbers, operator precedence, and right-associative ^
 *
 *  Key concepts used:
 *    - Stack (custom linked-list implementation, no STL!)
 *    - Shunting-Yard algorithm for infix -> postfix conversion
 *    - Reverse-then-convert trick for infix -> prefix
 *
 *  Time complexity:
 *    - Conversion:  O(n) where n = length of the expression string
 *    - Evaluation:  O(n) single pass through the postfix/prefix string
 *
 *  Space complexity: O(n) for the stack
 * =============================================================================
 */

#include <iostream>
#include <string>
#include <algorithm> 
#include <cmath>     

using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
//  Stack — a simple generic stack built on a singly linked list
//  I could've used std::stack but where's the fun in that, right?
// ─────────────────────────────────────────────────────────────────────────────
template <typename T>
class Stack {
private:
    // Each node holds one value and points to the node below it
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };

    Node* topNode;  // always points to the top of the stack

public:
    Stack() : topNode(nullptr) {}

    // Destructor — pops everything so we don't leak memory
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    // Push a new value on top — O(1)
    void push(T value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
    }

    // Pop the top value and return it — O(1)
    // Returns default T{} if the stack is empty (not ideal, but keeps things simple)
    T pop() {
        if (isEmpty()) {
            return T(); 
        }
        Node* temp = topNode;
        T poppedValue = temp->data;
        topNode = topNode->next;
        delete temp;
        return poppedValue;
    }

    // Peek at the top without removing it — O(1)
    T peek() {
        if (isEmpty()) return T();
        return topNode->data;
    }

    // Check if the stack is empty
    bool isEmpty() {
        return topNode == nullptr;
    }
};

// ─────────────────────────────────────────────────────────────────────────────
//  ExpressionManager — the brain of this program
//  Handles all the conversions and evaluations between infix, postfix & prefix
// ─────────────────────────────────────────────────────────────────────────────
class ExpressionManager {
private:
    /*
     * getPrecedence — returns how "strong" an operator binds
     *   ^          → 3 (highest — exponentiation first!)
     *   * and /    → 2
     *   + and -    → 1 (lowest)
     *   anything else → -1 (not an operator)
     */
    int getPrecedence(char op) {
        if (op == '^') return 3;
        if (op == '*' || op == '/') return 2;
        if (op == '+' || op == '-') return 1;
        return -1;
    }

    // Quick helper — checks if a character is one of the five operators we support
    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
    }

    /*
     * applyOp — does the actual math for two operands and one operator
     * Note: division by zero just returns 0 here (not the best, but keeps it simple)
     */
    double applyOp(double a, double b, char op) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return b != 0 ? a / b : 0; 
            case '^': return pow(a, b);
        }
        return 0;
    }

public:
    /*
     * infixToPostfix — converts an infix expression to postfix (Reverse Polish Notation)
     *
     * Uses the Shunting-Yard algorithm (thanks Dijkstra!):
     *   1. Scan left to right
     *   2. Operands go straight to output
     *   3. Operators get pushed/popped based on precedence
     *   4. Parentheses control grouping
     *
     * The `forPrefix` flag flips associativity handling — it's used internally
     * when we convert to prefix (we reverse the expression, convert to "postfix",
     * then reverse back — neat trick!)
     *
     * Supports: multi-digit numbers, single-letter variables, parentheses
     */
    string infixToPostfix(string infix, bool forPrefix = false) {
        Stack<char> s;
        string postfix = "";

        for (int i = 0; i < (int)infix.length(); i++) {
            char c = infix[i];

            if (c == ' ') continue;  // skip spaces

            // ── Operand: digit(s) ──
            if (isdigit(c)) {
                // grab the full number (could be multi-digit like 42 or 123)
                while (i < (int)infix.length() && isdigit(infix[i])) {
                    postfix += infix[i];
                    i++;
                }
                postfix += ' ';  // space-separate tokens in the output
                i--;
            }
            // ── Operand: variable (single letter) ──
            else if (isalpha(c)) {
                postfix += c;
                postfix += ' ';
            }
            // ── Opening parenthesis → just push it ──
            else if (c == '(') {
                s.push(c);
            }
            // ── Closing parenthesis → pop until we find the matching '(' ──
            else if (c == ')') {
                while (!s.isEmpty() && s.peek() != '(') {
                    postfix += s.pop();
                    postfix += ' ';
                }
                if (!s.isEmpty()) s.pop();  // discard the '('
            }
            // ── Operator → handle precedence & associativity ──
            else if (isOperator(c)) {
                // ^ is right-associative normally; when building prefix we flip it
                bool rightAssoc = (c == '^') != forPrefix;

                // pop operators with higher (or equal, for left-assoc) precedence
                while (!s.isEmpty() &&
                       (rightAssoc  ? getPrecedence(c) <  getPrecedence(s.peek())
                                    : getPrecedence(c) <= getPrecedence(s.peek()))) {
                    postfix += s.pop();
                    postfix += ' ';
                }
                s.push(c);
            }
        }

        // pop whatever is left on the stack
        while (!s.isEmpty()) {
            postfix += s.pop();
            postfix += ' ';
        }

        // trim trailing space
        if (!postfix.empty() && postfix.back() == ' ')
            postfix.pop_back();
        return postfix;
    }

    /*
     * infixToPrefix — converts infix to prefix (Polish Notation)
     *
     * The trick here is pretty cool:
     *   1. Reverse the infix string
     *   2. Swap '(' and ')'
     *   3. Run infixToPostfix on it (with flipped associativity)
     *   4. Reverse the result — boom, you've got prefix!
     */
    string infixToPrefix(string infix) {
        string reversedInfix = infix;
        reverse(reversedInfix.begin(), reversedInfix.end());

        // swap parentheses because we reversed the string
        for (int i = 0; i < (int)reversedInfix.length(); i++) {
            if (reversedInfix[i] == '(') reversedInfix[i] = ')';
            else if (reversedInfix[i] == ')') reversedInfix[i] = '(';
        }

        string postfix = infixToPostfix(reversedInfix, true);
        reverse(postfix.begin(), postfix.end());
        return postfix;
    }

    /*
     * evaluatePostfix — evaluates a postfix expression and returns the result
     *
     * Algorithm (super straightforward):
     *   - See a number? Push it onto the stack.
     *   - See an operator? Pop two numbers, apply the operator, push the result.
     *   - At the end, the answer is the last thing on the stack.
     */
    double evaluatePostfix(string postfix) {
        Stack<double> s;

        int i = 0;
        while (i < (int)postfix.length()) {
            if (postfix[i] == ' ') { i++; continue; }

            if (isdigit(postfix[i])) {
                // build the full number from consecutive digits
                double num = 0;
                while (i < (int)postfix.length() && isdigit(postfix[i])) {
                    num = num * 10 + (postfix[i] - '0');
                    i++;
                }
                s.push(num);
            } else if (isOperator(postfix[i])) {
                // pop two operands — note the order matters for - and /
                double val2 = s.pop();
                double val1 = s.pop();
                s.push(applyOp(val1, val2, postfix[i]));
                i++;
            } else {
                i++;  // skip unknown characters
            }
        }
        return s.pop();
    }

    /*
     * evaluatePrefix — evaluates a prefix expression and returns the result
     *
     * Same idea as postfix evaluation, but we scan right-to-left:
     *   - See a number? Push it.
     *   - See an operator? Pop two numbers (order is different from postfix!),
     *     apply the operator, push the result.
     */
    double evaluatePrefix(string prefix) {
        Stack<double> s;

        // scan from right to left
        int i = (int)prefix.length() - 1;
        while (i >= 0) {
            if (prefix[i] == ' ') { i--; continue; }

            if (isdigit(prefix[i])) {
                // we're reading right-to-left, so we need to find where the number starts
                int end = i;
                while (i >= 0 && isdigit(prefix[i])) i--;

                // now build the number left-to-right
                double num = 0;
                for (int j = i + 1; j <= end; j++)
                    num = num * 10 + (prefix[j] - '0');
                s.push(num);
            } else if (isOperator(prefix[i])) {
                // in prefix, the first popped value is the LEFT operand
                double val1 = s.pop();
                double val2 = s.pop();
                s.push(applyOp(val1, val2, prefix[i]));
                i--;
            } else {
                i--;
            }
        }
        return s.pop();
    }
};

// ─────────────────────────────────────────────────────────────────────────────
//  Main — some test cases to show everything works
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    ExpressionManager mgr;
    
    // --- Test 1: basic parenthesized expression ---
    string infixExp = "(3+4)*5";
    
    cout << "Infix Expression: " << infixExp << endl;
    cout << "----------------------------------------" << endl;

    string postfix = mgr.infixToPostfix(infixExp);
    cout << "Postfix: " << postfix << endl;

    string prefix = mgr.infixToPrefix(infixExp);
    cout << "Prefix:  " << prefix << endl;
    cout << "----------------------------------------" << endl;
    cout << "Evaluation (from Postfix): " << mgr.evaluatePostfix(postfix) << endl;
    cout << "Evaluation (from Prefix):  " << mgr.evaluatePrefix(prefix) << endl;

    // --- Test 2: operator precedence (* before +) ---
    cout << "\n--- Test 2: A+B*C (3+2*4) ---" << endl;
    string exp2 = "3+2*4"; 
    string post2 = mgr.infixToPostfix(exp2);
    cout << "Postfix: " << post2 << endl;   // expected: 3 2 4 * +
    cout << "Result:  " << mgr.evaluatePostfix(post2) << endl;  // expected: 11

    // --- Test 3: right-associative exponentiation (3^(3^2) = 19683, NOT (3^3)^2 = 729) ---
    cout << "\n--- Test 3: Right-associative ^ (3^3^2 = 19683) ---" << endl;
    string exp3 = "3^3^2";
    string post3 = mgr.infixToPostfix(exp3);
    string pre3  = mgr.infixToPrefix(exp3);
    cout << "Postfix: " << post3 << endl;
    cout << "Prefix:  " << pre3  << endl;
    cout << "Result (postfix): " << mgr.evaluatePostfix(post3) << endl;
    cout << "Result (prefix):  " << mgr.evaluatePrefix(pre3)  << endl;

    // --- Test 4: multi-digit number support ---
    cout << "\n--- Test 4: Multi-digit numbers (12+34*2 = 80) ---" << endl;
    string exp4 = "12+34*2";
    string post4 = mgr.infixToPostfix(exp4);
    string pre4  = mgr.infixToPrefix(exp4);
    cout << "Postfix: " << post4 << endl;
    cout << "Prefix:  " << pre4  << endl;
    cout << "Result (postfix): " << mgr.evaluatePostfix(post4) << endl;
    cout << "Result (prefix):  " << mgr.evaluatePrefix(pre4)  << endl;

    return 0;
}