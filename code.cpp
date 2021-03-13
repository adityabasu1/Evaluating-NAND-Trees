/*********************************
 
    Creator: Aditya Basu
    Date: 11/3/21

*********************************/

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

#define TIMES 100

struct node
{
    bool val;
    struct node *left;
    struct node *right;
};

node *create_node(bool val)
{
    node *newnode = new node;
    newnode->val = val;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

// Number of leaves = 2^k
node *build_tree(int lev, int k)
{
    bool inp;
    node *root;

    if (lev == k)
    {
        cout << "Enter data: ";
        cin >> inp;
        root = create_node(inp);
        return root;
    }
    else if (lev < k)
    {
        cout << "Enter data: ";
        cin >> inp;
        root = create_node(inp);
        root->left = build_tree(lev + 1, k);
        root->right = build_tree(lev + 1, k);
        return root;
    }
}

node *build_random_tree(int lev, int k)
{
    bool inp;
    node *root;

    if (lev == k)
    {
        inp = rand() % 2;
        root = create_node(inp);
        return root;
    }
    else if (lev < k)
    {
        inp = rand() % 2;
        root = create_node(inp);
        root->left = build_random_tree(lev + 1, k);
        root->right = build_random_tree(lev + 1, k);
        return root;
    }
}

bool naive_eval_NAND(node *root)
{
    bool l, r, val;
    //at the leaf node
    if ((root->right) == NULL) // this also means root->left = NULL
        return root->val;

    l = naive_eval_NAND(root->left);
    r = naive_eval_NAND(root->right);
    val = !(l && r); // NAND operation
    return val;
}

// "root" should contain the value to which the NAND tree would evaluate to
//  root is essentially a pointer to that first node
void create_worst_tree(node *root, int lev, int k)
{
    if (lev < k)
    {
        if (root->val)
        {
            root->left = create_node(1);
            root->right = create_node(0);
            create_worst_tree(root->left, lev + 1, k);
            create_worst_tree(root->right, lev + 1, k);
            return;
        }
        else
        {
            root->left = create_node(1);
            root->right = create_node(1);
            create_worst_tree(root->left, lev + 1, k);
            create_worst_tree(root->right, lev + 1, k);
            return;
        }
    }
}

bool left_first(node *root)
{
    bool l, r, val;

    //at the leaf node
    if ((root->right) == NULL) // this also means root->left = NULL
        return root->val;

    l = naive_eval_NAND(root->left);
    if (l == 0)
        return 1;
    else
    {
        r = naive_eval_NAND(root->right);
        val = !(l && r); // NAND operation
        return val;
    }
}

bool random_eval_NAND(node *root)
{
    bool l, r, val, choice;
    if ((root->right) == NULL) // this also means root->left = NULL
        return root->val;

    choice = rand() % 2;
    if (choice == 0)
    {
        l = random_eval_NAND(root->left);
        if (l == 0)
            return 1;
        else
        {
            r = random_eval_NAND(root->right);
            val = !(l && r);
            return val;
        }
    }
    else
    {
        r = random_eval_NAND(root->right);
        if (r == 0)
            return 1;
        else
        {
            l = random_eval_NAND(root->left);
            val = !(l && r);
            return val;
        }
    }
}

double calc_time(clock_t tic, clock_t toc)
{
    double tym = (toc - tic) / double(CLOCKS_PER_SEC);
    return tym;
}

void compare_methods(node *root)
{
    bool val;
    clock_t tic, toc;
    double a1 = 0, a2 = 0, a3 = 0;

    for (int i = 0; i < TIMES; i++)
    {
        tic = clock();
        val = naive_eval_NAND(root);
        toc = clock();
        a1 = (a1 * i + calc_time(tic, toc)) / (i + 1);

        tic = clock();
        val = left_first(root);
        toc = clock();
        a2 = (a2 * i + calc_time(tic, toc)) / (i + 1);

        tic = clock();
        val = random_eval_NAND(root);
        toc = clock();
        a3 = (a3 * i + calc_time(tic, toc)) / (i + 1);
    }

    cout << "Naive recursive algorithm: " << a1 << " seconds" << endl;
    cout << "Left-first algorithm: " << a2 << " seconds" << endl;
    cout << "Random algorithm: " << a3 << " seconds" << endl;

    return;
}

void preOrder(node *root)
{
    if (root == NULL)
        return;

    cout << root->val << " ";
    preOrder(root->left);
    preOrder(root->right);
}

int main()
{
    int k;
    cout << "Enter k: ";
    cin >> k;

    srand(time(0));

    // node *WorstTreeZero = create_node(0);
    // create_worst_tree(WorstTreeZero, 0, k);

    // // cout<<endl;
    // // cout<<"Tree with root = 0 and "<<pow(2,k)<<" leaves: ";
    // // preOrder(WorstTreeZero);
    // // cout<<endl;

    // node *WorstTreeOne = create_node(1);
    // create_worst_tree(WorstTreeOne, 0, k);

    // // cout<<endl;
    // // cout<<"Tree with root = 1 and "<<pow(2,k)<<" leaves: ";
    // // preOrder(WorstTreeOne);
    // // cout<<endl;

    // cout << endl
    //      << endl
    //      << endl;
    // compare_methods(WorstTreeOne);
    // compare_methods(WorstTreeZero);
    // // cout<<naive_eval_NAND(WorstTreeZero)<<endl;
    // // cout<<naive_eval_NAND(WorstTreeOne)<<endl;
    // // cout<< left_first(WorstTreeZero)<<endl;
    // cout<<left_first(WorstTreeOne)<<endl;

    // cout<<random_eval_NAND(WorstTreeZero)<<endl;
    // cout<<random_eval_NAND(WorstTreeOne)<<endl;

    node *ND = build_random_tree(0,k);

    cout << endl << random_eval_NAND(ND) << endl;

    //compare_methods(ND);

    // cout<<endl;
    // cout<<"Tree with "<<pow(2,k)<<" leaves: ";
    // preOrder(ND);
    // cout<<endl;

    return 0;
}
