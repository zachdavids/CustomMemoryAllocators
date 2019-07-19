#include "FreeListAllocator.h"
#include "AlignmentUtility.h"

#include <assert.h>
#include <stdlib.h>

FreeListAllocator::FreeListAllocator(std::size_t size) :
	m_Size(size)
{
	Initialize();
}

FreeListAllocator::~FreeListAllocator()
{
	free(m_MemoryBlock);
}

void FreeListAllocator::Initialize()
{
	m_MemoryBlock = reinterpret_cast<U8*>(malloc(m_Size));

	Reset();
}

void* FreeListAllocator::Allocate(std::size_t size, std::size_t alignment /*= 8*/)
{
	std::tuple result = FindFirstFit(size, alignment);
	Node* current_node = std::get<0>(result);
	Node* previous_node = std::get<1>(result);

	const std::size_t remaining_size = current_node->size - size;
	if (remaining_size > 0)
	{
		Node* node = reinterpret_cast<Node*>(reinterpret_cast<std::size_t>(current_node) + size);
		*node = Node{ remaining_size, nullptr };
		InsertAfter(node, current_node);
	}

	RemoveAfter(current_node, previous_node);

	const std::size_t alignment_padding = alignment - sizeof(Header);
	const std::size_t header_address = reinterpret_cast<std::size_t>(current_node) + alignment_padding;
	Header* header = reinterpret_cast<Header*>(header_address);
	*header = Header{ size, alignment_padding };

	return reinterpret_cast<void*>(header_address + s_HeaderSize);
}

void FreeListAllocator::Deallocate(void* address)
{
	const std::size_t current_address = reinterpret_cast<std::size_t>(address);
	const std::size_t header_address = current_address - s_HeaderSize;
	
	Header* header = reinterpret_cast<Header*>(header_address);
	Node* node = reinterpret_cast<Node*>(header_address);
	*node = Node{ header->size + header->alignment, nullptr };

	Node* current = m_Head;
	Node* previous = nullptr;

	if (current == nullptr)
	{
		InsertAfter(node, m_Head);
	}
	else
	{
		while (current != nullptr)
		{
			if (current > address)
			{
				break;
			}

			previous = current;
			current = current->next;
		}

		InsertAfter(node, previous);
	}

	Defragment();
}

void FreeListAllocator::Defragment()
{
	Node* current = m_Head;
	while (current != nullptr && current->next != nullptr)
	{
		if (reinterpret_cast<std::size_t>(current) + current->size == reinterpret_cast<std::size_t>(current->next))
		{
			current->size += current->next->size;
			RemoveAfter(current->next, current);
		}

		current = current->next;
	}
}

void FreeListAllocator::Reset()
{
	Node* node = reinterpret_cast<Node*>(m_MemoryBlock);
	*node = Node{ m_Size, nullptr };

	m_Head = nullptr;
	InsertAfter(node, nullptr);
}

std::tuple<FreeListAllocator::Node*, FreeListAllocator::Node*> FreeListAllocator::FindFirstFit(std::size_t& size, std::size_t alignment)
{
	Node* current_node = m_Head;
	Node* previous_node = nullptr;

	size = AlignmentUtility::AlignAddress(size + s_HeaderSize, alignment);

	while (current_node != nullptr)
	{
		if (current_node->size >= size)
		{
			break;
		}

		previous_node = current_node;
		current_node = current_node->next;
	}

	return std::make_tuple(current_node, previous_node);
}

void FreeListAllocator::InsertAfter(Node* insert, Node* previous)
{
	if (previous == nullptr)
	{
		if (m_Head == nullptr)
		{
			insert->next = nullptr;
			m_Head = insert;
		}
		else
		{
			insert->next = m_Head;
			m_Head = insert;
		}
	}
	else
	{
		if (previous->next == nullptr)
		{
			insert->next = nullptr;
			previous->next = insert;
		}
		else
		{
			insert->next = previous->next;
			previous->next = insert;
		}
	}
}

void FreeListAllocator::RemoveAfter(Node* remove, Node* previous)
{
	if (previous == nullptr)
	{
		if (remove->next == nullptr)
		{
			m_Head = nullptr;
		}
		else
		{
			m_Head = remove->next;
		}
	}
	else
	{
		previous->next = remove->next;
	}
}