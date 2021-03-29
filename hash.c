#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "C12.h"

// get the index of key k
int hash_function(struct hash T, int k)
{
    return k % T.size;
}

// initializes an empty hash table where the array has size s
struct hash make_table(int s) 
{
    struct hash T;
    T.size = s;
    T.table = (struct anode**)malloc(sizeof(struct anode)*s);
    for (int i=0; i<T.size; i++)
        T.table[i] = NULL;
    return T;
}

// searches for the string associated with key k in table T
char *search(struct hash T, int k)
{
    int index = hash_function(T, k);
    struct anode *cur = T.table[index];
    while(cur != NULL)
    {
        if(cur->key == k)
            return cur->value;

        cur = cur->next;
    }
    return NULL;
}

// stores in T the key k with associated string value v
void add(struct hash T, int k, char *v)
{
    int index = hash_function(T, k);

    // create the anode
    struct anode *tmp = (struct anode*)malloc(sizeof(struct anode));
    char *value = (char*)malloc(sizeof(char)*strlen(v));
    strcpy(value,v);
    tmp->key = k;
    tmp->value = value;
    tmp->next = NULL;

    struct anode *cur = T.table[index];
    
    if (cur == NULL) 
    {
        T.table[index] = tmp; 
    }
    else 
    {
        // if exists then replace the value
        while(cur != NULL)
        {
            if(k == cur->key)
            {
                free(cur->value);
                free(tmp);
                cur->value = value;
                return;
            }
            cur = cur->next;
        }
        // otherwise put the anode 
        tmp->next = T.table[index];
        T.table[index] = tmp; 
    }
}

// frees all heap-allocated memory used by T
void free_table(struct hash T)
{
    for (int i=0; i<T.size; i++)
    if(T.table[i] != NULL)
    {
        // frees the linked list
        struct anode *cur = T.table[i];
        while(cur != NULL)
        {
            free(cur->value);
            free(cur);
            cur = cur->next;
        }
    }
    free(T.table);
}

// delete the key k from the hash table T
void delete(struct hash T, int k)
{
    int index = hash_function(T, k);
    struct anode *cur = T.table[index];
    struct anode *prev;

    // delete the head node if itself holds the k
    if(cur != NULL)
    if(cur->key == k)
    {
        free(cur->value);
        free(cur);
        T.table[index] = cur->next;
        return;
    }

    // search for the key to be deleted
    while(cur != NULL)
    {
        if(cur->key == k)
        {
            break;
        }
        prev = cur;
        cur = cur->next;
    }

    // if k is not present in linked list
    if(cur == NULL)
        return;

    prev->next = cur->next;
    free(cur->value);
    free(cur);
}
