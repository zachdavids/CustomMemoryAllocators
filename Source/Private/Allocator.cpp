#include "Allocator.h"

#include <assert.h>

Allocator::Allocator(std::size_t size) :
    m_Size(size),
    m_MemoryUsed(0)
{
}

Allocator::~Allocator()
{
    m_Start = nullptr;
    m_Size = 0;
}