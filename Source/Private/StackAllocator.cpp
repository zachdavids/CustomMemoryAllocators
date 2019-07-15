#include "StackAllocator.h"

#include <assert.h>
#include <stdlib.h>
#include <iostream>

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

void* StackAllocator::Allocate(std::size_t requested_size, std::size_t alignment /*= 4*/)
{
	std::size_t adjustment = AlignHeader(m_CurrentPosition, alignment, sizeof(Header));

	const std::size_t aligned_address = m_CurrentPosition + adjustment;

	Header* headerPtr = reinterpret_cast<Header*>(aligned_address - sizeof(Header));
	*headerPtr = Header{ adjustment };

	m_CurrentPosition += requested_size + adjustment;
	m_MemoryUsed += requested_size + adjustment;

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