#include "BenchmarkUtility.h"

#include <chrono>
#include <iostream>
#include <vector>

double BenchmarkUtility::RunSingleAllocationTest(Allocator* allocator, const std::size_t object_size)
{
	return RunMultipleAllocationTest(allocator, object_size, 1);
}

double BenchmarkUtility::RunMultipleAllocationTest(Allocator* allocator, const std::size_t object_size, const std::size_t count)
{
	double total = 0;

	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> stop;
	for (std::size_t i = 0; i < count; ++i)
	{
		start = std::chrono::high_resolution_clock::now();
		allocator->Allocate(object_size);
		stop = std::chrono::high_resolution_clock::now();

		total += static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count());
	}

	allocator->Reset();

	return total;
}

double BenchmarkUtility::RunSingleDeallocationTest(Allocator* allocator, const std::size_t object_size)
{
	return RunMultipleDeallocationTest(allocator, object_size, 1);
}

double BenchmarkUtility::RunMultipleDeallocationTest(Allocator* allocator, const std::size_t object_size, const std::size_t count)
{
	double total = 0;

	std::vector<void*> addresses;
	for (std::size_t i = 0; i < count; ++i)
	{
		addresses.emplace_back(allocator->Allocate(object_size));
	}

	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> stop;
	for (std::size_t i = addresses.size(); i-- > 0;)
	{
		start = std::chrono::high_resolution_clock::now();
		allocator->Deallocate(addresses[i]);
		stop = std::chrono::high_resolution_clock::now();

		total += static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count());
	}

	allocator->Reset();

	return total;
}
