#pragma once

#include "Allocator.h"

#include <stddef.h>

class DoubleEndedStackAllocator : public Allocator
{
public:

	DoubleEndedStackAllocator(std::size_t size);
	~DoubleEndedStackAllocator();
	virtual void* Allocate(std::size_t size, std::size_t alignment = 8) override;
	virtual void Deallocate(void* address) override;
	virtual void Reset() override;

private:

	std::size_t m_Bottom;
	std::size_t m_Top;
	void Initialize();
};

