#include "PoolAllocator.h"
#include "StackAllocator.h"
#include "BenchmarkUtility.h"

#include <iostream>
#include <chrono>

int main()
{
    PoolAllocator* pool = new PoolAllocator(83886080, 4096);
	StackAllocator* stack = new StackAllocator(83886080);

	std::cout << "Pool Multiple Allocate: " << BenchmarkUtility::RunMultipleAllocationTest(pool, 4096, 20480) << std::endl;
	std::cout << "Pool Multiple Deallocate: " << BenchmarkUtility::RunMultipleDeallocationTest(pool, 4096, 20480) << std::endl;

	std::cout << "Pool Multiple Allocate: " << BenchmarkUtility::RunMultipleAllocationTest(stack, 4096, 2000) << std::endl;
	std::cout << "Pool Multiple Deallocate: " << BenchmarkUtility::RunMultipleDeallocationTest(stack, 4096, 1) << std::endl;

	delete pool;
}