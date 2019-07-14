#pragma once

#include "Allocator.h"
#include "FreeList.h"

class PoolAllocator : public Allocator
{
public:

	PoolAllocator(std::size_t size, std::size_t object_size);
	~PoolAllocator();
	virtual void* Allocate(std::size_t requested_size, std::size_t alignment = 4) override;
	virtual void Deallocate(void* node) override;
	void Reset();

private:

	void* m_Start;
	FreeList m_FreeList;
	std::size_t m_ObjectSize;

	void Initialize();
};