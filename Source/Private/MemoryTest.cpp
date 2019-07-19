#include "PoolAllocator.h"
#include "StackAllocator.h"
#include "LinearAllocator.h"
#include "FreeListAllocator.h"

#include <iostream>
#include <chrono>

int main()
{
    PoolAllocator* pool = new PoolAllocator(83886080, 4096);
	StackAllocator* stack = new StackAllocator(83886080);
	LinearAllocator* linear = new LinearAllocator(83886080);
	FreeListAllocator* free_list = new FreeListAllocator(1024);

	uint32_t* number = new (free_list->Allocate(4)) uint32_t(999);

	delete pool;
	delete stack;
	delete linear;
	delete free_list;
}