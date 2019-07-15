#pragma once

#include <cstddef>

class Allocator
{
public:

    Allocator(std::size_t size);
    virtual ~Allocator();
    virtual void* Allocate(std::size_t size, std::size_t alignment = 4) = 0;
    virtual void Deallocate(void* address) = 0;
	virtual void Reset() = 0;
    inline void* GetStart() const { return m_Start; }
    std::size_t GetSize() const { return m_Size; }
    std::size_t GetMemoryUsed() const { return m_MemoryUsed; }

protected:

    void* m_Start;
    std::size_t m_Size;
	std::size_t m_MemoryUsed;
	std::size_t Align(std::size_t address, std::size_t alignment) const;
	std::size_t AlignHeader(std::size_t address, std::size_t alignment, std::size_t header_size) const;
};