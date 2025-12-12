#include "hash_map/c_hash_map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void destroy_hash_map(HashMap *map){
    for (int i = 0; i < map->capacity; i++){
        HashNode *node = map->buckets[i];
        while (node != NULL){
            HashNode *next = node->next;
            free(node->value);
            free(node->key);
            free(node);
            node = next;
        } 
    }
    free(map->buckets);
    free(map);
    return;
}

unsigned int hash_function(const char *key){
    unsigned int hash = 5186;
    int c;
    while ((c = *key++))
        hash = ((hash << 5) + hash) + c; 
    return hash;
}

int hash_map_insert(HashMap *map, const char *key, const char *value){
    if (map == NULL || key == NULL || value == NULL) return -1;
    unsigned int hashing_value = hash_function(key);
    int index = (int)(hashing_value % map->capacity);

    HashNode *current_node = map->buckets[index];

    while (current_node != NULL){
        if (strcmp(current_node->key, key) == 0){
            char *new_val = strdup(value);
            if (new_val == NULL) return -1; 
            free(current_node->value);
            current_node->value = new_val;
            return 1; 
        }
        current_node = current_node->next;
    }

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
    node->next = map->buckets[index];
    map->buckets[index] = node;
    return 0;
}

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

int hash_map_delete(HashMap *map, const char *key){
    if (map == NULL || key == NULL) return -1;

    unsigned int hashing_value = hash_function(key);
    int index = (int)(hashing_value % map->capacity);

    HashNode **current_node_pointer = &map->buckets[index];

    while (*current_node_pointer != NULL){
        HashNode *next = (*current_node_pointer)->next;
        if (strcmp((*current_node_pointer)->key, key) == 0){
            HashNode *to_delete = *current_node_pointer;
            *current_node_pointer = (*current_node_pointer)->next;
            free(to_delete->key);
            free(to_delete->value);
            free(to_delete);
            return 1; // find and delete
        }
        current_node_pointer = &(*current_node_pointer)->next;
    }
    return 0; //don't find ,just check and return nothing
}