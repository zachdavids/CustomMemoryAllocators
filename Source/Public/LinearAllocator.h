#pragma once

#include "Allocator.h"

class LinearAllocator : public Allocator
{
public:

	LinearAllocator(std::size_t size);
	~LinearAllocator();
	virtual void* Allocate(std::size_t size, std::size_t alignment = 4) override;
	virtual void Deallocate(void* address) override;
	virtual void Reset() override;

private:

	std::size_t m_CurrentPosition;
	void Initialize();

};

