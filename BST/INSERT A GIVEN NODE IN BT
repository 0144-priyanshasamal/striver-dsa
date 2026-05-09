#include <iostream>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        // If the tree is empty, return a new node
        if (root == nullptr) {
            return new TreeNode(val);
        }
        
        TreeNode* curr = root;
        while (true) {
            // If the value is less than the current node's value, go left
            if (val < curr->val) {
                if (curr->left != nullptr) {
                    curr = curr->left;
                } else {
                    curr->left = new TreeNode(val);
                    break;
                }
            } 
            // If the value is greater than or equal to the current node's value, go right
            else {
                if (curr->right != nullptr) {
                    curr = curr->right;
                } else {
                    curr->right = new TreeNode(val);
                    break;
                }
            }
        }
        
        return root;
    }
};

// Helper function to print tree in in-order traversal
void inorderTraversal(TreeNode* root) {
    if (root == nullptr) return;
    inorderTraversal(root->left);
    cout << root->val << " ";
    inorderTraversal(root->right);
}

int main() {
    Solution sol;
    
    // Example tree:
    //      4
    //    /   \
    //   2     7
    //  / \
    // 1   3
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    
    cout << "Inorder before insertion: ";
    inorderTraversal(root);
    cout << endl;
    
    // Insert 5
    root = sol.insertIntoBST(root, 5);
    
    cout << "Inorder after inserting 5: ";
    inorderTraversal(root);
    cout << endl;
    
    return 0;
}
