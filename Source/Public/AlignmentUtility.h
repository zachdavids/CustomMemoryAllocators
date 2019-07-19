#pragma once

#include <stdint.h>
#include <cstddef>

namespace AlignmentUtility
{
	inline uintptr_t AlignAddress(uintptr_t address, std::size_t alignment)
	{
		const size_t mask = alignment - 1;
		return (address + mask) & ~mask;
	}

	template<class T>
	inline T* AlignPointer(T* pointer, std::size_t alignment)
	{
		const uintptr_t address = reinterpret_cast<uintptr_t>(pointer);
		const uintptr_t aligned_address = AlignAddress(address, alignment);
		return reinterpret_cast<T*>(aligned_address);
	}
}