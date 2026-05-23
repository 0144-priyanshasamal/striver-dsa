/*
Largest BST in Binary Tree
Medium

Given a binary tree. Find the size of the largest subtree which is a Binary Search Tree (BST).
Note: Here Size is equal to the number of nodes in the subtree.

Example 1:
Input:
      1
    /   \
   4     4
  / \
 6   8
Output: 1
Explanation: There's no sub-tree with size greater than 1 which forms a BST. All the leaf nodes are BSTs of size 1.

Example 2:
Input:
      10
    /    \
   5      15
  / \    /  \
 1   8  null 7
Output: 3
Explanation: The subtree rooted at 5 is a BST and its size is 3 (nodes: 5, 1, 8).

Constraints:
- The number of nodes in the tree is in the range [1, 10^5].
- -10^5 <= Node.val <= 10^5
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

#include <climits>
#include <algorithm>
using namespace std;

class NodeValue {
public:
    int minNode, maxNode, maxSize;
    
    NodeValue(int minNode, int maxNode, int maxSize) {
        this->minNode = minNode;
        this->maxNode = maxNode;
        this->maxSize = maxSize;
    }
};

class Solution {
private:
    NodeValue largestBSTHelper(TreeNode* root) {
        // An empty tree is a BST of size 0.
        // We use INT_MAX for minNode and INT_MIN for maxNode so that
        // the BST property condition at leaf nodes is always satisfied.
        if (root == nullptr) {
            return NodeValue(INT_MAX, INT_MIN, 0);
        }
        
        // Post-order traversal: check left and right subtrees
        auto left = largestBSTHelper(root->left);
        auto right = largestBSTHelper(root->right);
        
        // If current node is greater than the max on the left 
        // and smaller than the min on the right, it is a valid BST!
        if (root->val > left.maxNode && root->val < right.minNode) {
            return NodeValue(
                min(root->val, left.minNode),
                max(root->val, right.maxNode),
                1 + left.maxSize + right.maxSize
            );
        }
        
        // Otherwise, it cannot be a valid BST.
        // Return [-infinity, infinity] so that any parent node above fails the BST property check,
        // but carry up the maximum BST size found in the subtrees so far.
        return NodeValue(INT_MIN, INT_MAX, max(left.maxSize, right.maxSize));
    }

public:
    int largestBST(TreeNode* root) {
        return largestBSTHelper(root).maxSize;
    }
};
