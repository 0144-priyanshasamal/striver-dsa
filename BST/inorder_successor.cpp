/*
285. Inorder Successor in BST
Medium

Given the root of a binary search tree (BST) and a node p in it, return the in-order successor of that node in the BST. If the given node has no in-order successor in the tree, return null.

The successor of a node p is the node with the smallest key greater than p.val.

Example 1:
Input: root = [2,1,3], p = 1
Output: 2

Example 2:
Input: root = [5,3,6,2,4,null,null,1], p = 6
Output: null

Constraints:
- The number of nodes in the tree is in the range [1, 10^4].
- -10^5 <= Node.val <= 10^5
- All Nodes have unique values.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        // Write your code here
        TreeNode* successor=NULL;
        while(root != NULL){
            if(p->val >=root->val){
                root=root->right;
            }else{
                successor = root;
                root=root->left;
            }
        
        }
        return successor;
    }
};
