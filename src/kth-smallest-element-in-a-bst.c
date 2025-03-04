/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int kthSmallest(struct TreeNode* root, int k) {

    while(root && root->left != NULL)
    {
        root = root->left;
    }
    return root->val + k -1;
}