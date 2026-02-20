/*
 * AVL Tree Implementation
 * -----------------------
 * Self-balancing BST that supports insert, delete, rank queries, and kth smallest.
 * I wrote this for my DSA course. The tree stays balanced using rotations so all
 * operations run in O(log n). Each node also keeps track of the subtree size (cnt)
 * which lets us do order-statistic stuff like finding the kth smallest element.
 *
 * Supported commands (read from stdin):
 *   INSERT x  -> insert value x into the tree
 *   DELETE x  -> delete value x from the tree
 *   KTH k     -> print the k-th smallest element
 *   RANK x    -> print the rank of x (1-indexed)
 *   COUNT l r -> print how many elements are in range [l, r]
 */

#include <iostream>
#include <string>
using namespace std;

// node structure for AVL tree
struct Node {
    int data;
    int h;   // height of this node
    int cnt; // number of nodes in this subtree
    Node* left;
    Node* right;
};

// creates a new leaf node with the given value
Node* newNode(int x) {
    Node* n = new Node();
    n->data = x;
    n->h = 1;
    n->cnt = 1;
    n->left = NULL;
    n->right = NULL;
    return n;
}

// returns the height of a node (0 if null)
int height(Node* n) {
    if (n == NULL)
        return 0;
    return n->h;
}

// returns the subtree size of a node (0 if null)
int count(Node* n) {
    if (n == NULL)
        return 0;
    return n->cnt;
}

// returns the max of two integers
int maxi(int a, int b) {
    if (a > b)
        return a;
    return b;
}

// updates height and subtree count after structural changes
void updateNode(Node* n) {
    if (n != NULL) {
        n->h = 1 + maxi(height(n->left), height(n->right));
        n->cnt = 1 + count(n->left) + count(n->right);
    }
}

// right rotation (used when left subtree is too tall)
//
//       y              x
//      / \            / \
//     x   T3  -->   T1   y
//    / \                 / \
//   T1  T2             T2  T3
//
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* temp = x->right;
    
    // perform rotation
    x->right = y;
    y->left = temp;
    
    // update heights and counts
    updateNode(y);
    updateNode(x);
    
    return x;
}

// left rotation (used when right subtree is too tall)
//
//     x                y
//    / \              / \
//   T1   y    -->    x   T3
//       / \         / \
//      T2  T3     T1  T2
//
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* temp = y->left;
    
    // perform rotation
    y->left = x;
    x->right = temp;
    
    // update heights and counts
    updateNode(x);
    updateNode(y);
    
    return y;
}

// returns balance factor (left height - right height)
// if |bf| > 1, the node is unbalanced and needs rotation
int getBF(Node* n) {
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

// inserts a value into the AVL tree and rebalances if needed
Node* insert(Node* node, int x) {
    // base case: empty spot found, create new node
    if (node == NULL) {
        return newNode(x);
    }
    
    // standard BST recursive insert
    if (x < node->data) {
        node->left = insert(node->left, x);
    }
    else if (x > node->data) {
        node->right = insert(node->right, x);
    }
    else {
        // duplicate value, ignore it
        return node;
    }
    
    // update height and count
    updateNode(node);
    
    // check balance factor to see if we need rotations
    int bf = getBF(node);
    
    // there are 4 possible unbalanced cases:
    
    // Left Left case
    if (bf > 1 && x < node->left->data) {
        return rightRotate(node);
    }
    
    // Right Right case
    if (bf < -1 && x > node->right->data) {
        return leftRotate(node);
    }
    
    // Left Right case
    if (bf > 1 && x > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    // Right Left case
    if (bf < -1 && x < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    return node;
}

// finds the node with the minimum value (leftmost node)
Node* findMin(Node* node) {
    Node* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

// deletes a value from the AVL tree and rebalances
Node* deleteNode(Node* root, int x) {
    if (root == NULL) {
        return root;
    }
    
    // search for the node to delete
    if (x < root->data) {
        root->left = deleteNode(root->left, x);
    }
    else if (x > root->data) {
        root->right = deleteNode(root->right, x);
    }
    else {
        // found the node, now delete it
        
        // case 1 & 2: node has one child or no children
        if (root->left == NULL || root->right == NULL) {
            Node* temp;
            if (root->left != NULL)
                temp = root->left;
            else
                temp = root->right;
            
            delete root;
            return temp;
        }
        else {
            // case 3: node has two children
            // replace with inorder successor (smallest in right subtree)
            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    
    // update height and count
    updateNode(root);
    
    // rebalance if needed
    int bf = getBF(root);
    
    // Left Left case
    if (bf > 1 && getBF(root->left) >= 0) {
        return rightRotate(root);
    }
    
    // Left Right case
    if (bf > 1 && getBF(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    
    // Right Right case
    if (bf < -1 && getBF(root->right) <= 0) {
        return leftRotate(root);
    }
    
    // Right Left case
    if (bf < -1 && getBF(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;
}

// finds the rank of x (how many elements are smaller than x, + 1)
// basically the position x would be in a sorted array
int findRank(Node* node, int x) {
    if (node == NULL) {
        return 1;
    }
    
    if (x < node->data) {
        return findRank(node->left, x);
    }
    else if (x > node->data) {
        return count(node->left) + 1 + findRank(node->right, x);
    }
    else {
        return count(node->left) + 1;
    }
}

// finds the k-th smallest element using subtree sizes
// idea: if left subtree has (k-1) nodes, current node is the answer
//       if k <= left count, recurse left
//       otherwise recurse right with adjusted k
int findKth(Node* node, int k) {
    int leftCnt = count(node->left);
    
    if (k == leftCnt + 1) {
        return node->data;
    }
    else if (k <= leftCnt) {
        return findKth(node->left, k);
    }
    else {
        return findKth(node->right, k - leftCnt - 1);
    }
}

int main() {
    int q;
    cin >> q;
    
    Node* root = NULL;
    
    for (int i = 0; i < q; i++) {
        string cmd;
        cin >> cmd;
        
        if (cmd == "INSERT") {
            int x;
            cin >> x;
            root = insert(root, x);
        }
        else if (cmd == "DELETE") {
            int x;
            cin >> x;
            root = deleteNode(root, x);
        }
        else if (cmd == "KTH") {
            int k;
            cin >> k;
            cout << findKth(root, k) << endl;
        }
        else if (cmd == "RANK") {
            int x;
            cin >> x;
            cout << findRank(root, x) << endl;
        }
        else if (cmd == "COUNT") {
            int l, r;
            cin >> l >> r;
            // number of elements in [l, r] = rank(r+1) - rank(l)
            int ans = findRank(root, r + 1) - findRank(root, l);
            cout << ans << endl;
        }
    }
    
    return 0;
}