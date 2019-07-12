#include "PoolAllocator.h"

PoolAllocator::PoolAllocator(std::size_t size, std::size_t object_size) :
	Allocator(size, start),
	m_ObjectSize(object_size),
{
	assert(m_ObjectSize > sizeof(void*) && "Block size is smaller than pointer size");

	Initialize();
}

PoolAllocator::~PoolAllocator()
{
}

void PoolAllocator::Initialize()
{
}

void* PoolAllocator::Allocate(std::size_t size, std::size_t alignment /*= 0*/)
{
}

void PoolAllocator::Deallocate(void* address)
{
}
