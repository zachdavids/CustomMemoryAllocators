#include "StackAllocator.h"
#include "AlignmentUtility.h"

#include <assert.h>
#include <stdlib.h>

StackAllocator::StackAllocator(std::size_t size) :
	m_Size(size)
{
	Initialize();
}

StackAllocator::~StackAllocator()
{
	free(m_MemoryBlock);
}

void StackAllocator::Initialize()
{
	m_MemoryBlock = reinterpret_cast<U8*>(malloc(m_Size));

	Reset();
}

void* StackAllocator::Allocate(std::size_t size, std::size_t alignment /*= 8*/)
{
	size = AlignmentUtility::AlignAddress(size, alignment);

#ifdef _DEBUG
	assert(m_StartPosition + m_Size >= m_CurrentPosition + size && "Insufficient memory");
#endif
	
	U8* memory = m_CurrentPosition;
	m_CurrentPosition += size;

	return reinterpret_cast<void*>(memory);
}

void StackAllocator::Deallocate(void* node)
{
	m_CurrentPosition = reinterpret_cast<U8*>(node);
}

void StackAllocator::Reset()
{
	m_StartPosition = m_MemoryBlock;
	m_CurrentPosition = m_MemoryBlock;
}

void StackAllocator::FreeToMarker(Marker marker)
{
	m_CurrentPosition = marker.address;
}

StackAllocator::Marker StackAllocator::GetMarker() const
{
	return Marker{ m_CurrentPosition };
}
