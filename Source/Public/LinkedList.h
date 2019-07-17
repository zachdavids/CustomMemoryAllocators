#pragma once

template<class T>
class LinkedList
{
public:

	struct Node
	{
		T data;
		Node* next = nullptr;
	};

	Node* m_Head = nullptr;

public:

	LinkedList() = default;
	inline void InsertAfter(Node* insert, Node* previous);
	inline void RemoveAfter(Node* remove, Node* previous);

};

template<class T>
void LinkedList<T>::InsertAfter(Node* insert, Node* previous)
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

template<class T>
void LinkedList<T>::RemoveAfter(Node* remove, Node* previous)
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
