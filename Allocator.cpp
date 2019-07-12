#include "Allocator.h"

#include <cassert>

Allocator::Allocator(size_t size, void* start) :
    m_Size(size),
    m_Start(start),
    m_MemoryUsed(0),
    m_AllocationCount(0)
{
}

Allocator::~Allocator()
{
    assert(m_AllocationCount == 0 && m_MemoryUsed == 0);
    m_Start = nullptr;
    m_Size = 0;
}

u8 Allocator::GetAlignmentAdjust(void* address, u8 alignment)
{
	u8 adjustment = alignment - (reinterpret_cast<u8*>(address) & static_cast<u8*>(alignment - 1));

	return (adjustment == alignment) ? 0 : adjustment;
}