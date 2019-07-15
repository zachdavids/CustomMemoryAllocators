#include "Allocator.h"

#include <assert.h>

Allocator::Allocator(std::size_t size) :
    m_Size(size),
    m_MemoryUsed(0)
{
}

Allocator::~Allocator()
{
    m_Start = nullptr;
    m_Size = 0;
}

std::size_t Allocator::Align(void* address, std::size_t alignment) const
{
	std::size_t adjustment = alignment - (reinterpret_cast<std::size_t>(address) & (alignment - 1));

	return (adjustment == alignment) ? 0 : adjustment;
}

std::size_t Allocator::AlignHeader(void* address, std::size_t alignment, std::size_t header_size) const
{
	std::size_t adjustment = Align(address, alignment);

	if (header_size > adjustment)
	{
		std::size_t required_space = header_size - adjustment;
		adjustment += alignment * (required_space / alignment);

		if (required_space % alignment != 0)
		{
			adjustment += alignment;
		}
	}

	return adjustment;
}
