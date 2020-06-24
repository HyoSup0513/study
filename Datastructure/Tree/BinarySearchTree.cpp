#include <iostream>
#include <climits> // For INT_MIN, INT_MAX
using namespace std;

struct node
{
    int key;
    node *left;
    node *right;
};

bool is_bst(node *n, int low = INT_MIN, int high = INT_MAX);
node *find(node *n, int k);
node *find_parent(node *n, int k);
node *insert(node *n, int k);
bool exists(node *n, int k);
node *min(node *n);
node *max(node *n);
void print_in_order(node *n);
void delete_tree(node *n);

/*
   Returns true if n is the root of a valid BST where all keys in the tree are
   greater than low and less than high.
*/
bool is_bst(node *root, int low, int high)
{
    if (!root)
    {
        return true;
    }
    else if (root->key <= low || root->key >= high)
    {
        return false; // Out of bounds
    }
    else
        return is_bst(root->left, low, root->key) &&
               is_bst(root->right, root->key, high);
}

/*
   Insert k into the tree rooted at n. Returns the root of a "new" tree
   containing k. If k is already present in the tree, then this should leave the
   tree unchanged.
*/
node *insert(node *root, int key)
{
    if (root == nullptr)
        return new node{key, nullptr, nullptr};
    else if (root->key == key)
        return root;
    else if (key < root->key)
        root->left = insert(root->left, key);
    else // key > root->key
        root->right = insert(root->right, key);
    return root;
}

/*
   Finds the parent node (node directly above) the node containing key k, or if
   k is not in the tree, returns the node above the location where k should be
   added.
*/
node *find_parent(node *n, int k)
{ // n != nullptr
    node *p = nullptr;

    while (n != nullptr && n->key != k)
    {
        p = n;
        n = k < n->key ? n->left : n->right;
    }

    return p;
}

// Find k in the tree rooted at n.
// Returns a pointer to the node whose key is k, if it exists, or nullptr if it does not.
node *find(node *root, int key)
{
    if (!root)
        // Empty tree, or not found
        return root;
    else if (root->key == key)
        return root;
    else if (root->key < key)
        return find(root->right, key);
    else if (root->key > key)
        return find(root->left, key);
}

// Returns true if k exists in the tree rooted at n.
bool exists(node *n, int k)
{
    return find(n, k) != nullptr;
}

// Returns the node with the smallest key in the tree rooted at n.
node *min(node *n)
{ // n != nullptr.
    while (n->left != nullptr)
        n = n->left;
    return n;
}

// Returns the node with the largest key in the tree rooted at n.
node *max(node *n)
{ // n != nullptr.
    while (n->right != nullptr)
        n = n->right;
    return n;
}

void print_in_order(node *n)
{
    if (n == nullptr)
    {
        return;
    }
    else
    {
        print_in_order(n->left);
        cout << n->key << " ";
        print_in_order(n->right);
    }
}

// Delete (free all the nodes) the tree rooted at n.
void delete_tree(node *n)
{
    if (n == nullptr)
    {
        return;
    }
    else
    {
        delete_tree(n->left);
        delete_tree(n->right);
        delete n;
    }
}

int main()
{
    node *t = nullptr;
    t = insert(t, 5);
    t = insert(t, 6);
    t = insert(t, 3);
    t = insert(t, 10);
    t = insert(t, 8);
    t = insert(t, 2);
    t = insert(t, 4);
    t = insert(t, 1);
    t = insert(t, 7);
    print_in_order(t);

    cout << endl;
    cout << is_bst(t, 0, 100);

    delete_tree(t);
}