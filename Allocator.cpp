#include "Allocator.h"

#include <cassert>

Allocator::Allocator(std::size_t size, void* start) :
    m_Size(size),
    m_Start(start),
    m_MemoryUsed(0)
{
}

Allocator::~Allocator()
{
    assert(m_MemoryUsed == 0 && "Memory Leak Detected);
    m_Start = nullptr;
    m_Size = 0;
}