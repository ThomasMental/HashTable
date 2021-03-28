// initializes an empty hash table where the array has size s
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "C12.h"

int hash_function(struct hash T, int k)
{
    return k % T.size;
}

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
    tmp->key = index;
    tmp->value = value;
    tmp->next = NULL;

    struct anode *cur = T.table[k];

    if (cur == NULL) 
    {
        T.table[k] = tmp; 
    }
    else 
    {
        while(cur != NULL)
        {
            if(cur->key == k) 
            {
                cur->value = value;
                return;
            }
            cur = cur->next;
        }
        cur = tmp;
    }
}

// frees all heap-allocated memory used by T
void free_table(struct hash T)
{
    for (int i=0; i<T.size; i++)
    if(T.table[i] != NULL)
    {
        // frees an list
        struct anode *cur = T.table[i];
        while(cur != NULL)
        {
            free(cur);
            cur = cur->next;
        }
    }
    free(T.table);
}


void delete(struct hash T, int k)
{
    
}