#include "StackAllocator.h"

#include <assert.h>
#include <stdlib.h>

StackAllocator::StackAllocator(std::size_t size) :
	Allocator(size)
{
	Initialize();
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

void* StackAllocator::Allocate(std::size_t size, std::size_t alignment /*= 4*/)
{
	const std::size_t adjustment = AlignHeader(m_CurrentPosition, alignment, sizeof(Header));

#ifdef _DEBUG
	assert(m_Size > m_MemoryUsed + size + adjustment && "Not enough available memory for allocation");
#endif

	const std::size_t aligned_address = m_CurrentPosition + adjustment;
	Header* header = reinterpret_cast<Header*>(aligned_address - sizeof(Header));
	*header = Header{ adjustment };

	m_CurrentPosition += size + adjustment;
	m_MemoryUsed += size + adjustment;

	return reinterpret_cast<void*>(aligned_address);
}

void StackAllocator::Deallocate(void* node)
{
	const std::size_t address = reinterpret_cast<std::size_t>(node);
	const Header* header{ reinterpret_cast<Header*>(address - sizeof(Header)) };

	m_CurrentPosition = address - header->adjustment;
	m_MemoryUsed = m_CurrentPosition - reinterpret_cast<std::size_t>(m_Start);
}

void StackAllocator::Reset()
{
	m_CurrentPosition = reinterpret_cast<std::size_t>(m_Start);
	m_MemoryUsed = 0;
}