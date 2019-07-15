#include "StackAllocator.h"

#include <stdlib.h>

StackAllocator::StackAllocator(std::size_t size) :
	Allocator(size)
{
}

StackAllocator::~StackAllocator()
{
	free(m_Start);
}

void StackAllocator::Initialize()
{
	m_Start = malloc(m_Size);

	Reset();
}

void* StackAllocator::Allocate(std::size_t requested_size, std::size_t alignment /*= 4*/)
{
	const std::size_t adjustment = AlignHeader(m_CurrentPosition, alignment, sizeof(Header));

#ifdef _DEBUG
	assert(m_MemoryUsed + requested_size + adjustment > m_Size && "Requested size larger than stack size");
#endif

	void* aligned_address = reinterpret_cast<void*>(reinterpret_cast<std::size_t>(m_CurrentPosition) - adjustment);
	return new void*;
}

void StackAllocator::Deallocate(void* node)
{

}

void StackAllocator::Reset()
{
	m_MemoryUsed = 0;
}