/*
450. Delete Node in a BST

Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:
1. Search for a node to remove.
2. If the node is found, delete the node.

Example 1:
Input: root = [5,3,6,2,4,null,7], key = 3
Output: [5,4,6,2,null,null,7]
Explanation: Given key to delete is 3. So we find the node with value 3 and delete it.
One valid answer is [5,4,6,2,null,null,7], shown in the above BST.
Please notice that another valid answer is [5,2,6,null,4,null,7] and it's also accepted.

Example 2:
Input: root = [5,3,6,2,4,null,7], key = 0
Output: [5,3,6,2,4,null,7]
Explanation: The tree does not contain a node with value = 0.

Example 3:
Input: root = [], key = 0
Output: []

Constraints:
* The number of nodes in the tree is in the range [0, 10^4].
* -10^5 <= Node.val <= 10^5
* Each node has a unique value.
* root is a valid binary search tree.
* -10^5 <= key <= 10^5

Follow up: Could you solve it with time complexity O(height of tree)?
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == NULL) {
            return NULL;
        }
        if (root->val == key) {
            return helper(root);
        }
        
        TreeNode* dummy = root;
        while (root != NULL) {
            if (root->val > key) {
                if (root->left != NULL && root->left->val == key) {
                    root->left = helper(root->left);
                    break;
                } else {
                    root = root->left;
                }
            } else {
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
        if (root->left == NULL) {
            return root->right;
        } else if (root->right == NULL) {
            return root->left;
        }
        
        TreeNode* rightChild = root->right;
        TreeNode* lastRight = findLastRight(root->left);
        lastRight->right = rightChild;
        
        return root->left;
    }

    TreeNode* findLastRight(TreeNode* root) {
        if (root->right == NULL) {
            return root;
        }
        return findLastRight(root->right);
    }
};
