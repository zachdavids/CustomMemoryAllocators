#include "DoubleBufferedAllocator.h"

DoubleBufferedAllocator::DoubleBufferedAllocator(std::size_t size)
{
	m_Stack[0] = StackAllocator(size);
	m_Stack[1] = StackAllocator(size);

	m_CurrentStack = reinterpret_cast<std::size_t>(&m_Stack[0]);
}

void* DoubleBufferedAllocator::Allocate(std::size_t requested_size, std::size_t alignment)
{
	return m_Stack[m_CurrentStack].Allocate(requested_size, alignment);
}

void DoubleBufferedAllocator::SwapBuffers()
{
	m_CurrentStack = !m_CurrentStack;
}

void DoubleBufferedAllocator::ResetCurrentBuffer()
{
	m_Stack[m_CurrentStack].Reset();
}
