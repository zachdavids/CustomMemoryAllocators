#include "DoubleEndedStackAllocator.h"

#include <stdlib.h>

DoubleEndedStackAllocator::DoubleEndedStackAllocator(std::size_t size) :
	Allocator(size)
{
	Initialize();
}

DoubleEndedStackAllocator::~DoubleEndedStackAllocator()
{
	free(m_Start);
}

void DoubleEndedStackAllocator::Initialize()
{
	m_Start = malloc(m_Size);

	Reset();
}

void* DoubleEndedStackAllocator::Allocate(std::size_t size, std::size_t alignment /*= 8*/)
{

}

void DoubleEndedStackAllocator::Deallocate(void* address)
{

}

void DoubleEndedStackAllocator::Reset()
{
	m_Bottom = reinterpret_cast<std::size_t>(m_Start);
	m_Top = reinterpret_cast<std::size_t>(m_Start) + m_Size;
	m_MemoryUsed = 0;
}