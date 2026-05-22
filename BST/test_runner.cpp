#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <string>

using namespace std;

// Define a special value for null nodes in the array representation
const int null_node = INT_MIN;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Include the user's solution directly
#include "lca_in_bst.h"

// Helper function to build a tree from a level-order traversal vector
TreeNode* buildTree(const vector<int>& nodes) {
    if (nodes.empty() || nodes[0] == null_node) return nullptr;
    
    TreeNode* root = new TreeNode(nodes[0]);
    queue<TreeNode*> q;
    q.push(root);
    
    size_t i = 1;
    while (!q.empty() && i < nodes.size()) {
        TreeNode* curr = q.front();
        q.pop();
        
        if (i < nodes.size() && nodes[i] != null_node) {
            curr->left = new TreeNode(nodes[i]);
            q.push(curr->left);
        }
        i++;
        
        if (i < nodes.size() && nodes[i] != null_node) {
            curr->right = new TreeNode(nodes[i]);
            q.push(curr->right);
        }
        i++;
    }
    
    return root;
}

// Helper function to find a node with a specific value in the tree
TreeNode* findNode(TreeNode* root, int val) {
    if (root == nullptr) return nullptr;
    if (root->val == val) return root;
    
    TreeNode* left_res = findNode(root->left, val);
    if (left_res != nullptr) return left_res;
    
    return findNode(root->right, val);
}

// Helper function to free the tree memory
void freeTree(TreeNode* root) {
    if (root == nullptr) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

void printTestResult(int testNum, const string& testDesc, int expected, int actual) {
    cout << "--------------------------------------------------" << endl;
    cout << "Test Case " << testNum << ": " << testDesc << endl;
    cout << "Expected LCA Node Value: " << expected << endl;
    cout << "Actual LCA Node Value:   " << actual << endl;
    if (expected == actual) {
        cout << "\033[32m[PASS]\033[0m Test passed successfully!" << endl;
    } else {
        cout << "\033[31m[FAIL]\033[0m Test failed." << endl;
    }
}

int main() {
    cout << "==================================================" << endl;
    cout << "        LeetCode 235: LCA in BST Test Runner      " << endl;
    cout << "==================================================" << endl;

    Solution solver;

    // Test Case 1:
    // root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
    vector<int> tree1 = {6, 2, 8, 0, 4, 7, 9, null_node, null_node, 3, 5};
    TreeNode* root1 = buildTree(tree1);
    TreeNode* p1 = findNode(root1, 2);
    TreeNode* q1 = findNode(root1, 8);
    TreeNode* ans1 = solver.lowestCommonAncestor(root1, p1, q1);
    printTestResult(1, "p = 2, q = 8 (LCA should be 6)", 6, ans1 ? ans1->val : -1);
    freeTree(root1);

    // Test Case 2:
    // root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
    TreeNode* root2 = buildTree(tree1);
    TreeNode* p2 = findNode(root2, 2);
    TreeNode* q2 = findNode(root2, 4);
    TreeNode* ans2 = solver.lowestCommonAncestor(root2, p2, q2);
    printTestResult(2, "p = 2, q = 4 (LCA should be 2)", 2, ans2 ? ans2->val : -1);
    freeTree(root2);

    // Test Case 3:
    // root = [2,1], p = 2, q = 1
    vector<int> tree3 = {2, 1};
    TreeNode* root3 = buildTree(tree3);
    TreeNode* p3 = findNode(root3, 2);
    TreeNode* q3 = findNode(root3, 1);
    TreeNode* ans3 = solver.lowestCommonAncestor(root3, p3, q3);
    printTestResult(3, "p = 2, q = 1 (LCA should be 2)", 2, ans3 ? ans3->val : -1);
    freeTree(root3);

    cout << "==================================================" << endl;
    return 0;
}
