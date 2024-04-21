#include "key_val_list.h"
// implementation of a hash map using a hash table and linked list of key value pairs

#ifndef HASH_MAP_H
#define HASH_MAP_H

// 10 is a very modest number for the size of the hash map
// typically a large prime number is used for the size of the hash map
#define HASH_MAP_SIZE 10

typedef struct
{
    key_val_list table[HASH_MAP_SIZE];
    size_t size;
} hash_map;

hash_map *hash_map_create()
{
    hash_map *map = (hash_map *)malloc(sizeof(hash_map));
    if (map == NULL)
    {
        return NULL;
    }
    map->size = 0;
    for (int i = 0; i < HASH_MAP_SIZE; i++)
    {
        map->table[i] = key_val_list_create();
    }
    return map;
}

void hash_map_destroy(hash_map *map)
{
    if (map == NULL)
    {
        return;
    }
    for (int i = 0; i < HASH_MAP_SIZE; i++)
    {
        // either one of the following lines will work
        // key_val_list_destroy(&map->table[i]);
        key_val_list_destroy(map->table + i);
    }
    free(map);
}

// this is a very simple hash function using "polynomial rolling"
// it is not a very good hash function, but it is simple and works for our purposes
size_t hash(char *key, size_t table_size)
{
    size_t hash = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        hash = 31 * hash + key[i];
    }
    return hash % table_size;
}

int hash_map_add(hash_map *map, char *key, int value)
{
    // add a new key value pair to the map
    // if the map is NULL, return -1
    if (map == NULL)
    {
        return -1;
    }
    // if the key already exists, return -2
    key_val_list_node *current = map->table->head;
    while (current != NULL)
    {
        if (strcmp(current->data.key, key) == 0)
        {
            return -2;
        }
        current = current->next;
    }
    // if we failed to allocate memory, return -3
    key_val_list_node *new_node = malloc(sizeof(key_val_list_node));
    if (new_node == NULL)
    {
        return -3;
    }

    strncpy(new_node->data.key, key, MAX_KEY_LEN - 1);
    new_node->data.key[MAX_KEY_LEN - 1] = '\0';

    new_node->data.value = value;
    new_node->next = NULL;

    if (map->size == 0)
    {
        map->table->head = new_node;
        map->table->tail = new_node;
    }
    else
    {
        map->table->tail->next = new_node;
        map->table->tail = new_node;
    }
    map->size++;
    map->table->size++;
    // otherwise, return 0
    // TODO: implement this function
    return 0;
}

int hash_map_get(hash_map *map, char *key, int *value)
{
    // get the value associated with the key
    // if the map is NULL, return -1
    if (map == NULL)
    {
        return -1;
    }

    // otherwise, return 0
    key_val_list_node *current = map->table->head;
    while (current != NULL)
    {
        if (strcmp(current->data.key, key) == 0)
        {
            *value = current->data.value;
            return 0;
        }
        current = current->next;
    }
    // TODO: implement this function
    // if the key does not exist, return -2
    return -2;
}

int hash_map_remove(hash_map *map, char *key)
{
    // remove the key value pair from the map
    // if the map is NULL, return -1
    if (map == NULL)
    {
        return -1;
    }

    // otherwise, return 0
    key_val_list_node *current = map->table->head;
    key_val_list_node *previous = NULL;
    while (current != NULL)
    {
        if (strcmp(current->data.key, key) == 0)
        {
            if (previous == NULL)
            {
                map->table->head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            if (current == map->table->tail)
            {
                map->table->tail = previous;
            }
            free(current);
            map->table->size--;
            return 0;
        }
        previous = current;
        current = current->next;
    }
    // if the key does not exist, return -2
    return -2;
}

size_t hash_map_size(hash_map *map)
{
    // return the number of key value pairs in the map
    // if the map is NULL, return 0
    if (map == NULL)
    {
        return 0;
    }
    // otherwise, return the number of key value pairs
    return map->size;
}

int hash_map_update(hash_map *map, char *key, int value)
{
    // update the value of a key in the map
    // if the map is NULL, return -1
    if (map == NULL)
    {
        return -1;
    }
    // otherwise, return 0
    key_val_list_node *current = map->table->head;
    while (current != NULL)
    {
        if (strcmp(current->data.key, key) == 0)
        {
            current->data.value = value;
            return 0;
        }
        current = current->next;
    }
    // if the key does not exist, return -2
    return -2;
}

float hash_map_collision_ratio(hash_map *map)
{
    // return the ratio of the the total number of key value pairs in the map
    // to the number of non-empty buckets
    // 
    if (map == NULL || map->size == 0)
    {
        // if the map is NULL, you may return 0.0
        return 0.0;
    }
    
    size_t non_empty_buckets = 0;
    for (size_t i = 0; i < HASH_MAP_SIZE; ++i)
    {
        if (map->table[i].head != NULL)
        {
            non_empty_buckets++;
        }
    }

    if (non_empty_buckets == 0)
    {
        return 0.0;
    }

    return (float)map->size / non_empty_buckets;
}

void hash_map_print(hash_map *map)
{
    // print the contents of the map
    if (map->table == NULL)
    {
        return;
    }
    
    key_val_list_node *current = map->table->head;
    while (current != NULL)
    {
        printf("%s: %d --> ", current->data.key, current->data.value);
        current = current->next;
    }
    printf("NULL \n");
}

#endif // HASH_MAP_H