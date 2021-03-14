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

/* A function to create a node with its data field equal to val

Parameters: 
val: a boolean. value to be stored in the val field of the node to be created

Returns:
A node pointer to the newly created node

Time complexity:
O(1) */
node *create_node(bool val)
{
    node *newnode = new node;
    newnode->val = val;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

/* Function to create a NAND tree of 2^k leaf nodes taking from the user 

Parameters: 
lev: a non-negative integer, denotes level of the tree at which the function is. passed as 0 when called for the first time
k: a non-negative integer, such that n = #leaf nodes = 2^k

Returns:
A node pointer to the random tree created

Time complexity:
O(n) i.e O(2^k) */
node *build_tree(int lev, int k)
{
    bool inp;
    node *root;

    if (lev == k) // at the level of leaves
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
        root->left = build_tree(lev + 1, k);  // recursively build left subtree
        root->right = build_tree(lev + 1, k); // recursively build right subtree
        return root;
    }
}

/* Function to create a random NAND tree of 2^k leaf nodes

Parameters: 
lev: a non-negative integer, denotes level of the tree at which the function is. passed as 0 when called for the first time
k: a non-negative integer, such that n = #leaf nodes = 2^k

Returns:
A node pointer to the random tree created

Time complexity:
O(n) i.e O(2^k) */
node *build_random_tree(int lev, int k)
{
    bool inp;
    node *root;

    if (lev == k) // at the level of leaves
    {
        //store a random value in the node
        inp = rand() % 2;
        root = create_node(inp);
        return root;
    }
    else if (lev < k)
    {
        //store a random value in the node
        inp = rand() % 2;
        root = create_node(inp);
        root->left = build_random_tree(lev + 1, k);  // recursively build left subtree
        root->right = build_random_tree(lev + 1, k); // recursively build right subtree
        return root;
    }
}

/* #EVALUATING A NAND TREE => Finding the value of the top-most node a.k.a root
A recursive algorithm to evaluate a NAND tree 
Parameters: 
root: a node pointer

Returns:
Value of the root (top-most node): a boolean

Time complexity:
Let n = #leaf nodes
O(n) */
bool naive_eval_NAND(node *root)
{
    bool l, r, val;

    /* Base case: we're at the leaf node
    this also means root->left = NULL */
    if ((root->right) == NULL)
        return root->val;

    l = naive_eval_NAND(root->left);
    r = naive_eval_NAND(root->right);
    val = !(l && r); // NAND operation
    return val;
}

/* A recursive algorithm to evaluate a NAND tree which uses "short-circuiting"
We always recurse on the left subtree first and short-circuit if the left subtree evaluates to 0
leveraging the property: O NAND X = 1 

Parameters: 
root: a node pointer

Returns:
Value of the root (top-most node): a boolean

Time complexity:
Let n = #leaf nodes
Worst-case: O(n) */
bool left_first(node *root)
{
    bool l, r, val;

    /* Base case: we're at the leaf node
    this also means root->left = NULL */
    if ((root->right) == NULL)
        return root->val;

    l = naive_eval_NAND(root->left); // always recurse on left first
    if (l == 0)
        return 1; // short-circuit
    else          // can't short-circuit
    {
        r = naive_eval_NAND(root->right);
        val = !(l && r); // NAND operation
        return val;
    }
}

/* PART 1 of the project:
A function to create a NAND tree of 2^k leaf nodes which serves as the worst-case when evaluated by left-first 
"root" should contain the value to which the NAND tree would evaluate to
 root is essentially a pointer to the first node (or the "topmost" node) 

Parameters: 
root: a node pointer containing the value to which the NAND tree would evaluate to (i.e root->val should be 0 or 1)
lev: a non-negative integer, denotes level of the tree at which the function is. passed as 0 when called for the first time
k: a non-negative integer, such that n = #leaf nodes = 2^k

Time complexity:
O(n) i.e O(2^k) */
void create_worst_tree(node *root, int lev, int k)
{
    if (lev < k)
    {
        if (root->val) // if the node value is 1
        {
            root->left = create_node(1);                // assign left child 1
            root->right = create_node(0);               // assign right child 0
            create_worst_tree(root->left, lev + 1, k);  // recursively creating left subtree
            create_worst_tree(root->right, lev + 1, k); // recursively creating right subtree
            return;
        }
        else // if the node value is 0
        {
            root->left = create_node(1);                // assign left child 1
            root->right = create_node(1);               // assign right child 1
            create_worst_tree(root->left, lev + 1, k);  // recursively creating left subtree
            create_worst_tree(root->right, lev + 1, k); // recursively creating right susbtree
            return;
        }
    }
}

/* PART 2 of the project:
A randomized recursive algorithm to evaluate a NAND tree which uses "short-circuiting" 
At each node, we choose one subtree(either left or right) RANDOMLY to recurse first
If that subtree evaluates to 0, we short-circuit leveraging the property: O NAND X = 1  

Parameters: 
root: a node pointer

Returns:
Value of the root: a boolean

Time complexity:
Let n = #leaf nodes
Sublinear in expectation i.e O(n^c) (0<c<1) */
bool random_first(node *root)
{
    bool l, r, val, choice;

    /* Base case: we're at the leaf node
    this also means root->left = NULL */
    if ((root->right) == NULL)
        return root->val;

    // making a random choice
    choice = rand() % 2;
    if (choice == 0) // if choice is 0, then recurse on left subtree first
    {
        l = random_first(root->left);
        if (l == 0)
            return 1; // short-circuit
        else          // can't short-circuit
        {
            r = random_first(root->right);
            val = !(l && r);
            return val;
        }
    }
    else // if choice is 1, then recurse on right subtree first
    {
        r = random_first(root->right);
        if (r == 0)
            return 1; // short-circuit
        else          // can't short-circuit
        {
            l = random_first(root->left);
            val = !(l && r);
            return val;
        }
    }
}

// A function to calculate the time elapsed
double calc_time(clock_t tic, clock_t toc)
{
    double tym = (toc - tic) / double(CLOCKS_PER_SEC);
    return tym;
}

/* A function to compare the three methods based on their running time of evaluation
We run each method TIMES (=100) number of times for the input and report the average running time */
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
        val = random_first(root);
        toc = clock();
        a3 = (a3 * i + calc_time(tic, toc)) / (i + 1);
    }

    cout << "Naive recursive algorithm: " << a1 << " seconds" << endl;
    cout << "Left-first algorithm: " << a2 << " seconds" << endl;
    cout << "Random-first algorithm: " << a3 << " seconds" << endl;
    return;
}

/* A function to carry out pre-order traversal of a tree

Parameters: 
root: a node pointer 

Time complexity: 
Let n = #nodes
O(n) */
void preOrder(node *root)
{
    if (root == NULL)
        return;

    // traversal order: node -> node.leftsubtree -> node.rightsubtree
    cout << root->val << " ";
    preOrder(root->left);
    preOrder(root->right);
}

/* PART 3 of the project:

Notation:
P0(k) is the probability that a random NAND tree of 2^k leaf nodes evaluates to 0
P1(k) is the probability that a random NAND tree of 2^k leaf nodes evaluates to 1

Mathematical reccurence:

P0(k) = P1(k-1) * P1(k-1) = (1 - P0(k-1)) * (1 - P0(k-1))
P1(k) = 1 - P0(k) = 1 - P1(k-1) * P1(k-1)

Underlying formula:
Since a node can evaluate to 0 or 1 only, thus, P0(k) + P1(k) = 1 */

/* This function computes the probability that a random NAND tree of 2^k leaf nodes evaluates to 1

Parameters: 
k: a non-negative integer such that n = #leaf nodes = 2^k

Returns:
a double equal, to P0(k)

Time complexity: 
O(k) i.e O(logn) */
double P1(int k)
{
    double val;

    // if only one node in the tree, then both 0 and 1 are equally likely
    if (k == 0)
        return 0.5;
    else
    {
        val = P1(k - 1);
        return (1 - pow(val, 2));
    }
}

/* This function computes the probability that a random NAND tree of 2^k leaf nodes evaluates to 0
We can leverage the fact that Po(k) + P1(k) = 1, and thus P0(k) = 1 - P1(k)
But, still a function to calculate P0(k) by NOT using the previous function P1(k) 

Parameters: 
k: a non-negative integer such that n = #leaf nodes = 2^k

Returns:
a double, equal to P0(k)

Time complexity: 
O(k) i.e O(logn) */
double P0(int k)
{
    double val;

    // if only one node in the tree, then both 0 and 1 are equally likely
    if (k == 0)
        return 0.5;
    else
    {
        val = P0(k - 1);
        return pow((1 - P0(k - 1)), 2);
    }
}

//This function will demonstrate convergence of probabilties of a random NAND tree
void convergence_random_NAND()
{
    int k_MAX = 20; // sufficient to observe convergence
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

    cout << "We see P0(k) and P1(k) converge:" << endl << endl;
    cout << "For odd values of k, P0(k) converges to 0 and P1(k) converges to 1" << endl;
    cout << "That is, given k is odd and high enough in magnitude, the random NAND tree will evaluate to 1 with high probability" << endl;
    cout << endl;
    cout << "And for even values of k, P0(k) converges to 1 and P1(k) converges to 0" << endl;
    cout << "That is, given k is even and high enough in magnitude, the random NAND tree will evaluate to 0 with high probability" << endl;
    cout << endl;

    return;
}

int main()
{
    // Taking input
    int k;
    cout << "Enter k: ";
    cin >> k;

    // to generate different random numbers each time
    srand(time(0));

    // creating worst case for left-first where the tree (with 2^k leaf nodes) evaluates to 0
    node *WorstTreeZero = create_node(0);
    create_worst_tree(WorstTreeZero, 0, k);

    // creating worst case for left-first where the tree (with 2^k leaf nodes) evaluates to 1
    node *WorstTreeOne = create_node(1);
    create_worst_tree(WorstTreeOne, 0, k); // 2^k leaf nodes

    /* To show how efficient our randomized algorithm is
        we compare naive_recursive, left-first and random-first */
    cout << endl;
    compare_methods(build_random_tree(0, k));
    cout << endl;

    // To demonstrate convergence of probabilities
    convergence_random_NAND();

    // cout<<endl;
    // cout<<"Tree with "<<pow(2,k)<<" leaves: ";
    // preOrder(ND);
    // cout<<endl;

    return 0;
}
