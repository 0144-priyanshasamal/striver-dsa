/*
1008. Construct Binary Search Tree from Preorder Traversal
Medium

Given an array of integers preorder, which represents the preorder traversal of a BST (i.e., binary search tree), construct the tree and return its root.

It is guaranteed that there is always compatible binary search tree for the given test cases.

A preorder traversal of a binary tree displays the value of the node first, then traverses the left subtree, then traverses the right subtree.

A binary search tree is a binary tree where for every node, any descendant of left subtree has a value strictly less than the node's value, and any descendant of right subtree has a value strictly greater than the node's value.

Example 1:
Input: preorder = [8,5,1,7,10,12]
Output: [8,5,10,1,7,null,12]

Example 2:
Input: preorder = [1,3]
Output: [1,null,3]

Constraints:
- 1 <= preorder.length <= 100
- 1 <= preorder[i] <= 1000
- All the values of preorder are unique.
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

class Solution {
public:
    TreeNode* bstFromPreorder(vector<int>& A) {
        int i=0;
        return build(A,i,INT_MAX);
    }
    TreeNode* build(vector<int>& A,int &i,int bound){
        if(i==A.size() || A[i]>bound) return nullptr;
        TreeNode* root = new TreeNode(A[i++]);
        root->left=build(A,i,root->val);
        root->right=build(A,i,bound);
        return root;
    }
};

/*
Explanation
*/
