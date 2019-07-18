#pragma once

#include "Allocator.h"
#include "LinkedList.h"

#include <tuple>

class FreeListAllocator : public Allocator
{
public:

	struct Header
	{
		std::size_t alignment;
		std::size_t size;
	};

public:

	FreeListAllocator(std::size_t size);
	~FreeListAllocator();
	virtual void* Allocate(std::size_t size, std::size_t alignment = 8) override;
	virtual void Deallocate(void* address) override;
	virtual void Reset() override;

private:

	LinkedList<std::size_t> m_FreeList;
	static constexpr std::size_t s_HeaderSize = sizeof(Header);
	void Initialize();
	void Defragment();
	std::tuple<LinkedList<std::size_t>::Node*, LinkedList<std::size_t>::Node*, std::size_t> FindFirstFit(std::size_t size, std::size_t alignment);
};

