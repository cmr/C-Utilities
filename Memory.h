#ifndef INCLUDE_UTILITIES_MEMORY
#define INCLUDE_UTILITIES_MEMORY

#include "Common.h"

export void Memory_Free(void* block);
export void Memory_BlockCopy(uint8* source, uint8* destination, uint64 amount);
export boolean Memory_Compare(uint8* blockA, uint8* blockB, uint64 lengthA, uint64 lengthB);

/**
 * Frees a block of memory allocated by Allocate or AllocateArray
 * @param pointer The block of memory to free
 */
#define Free(pointer) Memory_Free(pointer)

#ifdef NDEBUG

export void* Memory_Allocate(uint64 size);
export void* Memory_Reallocate(void* block, uint64 size);

/**
 * @returns a pointer to a block of memory at least the sizeof @a type.
 */
#define Allocate(type) ((type*)Memory_Allocate(sizeof(type)))

/**
 * @returns a pointer to a block of memory large enough to contain @a count
 * objects of size @a type.
 */
#define AllocateArray(type, count) ((type*)Memory_Allocate(sizeof(type) * count))

/**
 * @returns a pointer to a block of memory large enough to contain @a count
 * objects of size @a type.
 */
#define ReallocateArray(type, count, array) ((type*)Memory_Reallocate((void*)array, sizeof(type) * count))

#else

export void* Memory_AllocateD(uint64 size, uint64 line, int8* file);
export void* Memory_ReallocateD(void* block, uint64 size, uint64 line, int8* file);

#define Allocate(type) ((type*)Memory_AllocateD(sizeof(type), __LINE__, __FILE__))
#define AllocateArray(type, count) ((type*)Memory_AllocateD(sizeof(type) * count, __LINE__, __FILE__))
#define ReallocateArray(type, count, array) ((type*)Memory_ReallocateD((void*)array, sizeof(type) * count, __LINE__, __FILE__))

#endif


#endif
