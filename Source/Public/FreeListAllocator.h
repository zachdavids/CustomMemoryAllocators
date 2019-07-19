#pragma once

#include <tuple>
#include <cstddef>

using U8 = unsigned char;

class FreeListAllocator
{
public:

	struct Header
	{
		std::size_t size;
		std::size_t alignment;
	};

public:

	struct Node
	{
		std::size_t size;
		Node* next;
	};

	Node* m_Head = nullptr;

private:

	void InsertAfter(Node* insert, Node* previous);
	void RemoveAfter(Node* remove, Node* previous);

public:

	FreeListAllocator(std::size_t size);
	~FreeListAllocator();
	void* Allocate(std::size_t size, std::size_t alignment = 8);
	void Deallocate(void* address);
	void Reset();

private:

	U8* m_MemoryBlock;
	std::size_t m_Size;
	static constexpr std::size_t s_HeaderSize = sizeof(Header);
	void Initialize();
	void Defragment();
	std::tuple<Node*, Node*> FindFirstFit(std::size_t size, std::size_t alignment);
};

