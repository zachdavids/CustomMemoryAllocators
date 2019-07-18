#include "FreeListAllocator.h"

#include <assert.h>
#include <stdlib.h>
#include <iostream>

using Node = LinkedList<std::size_t>::Node;

FreeListAllocator::FreeListAllocator(std::size_t size) :
	Allocator(size)
{
	Initialize();
}

FreeListAllocator::~FreeListAllocator()
{
	free(m_Start);
}

void FreeListAllocator::Initialize()
{
	m_Start = malloc(m_Size);

	Reset();
}

void* FreeListAllocator::Allocate(std::size_t size, std::size_t alignment /*= 4*/)
{
	std::tuple result = FindFirstFit(size, alignment);
	Node* current_node = std::get<0>(result);
	Node* previous_node = std::get<1>(result);
	const std::size_t adjustment = std::get<2>(result);

	const std::size_t required_size = size + adjustment;
	const std::size_t alignment_padding = alignment - sizeof(Header);
	const std::size_t remaining_size = current_node->data - required_size;

	if (remaining_size > 0)
	{
		Node* node = reinterpret_cast<Node*>(reinterpret_cast<std::size_t>(current_node) + required_size);
		node->data = remaining_size;
		node->next = nullptr;
		m_FreeList.InsertAfter(node, current_node);
	}

	m_FreeList.RemoveAfter(current_node, previous_node);

	const std::size_t header_address = reinterpret_cast<std::size_t>(current_node) + alignment_padding;
	const std::size_t aligned_address = header_address + s_HeaderSize;
	Header* header = reinterpret_cast<Header*>(header_address);
	*header = Header{ alignment_padding, required_size };

	m_MemoryUsed += required_size;

	return reinterpret_cast<void*>(aligned_address);
}

void FreeListAllocator::Deallocate(void* address)
{
	const std::size_t current_address = reinterpret_cast<std::size_t>(address);
	const std::size_t header_address = current_address - s_HeaderSize;
	
	Header* header = reinterpret_cast<Header*>(header_address);
	Node* node = reinterpret_cast<Node*>(header_address);
	node->data = header->size + header->alignment;
	node->next = nullptr;

	Node* current = m_FreeList.m_Head;
	Node* previous = nullptr;
	while (current != nullptr)
	{
		if (current > address)
		{
			m_FreeList.InsertAfter(node, previous);
			break;
		}

		previous = current;
		current = current->next;
	}

	m_MemoryUsed -= node->data;

	Defragment();
}

void FreeListAllocator::Defragment()
{
	Node* current = m_FreeList.m_Head;
	while (current != nullptr && current->next != nullptr)
	{
		if (reinterpret_cast<std::size_t>(current) + current->data == reinterpret_cast<std::size_t>(current->next))
		{
			current->data += current->next->data;
			m_FreeList.RemoveAfter(current->next, current);
		}

		current = current->next;
	}
}

void FreeListAllocator::Reset()
{
	Node* node = reinterpret_cast<Node*>(m_Start);
	node->data = m_Size;
	node->next = nullptr;

	m_FreeList.m_Head = nullptr;
	m_FreeList.InsertAfter(node, nullptr);

	m_MemoryUsed = 0;
}

std::tuple<Node*, Node*, std::size_t> FreeListAllocator::FindFirstFit(std::size_t size, std::size_t alignment)
{
	Node* current_node = m_FreeList.m_Head;
	Node* previous_node = nullptr;
	std::size_t adjustment = 0;

	while (current_node != nullptr)
	{
		adjustment = AlignHeader(reinterpret_cast<std::size_t>(current_node), alignment, sizeof(Header));
		std::size_t required_size = size + adjustment;

		if (current_node->data >= required_size)
		{
			break;
		}

		previous_node = current_node;
		current_node = current_node->next;
	}

	return std::make_tuple(current_node, previous_node, adjustment);
}
