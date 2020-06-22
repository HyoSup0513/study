#include <iostream>
using namespace std;

#define MAX_SIZE 10                  // Maximum size of hash table
#define HASH_KEY(key) key % MAX_SIZE // Key value for hash table

typedef struct Node
{
    int key;
    int data;
    Node *next;
};

Node *hashTable[MAX_SIZE];
Node *item;

void insert(int key, int data, Node *node)
{
    int hash_key = HASH_KEY(key);
    if (hashTable[hash_key] == NULL)
    {
        hashTable[hash_key] = node;
        node->data = data;
    }
    else
    {
        node->next = hashTable[hash_key];
        hashTable[hash_key] = node;
        node->data = data;
    }
}

void deleteData(int key)
{
    int hash_key = HASH_KEY(key);
    if (hashTable[hash_key] == NULL)
        return;

    Node *delNode = NULL;
    if (hashTable[hash_key]->key == key)
    {
        delNode = hashTable[hash_key];
        hashTable[hash_key] = hashTable[hash_key]->next;
    }

    else
    {
        Node *node = hashTable[hash_key];
        Node *next_node = node->next;
        while (next_node)
        {
            if (next_node->key == key)
            {
                node->next = next_node->next;
                delNode = next_node;
                break;
            }
            node = next_node;
            next_node = node->next;
        }
    }
    free(delNode);
}

Node *search(int key)
{
    int hash_key = HASH_KEY(key);
    if (hashTable[hash_key] == NULL)
        return NULL;

    if (hashTable[hash_key]->key == key)
    {
        return hashTable[hash_key];
    }
    else
    {
        Node *node = hashTable[hash_key];
        while (node->next)
        {
            if (node->next->key == key)
            {
                return node->next;
            }
            node = node->next;
        }
    }
    return NULL;
}

void display()
{
    cout << "Display Hash Table" << endl;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        cout << "index:" << i << " = ";

        if (hashTable[i] != NULL)
        {
            Node *node = hashTable[i];
            while (node->next)
            {
                cout << node->data << " ";
                node = node->next;
            }
            cout << node->data;
        }
        cout << endl;
    }
    cout << endl
         << endl;
}

int main()
{
    int arraydata[10] = {100, 165, 213, 224, 317, 325, 439, 413, 455, 514};
    int arraykey[10] = {1, 2, 40, 5, 12, 14, 17, 13, 37};
    for (int i = 0; i < 10; i++)
    {
        Node *node = (Node *)malloc(sizeof(Node));
        node->key = arraykey[i];
        node->data = arraydata[i];
        node->next = NULL;
        insert(node->key, node->data, node);
    }
    display();

    item = search(1);
    if (item != NULL)
    {
        cout << "Element found: "
             << "Key:" << item->key << " Data:" << item->data << endl;
    }
    else
    {
        cout << "Element not found: " << endl;
    }

    for (int i = 0; i < 10; i++)
    {
        deleteData(arraykey[i]);
    }
    display();

    return 0;
}