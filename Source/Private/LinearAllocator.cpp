#include "LinearAllocator.h"

#include <assert.h>
#include <stdlib.h>

LinearAllocator::LinearAllocator(std::size_t size) :
	Allocator(size)
{
	Initialize();
}

LinearAllocator::~LinearAllocator()
{
	free(m_Start);
}

void LinearAllocator::Initialize()
{
	m_Start = malloc(m_Size);

	Reset();
}

void* LinearAllocator::Allocate(std::size_t size, std::size_t alignment /*= 4*/)
{
	const std::size_t adjustment = Align(m_CurrentPosition, alignment);

#ifdef _DEBUG
	assert(m_Size > m_MemoryUsed + size + adjustment && "Not enough available memory for allocation");
#endif

	m_CurrentPosition += size + adjustment;
	m_MemoryUsed += size + adjustment;

	return reinterpret_cast<void*>(m_CurrentPosition + adjustment);
}

void LinearAllocator::Deallocate(void* address)
{
}

void LinearAllocator::Reset()
{
	m_CurrentPosition = reinterpret_cast<std::size_t>(m_Start);
	m_MemoryUsed = 0;
}