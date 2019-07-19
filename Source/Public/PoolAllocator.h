#pragma once

#include <cstddef>

using U8 = unsigned char;

class PoolAllocator
{
public:

	struct Node
	{
		Node* next;
	};

	Node* m_Head = nullptr;

private:

	void Insert(Node* node);
	Node* Remove();

public:

	PoolAllocator(std::size_t size, std::size_t object_size);
	~PoolAllocator();
	void* Allocate(std::size_t requested_size);
	void Deallocate(void* node);
	void Reset();

private:

	U8* m_MemoryBlock;
	std::size_t m_Size;
	std::size_t m_ObjectSize;
	void Initialize();
};