#pragma once

#include "Allocator.h"

class PoolAllocator : public Allocator
{
public:

	PoolAllocator(std::size_t size, std::size_t object_size);
	~PoolAllocator();
	void Initialize();
	virtual void* Allocate(std::size_t size, u8 alignment = 4) override;
	virtual void Deallocate(void* address) override;

private:

	std::size_t m_ObjectSize;
};