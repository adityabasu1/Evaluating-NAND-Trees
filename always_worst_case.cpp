// Implementing first problem statement of the project

#include <iostream>

using namespace std;

struct tree
{
    int val;
    struct tree *left;
    struct tree *right;
};

struct tree *make_tree(int value, int k, int i)
{
    struct tree *node = new tree;
    node->val = value;
    node->left = NULL;
    node->right = NULL;
    if (i == k)
        return node;
    int v = 1;
    node->left = make_tree(v, k, i + 1);
    if (value == 1)
        v = 0;
    node->right = make_tree(v, k, i + 1);
    return node;
}

void print(struct tree *root)
{
    if (root == NULL)
        return;
    cout << root->val << " ";
    print(root->left);
    print(root->right);
}

int main()
{
    int k;
    cin >> k;
    int val = 0, i = 0;
    struct tree *root = make_tree(val, k, i);
    print(root);
    return 0;
}
