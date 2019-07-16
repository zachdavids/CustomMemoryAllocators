#include "PoolAllocator.h"
#include "StackAllocator.h"
#include "LinearAllocator.h"
#include "FreeListAllocator.h"
#include "BenchmarkUtility.h"

#include <iostream>
#include <chrono>

int main()
{
    PoolAllocator* pool = new PoolAllocator(83886080, 4096);
	StackAllocator* stack = new StackAllocator(83886080);
	LinearAllocator* linear = new LinearAllocator(83886080);
	FreeListAllocator* free_list = new FreeListAllocator(1024);

	std::cout << "Pool Multiple Allocate: " << BenchmarkUtility::RunMultipleAllocationTest(pool, 4096, 20480) << std::endl;
	std::cout << "Pool Multiple Deallocate: " << BenchmarkUtility::RunMultipleDeallocationTest(pool, 4096, 20480) << std::endl;

	std::cout << "Stack Multiple Allocate: " << BenchmarkUtility::RunMultipleAllocationTest(stack, 4096, 2000) << std::endl;
	std::cout << "Stack Multiple Deallocate: " << BenchmarkUtility::RunMultipleDeallocationTest(stack, 4096, 2000) << std::endl;

	std::cout << "Linear Multiple Allocate: " << BenchmarkUtility::RunMultipleAllocationTest(linear, 4096, 2000) << std::endl;

	std::cout << "FreeList Multiple Allocate: " << BenchmarkUtility::RunMultipleAllocationTest(free_list, 16, 1) << std::endl;

	delete pool;
}