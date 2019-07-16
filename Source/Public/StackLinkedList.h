#pragma once

class StackLinkedList
{
public:

	struct Node
	{
		Node* next = nullptr;
	};

	Node* m_Head = nullptr;

public:

    StackLinkedList() = default;
	inline void Push(Node* node);
	inline void* Pop();

};

void StackLinkedList::Push(Node* node)
{
	node->next = m_Head;
	m_Head = node;
}

void* StackLinkedList::Pop()
{
	Node* head = m_Head;
	m_Head = head->next;

	return head;
}
