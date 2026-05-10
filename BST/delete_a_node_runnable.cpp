#include <iostream>
using namespace std;

/**
 * Definition for a binary tree node.
 */
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
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == NULL) {
            return NULL;
        }
        // If the root itself is the node to be deleted
        if (root->val == key) {
            return helper(root);
        }
        
        TreeNode* dummy = root;
        while (root != NULL) {
            if (root->val > key) { // Go left
                if (root->left != NULL && root->left->val == key) {
                    root->left = helper(root->left);
                    break;
                } else {
                    root = root->left;
                }
            } else { // Go right
                if (root->right != NULL && root->right->val == key) {
                    root->right = helper(root->right);
                    break;
                } else {
                    root = root->right;
                }
            }
        }
        return dummy;
    }

private:
    TreeNode* helper(TreeNode* root) {
        // If one of the children is NULL, simply return the other child
        if (root->left == NULL) {
            return root->right;
        } else if (root->right == NULL) {
            return root->left;
        }
        
        // If both children exist:
        TreeNode* rightChild = root->right;
        TreeNode* lastRight = findLastRight(root->left);
        
        // Attach the original right child to the right-most node of the left child
        lastRight->right = rightChild;
        
        // Return the left child as the new root of this subtree
        return root->left;
    }

    TreeNode* findLastRight(TreeNode* root) {
        if (root->right == NULL) {
            return root;
        }
        return findLastRight(root->right);
    }
};

// --- Helper Functions for VS Code Testing ---

void printInOrder(TreeNode* root) {
    if (root == NULL) return;
    printInOrder(root->left);
    cout << root->val << " ";
    printInOrder(root->right);
}

int main() {
    // Let's build the example tree:
    //         5
    //        / \
    //       3   6
    //      / \   \
    //     2   4   7
    
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(7);

    cout << "Original BST (In-order): ";
    printInOrder(root);
    cout << "\n";

    Solution sol;
    int keyToDelete = 3;
    cout << "Deleting node " << keyToDelete << "...\n";
    
    root = sol.deleteNode(root, keyToDelete);

    cout << "BST after deletion (In-order): ";
    printInOrder(root);
    cout << "\n";

    return 0;
}
