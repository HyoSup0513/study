#pragma once
/*
  dlist.h
  Doubly-linked lists of ints
 */
class dlist {
public:
    dlist() { }

    struct node {
        int value;
        node* next;
        node* prev;
    };

    node* head() const { return _head; }
    node* tail() const { return _tail; }

    // **** Implement ALL the following methods ****

    // Returns the node at a particular index (0 is the head). If n >= size()
    // return nullptr; if n < 0, return the head of the list.
    // Must run in O(n) time.
    node* at(int n) const;

    // Insert a new value, after an existing one. If previous == nullptr, then
    // the list is assumed to be empty.
    // Must run in O(1) time.
    void insert(node* previous, int value);

    // Delete the given node. Should do nothing if which == nullptr.
    // Must run in O(1) time.
    void remove(node* which);

    // Add a new element to the *end* of the list
    // Must run in O(1) time.
    void push_back(int value);

    // Add a new element to the *beginning* of the list
    // Must run in O(1) time.
    void push_front(int value);

    // Remove the first element
    // Must run in O(1) time
    void pop_front();

    // Remove the last element
    // Must run in O(1) time
    void pop_back();

    // Get the size of the list
    // Should run in O(n) time at the worst
    int size() const;

    // Returns true if the list is empty
    // Must run in O(1) time
    bool empty() const;

private:
    node* _head = nullptr;
    node* _tail = nullptr;
};

// **** Implement ALL the following functions ****

/* a == b
   Compares two lists for equality, returning true if they have the same
   elements in the same positions. (Hint: it is *not* enough to just compare
   pointers! You have to compare the values stored in the nodes.)

   Must run in O(m) time, where m is the length of the shorter of the two lists.
*/
bool operator== (const dlist& a, const dlist& b) {
    dlist::node* tempA = a.head();
    dlist::node* tempB = b.head();

    if (a.size() != b.size())
        return false;
    else {
        while (tempA != nullptr)
        {
            if (tempA->value != tempB->value)
                return false;
            else {
                tempA = tempA->next;
                tempB = tempB->next;
            }
        }
        return true;
    }
};

/* a + b
   Returns a new list consisting of all the elements of a, followed by all the
   elements of b (i.e., the list concatenation).

   Must run in O(n) time in the length of the result.
*/
dlist operator+ (const dlist& a, const dlist& b) {
    dlist::node* tempB = b.head();
    dlist::node* tempA = a.head();
    dlist c;
    while (tempA != nullptr)
    {
        c.push_back(tempA->value);
        tempA = tempA->next;
    }
    while (tempB != nullptr)
    {
        c.push_back(tempB->value);
        tempB = tempB->next;
    }

    return c;
};

/* reverse(l)
   Returns a new list that is the *reversal* of l; that is, a new list
   containing the same elements as l but in the reverse order.

   Must run in O(n) time.
*/
dlist reverse(const dlist& l) {
    dlist::node* tempA = l.tail();
    dlist c;
    while (tempA != nullptr)
    {
        c.push_back(tempA->value);
        tempA = tempA->prev;
    }

    return c;
};