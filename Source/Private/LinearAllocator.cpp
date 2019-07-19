#include "LinearAllocator.h"
#include "AlignmentUtility.h"

#include <assert.h>
#include <stdlib.h>

LinearAllocator::LinearAllocator(std::size_t size) :
	m_Size(size)
{
	Initialize();
}

LinearAllocator::~LinearAllocator()
{
	free(m_MemoryBlock);
}

void LinearAllocator::Initialize()
{
	m_MemoryBlock = reinterpret_cast<U8*>(malloc(m_Size));

	Reset();
}

void* LinearAllocator::Allocate(std::size_t size, std::size_t alignment /*= 8*/)
{
	size = AlignmentUtility::AlignAddress(size, alignment);

#ifdef _DEBUG
	assert(m_MemoryBlock + m_Size > m_CurrentPosition + size && "Not enough available memory for allocation");
#endif

	U8* memory = m_CurrentPosition;
	m_CurrentPosition += size;

	return reinterpret_cast<void*>(memory);
}

void LinearAllocator::Reset()
{
	m_CurrentPosition = m_MemoryBlock;
}