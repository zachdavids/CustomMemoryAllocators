#pragma once

#include "Allocator.h"
#include "StackLinkedList.h"

class PoolAllocator : public Allocator
{
public:

	PoolAllocator(std::size_t size, std::size_t object_size);
	~PoolAllocator();
	virtual void* Allocate(std::size_t requested_size, std::size_t alignment = 4) override;
	virtual void Deallocate(void* node) override;
	virtual void Reset() override;

private:

	void* m_Start;
	std::size_t m_ObjectSize;
	StackLinkedList m_FreeList;
	void Initialize();
};