#pragma once

#include <cstddef>

using U8 = unsigned char;

class LinearAllocator
{
public:

	LinearAllocator(std::size_t size);
	~LinearAllocator();
	void* Allocate(std::size_t size, std::size_t alignment = 8);
	void Reset();

private:

	U8* m_MemoryBlock;
	U8* m_CurrentPosition;
	std::size_t m_Size;
	void Initialize();

};

