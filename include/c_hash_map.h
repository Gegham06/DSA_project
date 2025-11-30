#ifndef C_HASH_MAP
#define C_HASH_MAP

typedef struct hash_node {
    char *key;
    char *value;
    struct hash_node *next;
} HashNode;

typedef struct hash_map {
    int capacity;          
    HashNode **buckets;    
} HashMap;

HashMap *create_hash_map(int capacity);
void destroy_hash_map(HashMap *map);
int hash_map_insert(HashMap *map, const char *key, const char *value);
char *hash_map_get(HashMap *map, const char *key);
int hash_map_delete(HashMap *map, const char *key);
unsigned int hash_function(const char *key);

#endif
