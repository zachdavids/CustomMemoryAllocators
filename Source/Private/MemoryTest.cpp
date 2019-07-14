#include "PoolAllocator.h"
#include "BenchmarkUtility.h"

#include <iostream>
#include <chrono>

int main()
{
    PoolAllocator* pool = new PoolAllocator(83886080, 32);

	std::cout << "Pool Multiple Allocate: " << BenchmarkUtility::RunMultipleAllocationTest(pool, 4096, 20480) << std::endl;
	std::cout << "Pool Multiple Deallocate: " << BenchmarkUtility::RunMultipleDeallocationTest(pool, 4096, 20480) << std::endl;

	delete pool;
}