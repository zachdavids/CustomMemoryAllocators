#pragma once

#include "StackAllocator.h"

class DoubleBufferedAllocator
{
public:

	DoubleBufferedAllocator(std::size_t size);
	void* Allocate(std::size_t requested_size, std::size_t alignment = 8);
	void SwapBuffers();
	void ResetCurrentBuffer();

private:

	std::size_t m_CurrentStack;
	StackAllocator m_Stack[2];

};