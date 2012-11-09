#ifndef INCLUDE_UTILITIES_HASHTABLE
#define INCLUDE_UTILITIES_HASHTABLE

#include "Common.h"

typedef struct HashTable HashTable;

public HashTable* HashTable_New();
public void HashTable_Initialize(HashTable* table);
public void HashTable_Free(HashTable* self);
public void HashTable_Uninitialize(HashTable* self);

public void* HashTable_Get(HashTable* self, uint8* key, uint32 keyLength, void** value, uint32* valueLength); //returns the value as well in case the length is already known.
public void HashTable_Add(HashTable* self, uint8* key, uint32 keyLength, void* value, uint32 valueLength);
public void HashTable_Remove(HashTable* self, uint8* key, uint32 keyLength);
public void* HashTable_GetInt(HashTable* self, uint64 key, void** value, uint32* valueLength);
public void HashTable_AddInt(HashTable* self, uint64 key, void* value, uint32 valueLength);
public void HashTable_RemoveInt(HashTable* self, uint64 key);

#endif
