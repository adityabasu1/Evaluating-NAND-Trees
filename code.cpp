/*********************************
 
    EVALUATING NAND TREES
    Creator: Aditya Basu
    Date: 11/3/21

*********************************/

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

#define TIMES 100

// A node contains a boolean data field and pointers to its left and right child
struct node
{
    bool val;
    struct node *left;
    struct node *right;
};

// function to create a node with its data field equal to val
node *create_node(bool val)
{
    node *newnode = new node;
    newnode->val = val;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

// Function to create a NAND tree taking data input from the user 
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

// Function to create a random NAND tree of 2^k leaf nodes
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

// #EVALUATING A NAND TREE => Finding the value of the top-most node a.k.a root
// A recursive algorithm to evaluate a NAND tree
bool naive_eval_NAND(node *root)
{
    bool l, r, val;

    //Base case: we're at the leaf node
    // this also means root->left = NULL
    if ((root->right) == NULL) 
        return root->val;

    l = naive_eval_NAND(root->left);
    r = naive_eval_NAND(root->right);
    val = !(l && r); // NAND operation
    return val;
}

// A recursive algorithm to evaluate a NAND tree which uses "short-circuiting"
// We always recurse on the left subtree first and short-circuit if the left subtree evaluates to 0
// Leverage the property: O NAND X = 1
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

// A function to create a NAND tree of 2^k leaf nodes which serves as the worst-case when evaluated by left-first 
// "root" should contain the value to which the NAND tree would evaluate to
//  root is essentially a pointer to the first node (or the "topmost" node)
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


// A randomized recursive algorithm to evaluate a NAND tree which uses "short-circuiting" 
// At each node, we choose one subtree(either left or right) RANDOMLY to recurse first
// If that subtree evaluates to 0, we short-circuit leveraging the property: O NAND X = 1 
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

// function to carry out pre-order traversal of a tree
void preOrder(node *root)
{
    if (root == NULL)
        return;

    cout << root->val << " ";
    preOrder(root->left);
    preOrder(root->right);
}

// Number of leaves = 2^k
// This function computes the probability that a random NAND tree of 2^k leaf nodes evaluates to 1
double P1(int k)
{
    double val;

    if (k == 0)
        return 0.5;
    else
    {
        val = P1(k - 1);
        return (1 - pow(val, 2));
    }
}

// Number of leaves in the random NAND tree = 2^k
// This function computes the probability that a random NAND tree of 2^k leaf nodes evaluates to 0
// We can leverage the fact that Po(k) + P1(k) = 1, and thus P0(k) = 1 - P1(k)
// But, still a function to calculate P0(k) by NOT using the previous function P1(k)
double P0(int k)
{
    double val;

    if (k == 0)
        return 0.5;
    else
    {
        val = P0(k - 1);
        return pow((1 - P0(k - 1)), 2);
    }
}

// This function will demonstrate convergence of probabilties
void convergence_random_NAND()
{
    int k_MAX = 20;
    double p_0, p_1;

    cout << "For reference: " << endl;
    cout << "P0(k) is the probability that a random NAND tree of 2^k leaf nodes evaluates to 0" << endl;
    cout << "P1(k) is the probability that a random NAND tree of 2^k leaf nodes evaluates to 1" << endl;
    cout << endl;
    for (int i = 0; i <= k_MAX; i++)
    {
        p_1 = P1(i);
        p_0 = 1 - p_1;
        cout << "P0(" << i << "): " << p_0 << endl;
        cout << "P1(" << i << "): " << p_1 << endl;
        cout << endl;
    }

    cout << endl << "We see P0(k) and P1(k) converge" << endl << endl;
    cout << "For odd values of k, P0(k) converges to 0 and P1(k) converges to 1" << endl;
    cout << "That is, given k is odd and high enough in magnitude, the random NAND tree will most likely evaluate to 1" << endl;
    cout << endl;
    cout << "And for even values of k, P0(k) converges to 1 and P1(k) converges to 0" << endl;
    cout << "That is, given k is even and high enough in magnitude, the random NAND tree will most likely evaluate to 0" << endl;
    cout<<endl;

    return;
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

    node *ND = build_random_tree(0, k);

    cout << random_eval_NAND(ND) << endl;

    convergence_random_NAND();

    //compare_methods(ND);

    // cout<<endl;
    // cout<<"Tree with "<<pow(2,k)<<" leaves: ";
    // preOrder(ND);
    // cout<<endl;

    return 0;
}
