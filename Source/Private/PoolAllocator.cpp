#include "PoolAllocator.h"

#include <assert.h>
#include <stdlib.h>

PoolAllocator::PoolAllocator(std::size_t size, std::size_t object_size) :
	Allocator(size),
	m_ObjectSize(object_size)
{
#ifdef _DEBUG
	assert(m_ObjectSize > sizeof(void*) && "Block size is smaller than pointer size");
	assert(m_Size % m_ObjectSize == 0 && "Object size not a multiple of pool size");
#endif

	Initialize();
}

PoolAllocator::~PoolAllocator()
{
	free(m_Start);
}

void PoolAllocator::Initialize()
{
	m_Start = malloc(m_Size);

	Reset();
}

void* PoolAllocator::Allocate(std::size_t requested_size, std::size_t alignment /*= 0*/)
{
#ifdef _DEBUG	
	assert(requested_size == m_ObjectSize && "Requested allocation is not equal to object size");
#endif

	Node* node = reinterpret_cast<Node*>(m_FreeList.Pop());

#ifdef _DEBUG
	assert(node != nullptr && "Pool is full");
#endif

	m_MemoryUsed += m_ObjectSize;

	return (void*)node;
}

void PoolAllocator::Deallocate(void* node)
{
	m_FreeList.Push(reinterpret_cast<Node*>(node));

	m_MemoryUsed -= m_ObjectSize;
}

void PoolAllocator::Reset()
{
	m_MemoryUsed = 0;

	const int num_objects = m_Size / m_ObjectSize;
	for (int i = 0; i < num_objects; ++i) 
	{
		const std::size_t address = reinterpret_cast<std::size_t>(m_Start) + (m_ObjectSize * i);
		m_FreeList.Push(reinterpret_cast<Node*>(address));
	}
}
