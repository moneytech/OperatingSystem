#pragma once
#include "types.h"

#define HASH_CUMULATIVE 0
#define HASH_AND 1

struct _hashtable_node
{
    struct _hashtable_node* next;
    uint64_t* key;
    uint64_t keysize;
    void* data;
};

// Since the hash list won't allocate memory for nodes, the node struct
// must be contained in the object and it will reference itself. ie:
//    object->hashtable_node->data = object;

typedef struct _hashtable_node hashtable_node;

typedef struct
{
    hashtable_node* node;
    uint64_t lock;
} hashtable_bucket;
    

struct _hashtable
{
    uint64_t (*hash_function)(struct _hashtable*, uint64_t keysize, uint64_t* key);
    unsigned char keysize;
    hashtable_bucket buckets[];
} _hashtable;

typedef struct _hashtable hashtable;

typedef void (*hashtable_visitor)(void* data, void* meta);
typedef bool (*hashtable_clean_visitor)(void* data, void* meta);

// The hashtable code will not reserve memory for the hashtable. 
// You must determine the size of the hashtable with hashtable_getrequiredsize()
// and then create a buffer of that size and pass it to hashtable_init to it
// can initialize it. 
uint64_t hashtable_getrequiredsize(unsigned char hashsize);
void hashtable_init(hashtable*,unsigned char hashsize,unsigned char hash_function);
void hashtable_add(hashtable*,uint64_t keysize, uint64_t* key, hashtable_node* node);
void hashtable_remove(hashtable*,uint64_t keysize, uint64_t* key);
void* hashtable_get(hashtable*,uint64_t keysize, uint64_t* key);
bool hashtable_visit(hashtable*,uint64_t keysize, uint64_t* key,hashtable_visitor visitor, void* meta);
void hashtable_scan_and_clean(hashtable*, hashtable_clean_visitor visitor, void* meta);
