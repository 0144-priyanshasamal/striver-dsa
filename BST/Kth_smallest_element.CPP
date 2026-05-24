class Solution {
public:
    
    void inorder(TreeNode* root, vector<int>& arr) {
        if (root == NULL)
            return;

        inorder(root->left, arr);
        arr.push_back(root->val);
        inorder(root->right, arr);
    }

    vector<int> kthSmallLarge(TreeNode* root, int k) {
        vector<int> arr;

        // Store BST elements in sorted order
        inorder(root, arr);

        int kthSmallest = arr[k - 1];
        int kthLargest = arr[arr.size() - k];

        return {kthSmallest, kthLargest};
    }
};
