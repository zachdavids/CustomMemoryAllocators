#pragma once

#include <cstddef>

using U8 = unsigned char;

class StackAllocator
{
public:

	struct Marker
	{
		U8* address;
	};

public:

	StackAllocator() = default;
	StackAllocator(std::size_t size);
	~StackAllocator();
	void* Allocate(std::size_t requested_size, std::size_t alignment = 8);
	void Deallocate(void* node);
	void Reset();
	void FreeToMarker(Marker marker);
	Marker GetMarker() const;

private:

	U8* m_MemoryBlock;
	U8* m_StartPosition;
	U8* m_CurrentPosition;
	std::size_t m_Size;
	void Initialize();
};