#include "include/c_hash_map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Function: create_hash_map
 * -------------------------
 * Allocates and initializes a new hash map with the given capacity.
 *
 * capacity: number of buckets for the hash map
 *
 * returns: pointer to the created HashMap, or NULL if allocation fails
 */
HashMap *create_hash_map(int capacity){
    if (capacity <= 0) return NULL;

    HashMap *map = malloc(sizeof(HashMap));
    if (map == NULL) return NULL;

    map->capacity = capacity;
    map->buckets = calloc(capacity, sizeof(HashNode*));
    if (map->buckets == NULL){
        free(map);
        return NULL;
    } 
    return map;
}

/*
 * Function: destroy_hash_map
 * --------------------------
 * Frees all memory allocated for the hash map, including all keys, values, and nodes.
 *
 * map: pointer to the HashMap to destroy
 *
 * returns: void
 */
void destroy_hash_map(HashMap *map){
    for (int i = 0; i < map->capacity; i++){
        HashNode *node = map->buckets[i];
        while (node != NULL){
            HashNode *next = node->next;
            free(node->value); // Free value string
            free(node->key);   // Free key string
            free(node);        // Free node
            node = next;
        } 
    }
    free(map->buckets);
    free(map);
}

/*
 * Function: hash_function
 * -----------------------
 * Computes a hash value for a given string key using a variation of the djb2 algorithm.
 *
 * key: string to hash
 *
 * returns: unsigned int hash value
 */
unsigned int hash_function(const char *key){
    unsigned int hash = 5186;
    int c;
    while ((c = *key++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash;
}

/*
 * Function: hash_map_insert
 * -------------------------
 * Inserts a key-value pair into the hash map.
 * If the key already exists, updates its value.
 *
 * map: pointer to the HashMap
 * key: string key
 * value: string value
 *
 * returns: 0 if new key inserted, 1 if value updated, -1 on error
 */
int hash_map_insert(HashMap *map, const char *key, const char *value){
    if (map == NULL || key == NULL || value == NULL) return -1;

    unsigned int hashing_value = hash_function(key);
    int index = (int)(hashing_value % map->capacity);

    HashNode *current_node = map->buckets[index];

    // Check if key already exists
    while (current_node != NULL){
        if (strcmp(current_node->key, key) == 0){
            char *new_val = strdup(value);
            if (new_val == NULL) return -1; 
            free(current_node->value); 
            current_node->value = new_val; // Update existing value
            return 1; 
        }
        current_node = current_node->next;
    }

    // Key not found, create new node
    HashNode *node = malloc(sizeof(HashNode));
    if (node == NULL) return -1;
    node->key = strdup(key);
    node->value = strdup(value);
    node->next = NULL;

    if(node->value == NULL || node->key == NULL){
        free(node->key);
        free(node->value);
        free(node);
        return -1;
    }

    // Insert node at the beginning of the bucket
    map->buckets[index] = node;
    return 0;
}

/*
 * Function: hash_map_get
 * ----------------------
 * Retrieves the value associated with a key in the hash map.
 *
 * map: pointer to the HashMap
 * key: string key
 *
 * returns: pointer to value string, or NULL if key not found
 */
char *hash_map_get(HashMap *map, const char *key){
    if (map == NULL || key == NULL) return NULL;

    unsigned int hashing_value = hash_function(key);
    int index = (int)(hashing_value % map->capacity);

    HashNode *current_node = map->buckets[index];

    while (current_node != NULL){
        if (strcmp(current_node->key, key) == 0){
            return current_node->value;
        }
        current_node = current_node->next;
    }
    return NULL;
}

/*
 * Function: hash_map_delete
 * -------------------------
 * Deletes a key-value pair from the hash map if it exists.
 *
 * map: pointer to the HashMap
 * key: string key
 *
 * returns: 1 if key was found and deleted, 0 if key not found, -1 on error
 */
int hash_map_delete(HashMap *map, const char *key){
    if (map == NULL || key == NULL) return -1;

    unsigned int hashing_value = hash_function(key);
    int index = (int)(hashing_value % map->capacity);

    HashNode **current_node_pointer = &map->buckets[index];

    while (*current_node_pointer != NULL){
        HashNode *next = (*current_node_pointer)->next;
        if (strcmp((*current_node_pointer)->key, key) == 0){
            HashNode *to_delete = *current_node_pointer;
            *current_node_pointer = (*current_node_pointer)->next; // Remove node from list
            free(to_delete->key);
            free(to_delete->value);
            free(to_delete);
            return 1; // Key found and deleted
        }
        current_node_pointer = &(*current_node_pointer)->next;
    }
    return 0; // Key not found
}
