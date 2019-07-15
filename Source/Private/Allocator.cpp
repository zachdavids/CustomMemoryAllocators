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

std::size_t Allocator::Align(std::size_t address, std::size_t alignment) const
{
	std::size_t adjustment = alignment - (address & (alignment - 1));

	return (adjustment == alignment) ? 0 : adjustment;
}

std::size_t Allocator::AlignHeader(std::size_t address, std::size_t alignment, std::size_t header_size) const
{
	std::size_t adjustment = Align(address, alignment);
	std::size_t required_size = header_size;

	if (adjustment < required_size)
	{
		required_size -= adjustment;

		adjustment += alignment * (1 + (required_size / alignment));

		if (required_size % alignment != 0)
		{
			adjustment += alignment;
		}
	}

 	return adjustment;
}
