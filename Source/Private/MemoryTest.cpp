#include "PoolAllocator.h"
#include "BenchmarkUtility.h"

#include <iostream>
#include <chrono>

int main()
{
    PoolAllocator* pool = new PoolAllocator(204800, 32);

	std::cout << "Pool Multiple-deallocate: " << BenchmarkUtility::RunSingleDeallocationTest(pool, 32) << std::endl;

	delete pool;
}