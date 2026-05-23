/*
653. Two Sum IV - Input is a BST
Easy

Given the root of a binary search tree (BST) and a target number k, return true if there exist two elements in the BST such that their sum is equal to the given target.

Example 1:
Input: root = [5,3,6,2,4,null,7], k = 9
Output: true

Example 2:
Input: root = [5,3,6,2,4,null,7], k = 28
Output: false

Constraints:
- The number of nodes in the tree is in the range [1, 10^4].
- -10^4 <= Node.val <= 10^4
- root is guaranteed to be a valid binary search tree.
- -10^5 <= k <= 10^5
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

#include <stack>
using namespace std;

class BSTIterator {
private:
    stack<TreeNode*> myStack;
    bool reverse; // true for reverse inorder (right to left), false for normal inorder (left to right)

    void pushAll(TreeNode* node) {
        while (node != nullptr) {
            myStack.push(node);
            if (reverse) {
                node = node->right;
            } else {
                node = node->left;
            }
        }
    }

public:
    BSTIterator(TreeNode* root, bool isReverse) {
        reverse = isReverse;
        pushAll(root);
    }

    bool hasNext() {
        return !myStack.empty();
    }

    int next() {
        TreeNode* tmpNode = myStack.top();
        myStack.pop();
        if (reverse) {
            pushAll(tmpNode->left);
        } else {
            pushAll(tmpNode->right);
        }
        return tmpNode->val;
    }
};

class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        if (root == nullptr) return false;

        BSTIterator l(root, false); // Forward iterator: gives elements in ascending order
        BSTIterator r(root, true);  // Backward iterator: gives elements in descending order

        int i = l.next();
        int j = r.next();

        while (i < j) {
            if (i + j == k) {
                return true;
            } else if (i + j < k) {
                i = l.next();
            } else {
                j = r.next();
            }
        }

        return false;
    }
};
