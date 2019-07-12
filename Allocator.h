#pragma once

class Allocator
{
public:

    Allocator(size_t size, void* start);
    virtual ~Allocator();
    virtual void Allocate(size_t size, u8 alignment = 4) = 0;
    virtual void Deallocate(void* address) = 0;
    inline void* GetStart() const { return m_Start; }
    size_t GetSize() const { return m_Size; }
    size_t GetMemoryUsed() const { return m_MemoryUsed; }
    size_t GetAllocationCount() const { return m_AllocationCount; }
    u8 GetAlignmentAdjust(void* address, u8 alignment);

protected:

    void* m_Start;
    size_t m_Size;
    size_t m_MemoryUsed;
    size_t m_AllocationCount;
};