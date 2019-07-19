#include "PoolAllocator.h"

#include <assert.h>
#include <stdlib.h>

PoolAllocator::PoolAllocator(std::size_t size, std::size_t object_size) :
	m_Size(size),
	m_ObjectSize(object_size)
{
#ifdef _DEBUG
	assert(m_ObjectSize > sizeof(Node) && "Object size is smaller than node size");
	assert(m_Size % m_ObjectSize == 0 && "Object size not a multiple of memory block size");
#endif

	Initialize();
}

PoolAllocator::~PoolAllocator()
{
	free(m_MemoryBlock);
}

void PoolAllocator::Initialize()
{
	m_MemoryBlock = reinterpret_cast<U8*>(malloc(m_Size));

	Reset();
}

void* PoolAllocator::Allocate(std::size_t requested_size)
{
#ifdef _DEBUG	
	assert(requested_size == m_ObjectSize && "Requested allocation is not equal to object size");
#endif

	return reinterpret_cast<void*>(Remove());
}

void PoolAllocator::Deallocate(void* node)
{
	Insert(reinterpret_cast<Node*>(node));
}

void PoolAllocator::Reset()
{
	const int num_objects = m_Size / m_ObjectSize;
	for (int i = 0; i < num_objects; ++i) 
	{
		Insert(reinterpret_cast<Node*>(m_MemoryBlock + (m_ObjectSize * i)));
	}
}

void PoolAllocator::Insert(Node* node)
{
	node->next = m_Head;
	m_Head = node;
}

PoolAllocator::Node* PoolAllocator::Remove()
{
	Node* head = m_Head;
	m_Head = head->next;

	return head;
}
