#pragma once

struct Node
{
	Node* next;
};

class FreeList
{
public:

    FreeList() = default;
	inline void Push(Node* node);
	inline void* Pop();

private:

	Node* m_Head = nullptr;
};

void FreeList::Push(Node* node)
{
	node->next = m_Head;
	m_Head = node;
}

void* FreeList::Pop()
{
	Node* head = m_Head;
	m_Head = head->next;

	return head;
}
