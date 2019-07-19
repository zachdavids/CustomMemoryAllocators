#pragma once

#include <cstddef>

using U8 = unsigned char;

class DoubleEndedStackAllocator
{
public:

	struct Marker
	{
		U8* address;
		int stack_id;
	};

public:

	DoubleEndedStackAllocator(std::size_t size);
	~DoubleEndedStackAllocator();
	void* Allocate(std::size_t size, std::size_t stack_id, std::size_t alignment = 8);
	void FreeToMarker(Marker marker);
	void Reset();
	Marker GetMarker(int stack_id) const;

private:

	U8* m_MemoryBlock;
	U8* m_StartPosition[2];
	U8* m_CurrentPosition[2];
	std::size_t m_Size;
	void Initialize();
};

