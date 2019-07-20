#include "BenchmarkUtility.h"
#include "LinearAllocator.h"
#include "StackAllocator.h"
#include "DoubleBufferedAllocator.h"
#include "DoubleEndedStackAllocator.h"
#include "PoolAllocator.h"
#include "FreeListAllocator.h"

#include <iostream>

int main()
{
	LinearAllocator* linear = new LinearAllocator(1073741824);
	std::cout << "Linear Allocation Average: " << BenchmarkUtility::RunAllocationTest(linear, 4096, 260000) << "\n";
	delete linear;

	StackAllocator* stack = new StackAllocator(1073741824);
	std::cout << "Stack Allocation Average: " << BenchmarkUtility::RunAllocationTest(stack, 4096, 260000) << "\n";
	std::cout << "Stack Deallocation Average: " << BenchmarkUtility::RunMarkerFreeTest(stack, 4096, 260000) << "\n";
	delete stack;

	DoubleEndedStackAllocator* double_stack = new DoubleEndedStackAllocator(1073741824);
	std::cout << "Double Stack Allocation Average: " << BenchmarkUtility::RunDoubleStackAllocationTest(double_stack, 4096, 260000) << "\n";
	std::cout << "Double Stack Deallocation Average: " << BenchmarkUtility::RunDoubleMarkerFreeTest(double_stack, 4096, 260000) << "\n";
	delete double_stack;

	PoolAllocator* pool = new PoolAllocator(1073741824, 4096);
	std::cout << "Pool Allocation Average: " << allocation_total += BenchmarkUtility::RunAllocationTest(pool, 4096, 260000) << "\n";
	std::cout << "Pool Deallocation Average: " << deallocation_total += BenchmarkUtility::RunDeallocationTest(pool, 4096, 260000) << "\n";
	delete pool;

	FreeListAllocator* free_list = new FreeListAllocator(1073741824);
	std::cout << "Free List Allocation Average: " << allocation_total += BenchmarkUtility::RunAllocationTest(free_list, 4096, 260000) << "\n";
	std::cout << "Free List Deallocation Average: " << deallocation_total += BenchmarkUtility::RunDeallocationTest(free_list, 4096, 260000) << "\n";
	delete free_list;
}