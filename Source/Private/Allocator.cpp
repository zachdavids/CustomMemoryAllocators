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
	const std::size_t multiplier = (address / alignment) + 1;
	const std::size_t alignedAddress = multiplier * alignment;
	const std::size_t padding = alignedAddress - address;
	return padding;
}

std::size_t Allocator::AlignHeader(std::size_t address, std::size_t alignment, std::size_t header_size) const
{
	std::size_t padding = Align(address, alignment);
	std::size_t neededSpace = header_size;

	if (padding < neededSpace) {
		// Header does not fit - Calculate next aligned address that header fits
		neededSpace -= padding;

		// How many alignments I need to fit the header        
		if (neededSpace % alignment > 0) {
			padding += alignment * (1 + (neededSpace / alignment));
		}
		else {
			padding += alignment * (neededSpace / alignment);
		}
	}

	return padding;
}
