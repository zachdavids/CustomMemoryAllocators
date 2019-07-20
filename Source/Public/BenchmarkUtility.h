#include "StackAllocator.h"

#include <chrono>
#include <vector>

namespace BenchmarkUtility
{
	template<typename T>
	double RunAllocationTest(T* allocator, const std::size_t object_size, const std::size_t count)
	{
		double total = 0;

		std::chrono::time_point<std::chrono::steady_clock> start;
		std::chrono::time_point<std::chrono::steady_clock> stop;
		for (std::size_t i = 0; i < count; ++i)
		{
			start = std::chrono::high_resolution_clock::now();
			allocator->Allocate(object_size);
			stop = std::chrono::high_resolution_clock::now();

			total += static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count());
		}

		allocator->Reset();

		return total;
	}

	template<typename T>
	double RunDeallocationTest(T* allocator, const std::size_t object_size, const std::size_t count)
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
	
			total += static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count());
		}
	
		allocator->Reset();
	
		return total;
	}

	template<typename T>
	double RunMarkerFreeTest(T* allocator, const std::size_t object_size, const std::size_t count)
	{
		double total = 0;

		std::vector<T::Marker> markers;
		for (std::size_t i = 0; i < count; ++i)
		{
			markers.emplace_back(allocator->GetMarker());
			allocator->Allocate(object_size);
		}

		std::chrono::time_point<std::chrono::steady_clock> start;
		std::chrono::time_point<std::chrono::steady_clock> stop;
		for (std::size_t i = markers.size(); i-- > 0;)
		{
			start = std::chrono::high_resolution_clock::now();
			allocator->FreeToMarker(markers[i]);
			stop = std::chrono::high_resolution_clock::now();

			total += static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count());
		}

		allocator->Reset();

		return total;
	}


	template<typename T>
	double RunDoubleStackAllocationTest(T* allocator, const std::size_t object_size, const std::size_t count)
	{
		double total = 0;

		std::chrono::time_point<std::chrono::steady_clock> start;
		std::chrono::time_point<std::chrono::steady_clock> stop;
		for (std::size_t i = 0; i < count; ++i)
		{
			int stack_id = 1;
			if (i % 2 == 0)
			{
				stack_id = 0;
			}
			start = std::chrono::high_resolution_clock::now();
			allocator->Allocate(object_size, stack_id);
			stop = std::chrono::high_resolution_clock::now();

			total += static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count());
		}

		allocator->Reset();

		return total;
	}

	template<typename T>
	double RunDoubleMarkerFreeTest(T* allocator, const std::size_t object_size, const std::size_t count)
	{
		double total = 0;

		std::vector<T::Marker> markers;
		for (std::size_t i = 0; i < count; ++i)
		{
			int stack_id = 1;
			if (i % 2 == 0)
			{
				stack_id = 0;
			}
			markers.emplace_back(allocator->GetMarker(stack_id));
			allocator->Allocate(object_size, stack_id);
		}

		std::chrono::time_point<std::chrono::steady_clock> start;
		std::chrono::time_point<std::chrono::steady_clock> stop;
		for (std::size_t i = markers.size(); i-- > 0;)
		{
			start = std::chrono::high_resolution_clock::now();
			allocator->FreeToMarker(markers[i]);
			stop = std::chrono::high_resolution_clock::now();

			total += static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count());
		}

		allocator->Reset();

		return total;
	}
}
