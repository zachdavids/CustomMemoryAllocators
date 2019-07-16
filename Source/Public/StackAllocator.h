#pragma once

#include "Allocator.h"

class StackAllocator : public Allocator
{

	struct Header
	{
		std::size_t adjustment;
	};

public:

	StackAllocator() = default;
	StackAllocator(std::size_t size);
	~StackAllocator();
	virtual void* Allocate(std::size_t requested_size, std::size_t alignment = 4) override;
	virtual void Deallocate(void* node) override;
	virtual void Reset() override;

private:

	std::size_t m_CurrentPosition;
	void Initialize();
};