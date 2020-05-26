/*
 * list_tests.cc
 * Test the doubly-linked list implementation
 */
#include <iostream>
#include <string>
#include <sstream>
#include "dlist.hpp"

/* verify(l)
   Double-check the structure of the list.
*/
bool verify(dlist& l) {
    using std::cout;    

    if((!l.head() && l.tail()) ||
       (l.head() && !l.tail())) {
        cout << "FAILED: If one of head/tail is null, both should be.\n";
        return false;
    }
    else if(l.head() == nullptr && l.tail() == nullptr) 
        return true; // Empty list
    else if(l.head() == l.tail()) {

        if(l.head() != l.tail()) {
            cout << "FAILED: One-element list with different head/tail.\n";
            return false;
        }
        else if(l.head()->next != nullptr) {
            cout << "FAILED: One-element list with head->next not null.\n";
            return false;
        }
        else if(l.head()->prev != nullptr) {
            cout << "FAILED: One-element list with head->prev not null.\n";
            return false;
        }
        else if(l.tail()->next != nullptr) {
            cout << "FAILED: One-element list with tail->next not null.\n";
            return false;
        }
        else if(l.tail()->prev != nullptr) {
            cout << "FAILED: One-element list with tail->prev not null.\n";
            return false;
        }
        return true; 
    }
    else {
        // Multi-element list: head has a non-null next, and tail has non-null
        // prev. 

        // Check outward-pointing pointers for nullness
        if(l.head()->prev != nullptr) {
            cout << "FAILED: Head->prev is non-null";
            return false;
        }
        else if(l.tail()->next != nullptr) {
            cout << "FAILED: Tail->next is non-null";
            return false;
        }

        // Check all internal pointers to make sure they line up.

        dlist::node*c = l.head()->next;
        while(c != l.tail()) {
            if(c->prev == nullptr) {
                cout << "FAILED: found internal node with ->prev == nullptr.\n";
                return false;
            }
            else if(c->next == nullptr) {
                cout << "FAILED: found non-tail node with ->next == nullptr.\n";
                return false;
            }
            else if(c->next->prev != c) {
                cout << "FAILED: n->next->prev does not point back to n.\n";
                return false;
            }
            else if(c->prev->next != c) {
                cout << "FAILED: n->prev->next does not point back to n.\n";
                return false;                
            }
            else if(c->prev == c->next) {
                cout << "FAILED: found a node where next == prev.\n";
                return false;
            }
            else if(c->prev == c) {
                cout << "FAILED: found a node n where n->prev = n itself. ";
                cout << "(value = " << c->value << ")\n";
                return false;
            }
            else if(c->next == c) {
                cout << "FAILED: found a node n where n->next == n itself.\n";
                cout << "(value = " << c->value << ")\n";
                return false;
            }

            c = c->next;
        }

        // Make sure we can traverse the list from both directions
        for(dlist::node* n = l.head(); n != l.tail(); n = n->next) {
            if(n == nullptr) {
                cout << "FAILED: could not walk from head to tail.\n";
                return false;
            }
        }
        for(dlist::node* n = l.tail(); n != l.head(); n = n->prev) {
            if(n == nullptr) {
                cout << "FAILED: could not walk from tail to head.\n";
                return false;
            }
        } 

        return true; // Everything OK!
    }
}

/*****************************************************************************
 * Test functions
 *****************************************************************************/

bool test_empty() {
    std::cout << "Checking empty list...\n";
    dlist e;
    if(!verify(e))
        return false;

    if(e.size() != 0) {
        std::cout << "FAILED: size of empty list is != 0.\n";
        return false;
    }

    if(!e.empty()) {
        std::cout << "FAILED: empty list is not .empty().\n";
        return false;
    }

    return true;
}

bool test_insert() {
    using std::cout;

    cout << "Checking .insert() into empty list...";
    dlist e;
    e.insert(e.head(), 100);
    if(!verify(e))
        return false;
    if(e.size() != 1) {
        cout << "FAILED: size != 1 after inserting 1 element.\n";
        return false;
    }
    cout << "OK\n";

    cout << "Checking .insert() method at head()...";
    dlist l1;
    for(int i = 0; i < 10; ++i) {
        cout << i << " ";

        l1.insert(l1.head(), i);
        if(!verify(l1))
            return false;

        if(l1.size() != i+1) {
            cout << "FAILED: size != " << i+1 << " after inserting " << 
                    i+1 << " elements.\n";
            return false;
        }        
    }
    cout << "OK" << std::endl;

    std::cout << "Checking .insert() at tail()...";    
    dlist l2;
    for(int i = 0; i < 10; ++i) {
        cout << i << " ";

        l2.insert(l2.tail(), i);
        if(!verify(l2))
            return false;

        if(l2.size() != i+1) {
            cout << "FAILED: size != " << i+1 << " after inserting " << 
                    i+1 << " elements.\n";
            return false;
        }
    }
    cout << "OK" << std::endl;

    std::cout << "Checking .insert() in the middle...";
    dlist l3;
    dlist::node* m = nullptr;
    for(int i = 0; i < 11; ++i) {
        cout << i << " ";

        l3.insert(l3.tail(), i); // We know this is safe
        if(i == 5)
            m = l3.head()->next; // Save pointer in the middle
    }    

    // Actually insert some values in the middle
    for(int i = 100; i < 120; ++i) {
        cout << i << " "; 

        l3.insert(m, i);
        if(!verify(l3))
            return false;
    }
    if(l3.size() != 11 + 20) {
        cout << "FAILED: size != 31 after inserting 31 elements.\n";
        return false;
    }
    cout << "OK" << std::endl;

    return true;
}

bool test_remove() {
    using std::cout;
    using std::endl;

    dlist::node* n = nullptr;
    dlist l;

    cout << "Checking remove from empty list...";
    dlist e;
    e.remove(nullptr); // This will most likely crash if it fails at all
    if(!verify(e))
        return false;
    cout << "OK" << endl;

    // We know that insert works at this point, so we use it to construct
    // the list, and we don't bother to verify.
    for(int i = 0; i < 30; ++i) {
        l.insert(l.head(), i);
        if(i == 15)
            n = l.head()->next; // Save pointer
    }

    cout << "Checking remove from the head...";
    for(int i = 0; i < 10; ++i) {
        cout << i << " ";

        l.remove(l.head());
        if(!verify(l))
            return false;
    }
    cout << "OK" << endl;

    cout << "Checking remove from the tail...";
    for(int i = 0; i < 10; ++i) {
        cout << i << " ";

        l.remove(l.tail());
        if(!verify(l))
            return false;
    }
    cout << "OK" << endl;

    cout << "Checking remove from the middle...";
    l.remove(n);
    if(!verify(l))
        return false;
    cout << "OK" << endl;

    return true;
}

bool test_push_back() {
    using std::cout;
    using std::endl;

    dlist e;

    cout << "Checking push_back...";
    for(int i = 0; i < 20; ++i) {
        cout << i << " ";
        e.push_back(i);
        if(!verify(e))
            return false;

        if(e.tail()->value != i) {
            cout << "FAILED: Tail != last push_back value.\n";
            return false;
        }
        if(e.size() != i+1) {
            cout << "FAILED: Size != # of push_backs.\n";
            return false;
        }
    }
    cout << "OK" << endl;

    cout << "Checking push_back order...";
    int i = 0;
    for(dlist::node* n = e.head(); n != nullptr; n = n->next) {
        if(n->value != i) {
            cout << "FAILED: Push_back'd elements are not in order.\n";
            return false;
        }
        cout << i << " ";
        ++i;
    }
    cout << "OK" << endl;

    return true;
}

bool test_push_front() {
    using std::cout;
    using std::endl;

    dlist e;

    cout << "Checking push_front...";
    for(int i = 0; i < 20; ++i) {
        cout << i << " ";
        e.push_front(i);
        if(!verify(e))
            return false;

        if(e.head()->value != i) {
            cout << "FAILED: Tail != last push_front value.\n";
            return false;
        }
        if(e.size() != i+1) {
            cout << "FAILED: Size != # of push_fronts.\n";
            return false;
        }
    }
    cout << "OK" << endl;

    cout << "Checking push_front order...";
    int i = 19;
    for(dlist::node* n = e.head(); n != nullptr; n = n->next) {
        if(n->value != i) {
            cout << "FAILED: Push_front'd elements are not in order.\n";
            return false;
        }
        cout << i << " ";
        --i;
    }
    cout << "OK" << endl;

    return true;
}

bool test_pop_front() {
    using std::cout;
    using std::endl;
    dlist e;

    cout << "Checking pop_front from empty list...";
    dlist l;
    l.pop_front();
    if(!verify(l))
        return false;
    cout << "OK" << endl;

    // Construct list using insert. 0-9
    for(int i = 0; i < 10; ++i)
        e.insert(e.tail(), i);

    cout << "Checking pop_front...";
    for(int i = 0; i < 10; ++i) {
        cout << i << " ";
        e.pop_front();
        if(!verify(e))
            return false;
        if(e.size() != 9-i) {
            cout << "FAILED: size incorrect after pop_front.\n";
            return false;
        }
    }
    cout << "OK" << endl;

    return true;
}

bool test_pop_back() {
    using std::cout;
    using std::endl;
    dlist e;

    cout << "Checking pop_back from empty list...";
    dlist l;
    l.pop_back();
    if(!verify(l))
        return false;
    cout << "OK" << endl;

    // Construct list using insert. 0-9
    for(int i = 0; i < 10; ++i)
        e.insert(e.tail(), i);

    cout << "Checking pop_back...";
    for(int i = 0; i < 10; ++i) {
        cout << i << " ";
        e.pop_back();
        if(!verify(e))
            return false;
        if(e.size() != 9-i) {
            cout << "FAILED: size incorrect after pop_back.\n";
            return false;
        }
    }
    cout << "OK" << endl;

    return true;
}

bool test_equal() {
    using std::cout;

    dlist a, b, c, e;

    cout << "Checking == operator...";

    for(int i = 0; i < 10; ++i) {
        a.push_back(i);
        b.push_back(i);
        c.push_back(i + 10);
    }

    if(!(a == b)) {
        cout << "FAILED: two equal lists are not ==.\n";
        return false;
    }

    if(a == c || a == e || e == a) {
        cout << "FAILED: two non-equal lists are ==.\n";
        return false;
    }

    // Test with lists of different lengths
    // Note that a and b are equal up to the last element!
    c.push_back(12); // Longer
    b.push_back(12);    
    if(a == c || a == b) {
        cout << "FAILED: two non-equal lists are ==.\n";
        return false;
    }

    // Shorter
    c.pop_back(); c.pop_back(); b.pop_back(); b.pop_back();
    if(a == c || a == b) {
        cout << "FAILED: two non-equal lists are ==.\n";
        return false;
    }

    if(!(a == a && b == b && c == c && e == e)) {
        cout << "FAILED: a list must be == to itself.\n";
        return false;
    }

    cout << "OK\n";

    return true;    

}

bool test_concat() {
    using std::cout;

    dlist a, b;

    cout << "Checking + operator...";

    for(int i = 0; i < 10; ++i) {
        a.push_back(i);
        b.push_back(i+10);
    }

    if(!verify(a) || !verify(b))
        return false;

    dlist c = a + b;
    if(!verify(c))
        return false;

    // Check to make sure all elements are present
    int i = 0;
    for(dlist::node* n = c.head(); n != nullptr; n = n->next) {
        cout << i << " ";
        if(n->value != i++) {
            cout << "FAILED: Result of + has the wrong element(s).\n";
            return false;
        }
    }

    cout << "OK\n";
    cout << "Checking operator + with empty lists...";

    // Check concat with the empty list
    dlist e;
    dlist a2 = a + e;

    if(!verify(a2))
        return false;

    i = 0;
    for(dlist::node* n = a.head(); n != nullptr; n = n->next) {
        cout << i << " ";
        if(n->value != i++) {
            cout << "FAILED: + with empty list has wrong element(s).\n";
            return false;
        }
    }

    a2 = e + a;
    i = 0;
    for(dlist::node* n = a.head(); n != nullptr; n = n->next) {
        cout << i << " ";
        if(n->value != i++) {
            cout << "FAILED: + with empty list has wrong element(s).\n";
            return false;
        }
    }

    dlist e2 = e + e;
    if(!verify(e2))
        return false;

    if(!e2.empty()) {
        cout << "FAILED: empty + empty is not empty!\n";
        return false;
    }

    cout << "OK\n";

    return true;
}

bool test_reverse() {
    using std::cout;

    dlist a, e;

    cout << "Checking reverse()...";

    dlist er = reverse(e);
    if(!verify(er))
        return false;

    if(!er.empty()) {
        cout << "FAILED: reverse() of the empty list is not empty!\n";
        return false;
    }

    for(int i = 0; i < 10; ++i)
        a.push_back(i);

    dlist ar = reverse(a);

    int i = 0, j = 9;
    for(dlist::node* m = a.head(), *n = ar.head(); 
        m != nullptr && n != nullptr; 
        m = m->next, n = n->next) {

        cout << i << " ";

        if(m->value != i++) {
            cout << "FAILED: reverse() must not modify its input!\n";
            return false;
        }
        if(n->value != j--) {
            cout << "FAILED: elements in reverse()'d list are incorrect.\n";
            return false;
        }
    }

    cout << "OK\n";

    if(!(reverse(reverse(a)) == a)) {
        cout << "FAILED: reverse()ing a list twice is not equal to itself.\n";
        return false;
    }

    return true;
}

int main() {

    std::cout << "*** Starting dlist tests ***" << std::endl;
    if(test_empty()      &&
       test_insert()     &&
       test_remove()     &&
       test_push_back()  &&
       test_push_front() &&
       test_pop_front()  &&
       test_pop_back()   &&
       test_equal()      &&
       test_concat()     && 
       test_reverse())
        std::cout << "*** All tests passed! ***" << std::endl;   

    return 0;
}