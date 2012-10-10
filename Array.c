/**
 * @file Array.c
 * @brief A dynamicly sized array that expands as you append, but remains
 * contiguous.
 */
#include "Array.h"

/**
 * Create a new array.
 *
 * @param size Size in bytes of new array
 * @returns pointer to newly initialzed array
 */
Array* Array_New(uint64 size) {
    Array* array;
    
    array = Allocate(Array);
    Array_Initialize(array, size);

    return array;
}

/**
 * Create a new array using data from an existing buffer.
 *
 * @param data Pointer to buffer to copy data from
 * @param size New size of array
 * @returns pointer to newly created array
 */
Array* Array_NewFromExisting(uint8* data, uint64 size) {
    Array* array;
    uint64 actualSize;
    
    assert(size > 0);
    assert(data != NULL);
    
    actualSize = 32;
    while (actualSize < size)
        actualSize *= 2;

    array = Allocate(Array);
    array->Size = size;
    array->Allocation = actualSize;
    array->Data = ReallocateArray(uint8, actualSize, data); /* XXX: copy? */

    return array;
}

/**
 * Initialize an already allocated array.
 *
 * @param array array object to initialize
 * @param size size of new array
 */
void Array_Initialize(Array* array, uint64 size) {
    uint64 actualSize;

    assert(array != NULL);

    actualSize = 32;
    while (actualSize < size)
        actualSize *= 2;
        
    array->Size = size;
    array->Allocation = actualSize;
    array->Data = AllocateArray(uint8, actualSize);
}

/**
 * Free the data + deinitialize an array.
 *
 * @param self Array to dispose of.
 * @warning @a self is not freed!
 */
void Array_Dispose(Array* self) {
    assert(self != NULL);

    Free(self->Data);
    self->Size = 0;
    self->Allocation = 0;
}

/**
 * Resize an array.
 *
 * @param self Array to resize
 * @param newSize Desired size of array
 */
void Array_Resize(Array* self, uint64 newSize) {
    uint64 actualSize;

    assert(newSize > 0);
    assert(self != NULL);

    actualSize = self->Allocation;
    while (actualSize < newSize)
        actualSize *= 2;

    if (actualSize != self->Allocation) self->Data = ReallocateArray(uint8, actualSize, self->Data);
    self->Allocation = actualSize;
    self->Size = newSize;
}

/**
 * Read bytes from an array.
 *
 * @param self Array to read from
 * @param position Offset (in bytes) from start of the array to read from
 * @param amount Number of bytes to read
 */
uint8* Array_Read(Array* self, uint64 position, uint64 amount) {
    assert(self != NULL);
    assert(position + amount <= self->Size);

    return self->Data + position;
}

/**
 * Write data to an array, resizing if needed.
 *
 * @param self Array to write to
 * @param position Offset (in bytes) from start of array to write to
 * @param data Data to write
 * @param amount Number of bytes to write from @a data
 */
void Array_Write(Array* self, const uint8* data, uint64 position, uint64 amount) {
    uint8 i;

    assert(self != NULL);
    
    if (position + amount > self->Size) Array_Resize(self, position + amount);

    for (i = 0; i < amount; i++)
        *(self->Data + position + i) = *(data + i);
}

/**
 * Append an array to another array.
 *
 * @param self Array to append to
 * @param source Array to append from
 */
void Array_Append(Array* self, Array* source) {
    assert(self != NULL && source != NULL);

    Array_Resize(self, self->Size + source->Size);
    Array_Write(self, source->Data, self->Size, source->Size);
}