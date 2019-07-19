#include "DoubleEndedStackAllocator.h"
#include "AlignmentUtility.h"

#include <assert.h>
#include <stdlib.h>

DoubleEndedStackAllocator::DoubleEndedStackAllocator(std::size_t size) :
	m_Size(size)
{
	Initialize();
}

DoubleEndedStackAllocator::~DoubleEndedStackAllocator()
{
	free(m_MemoryBlock);
}

void DoubleEndedStackAllocator::Initialize()
{
	m_MemoryBlock = reinterpret_cast<U8*>(malloc(m_Size));

	Reset();
}

void* DoubleEndedStackAllocator::Allocate(std::size_t size, std::size_t stack_id, std::size_t alignment /*= 8*/)
{
	size = AlignmentUtility::AlignAddress(size, alignment);

#ifdef _DEBUG
	assert(m_CurrentPosition[1] >= m_CurrentPosition[0] + size && "Insufficient memory");
#endif

	U8* memory;
	if (stack_id)
	{
		m_CurrentPosition[1] -= size;
		memory = m_CurrentPosition[1];
	}
	else
	{
		memory = m_CurrentPosition[0];
		m_CurrentPosition[0] += size;
	}

	return reinterpret_cast<void*>(memory);
}

void DoubleEndedStackAllocator::FreeToMarker(Marker marker)
{
	m_CurrentPosition[marker.stack_id] = marker.address;
}

void DoubleEndedStackAllocator::Reset()
{
	m_StartPosition[0] = m_MemoryBlock;
	m_StartPosition[1] = m_MemoryBlock + m_Size;
	m_CurrentPosition[0] = m_StartPosition[0];
	m_CurrentPosition[1] = m_StartPosition[1];
}

DoubleEndedStackAllocator::Marker DoubleEndedStackAllocator::GetMarker(int stack_id) const
{
	return Marker{ m_CurrentPosition[stack_id], stack_id };
}
