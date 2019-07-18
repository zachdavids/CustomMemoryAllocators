# Custom Memory Allocators
****
A collection of custom memory allocators used frequently in game engines. Memory allocation via malloc() or by operator new is very slow, however the performance of dynamic memory allocation can be greatly improved by satisfying requests from a pre-allocated memory block avoiding expensive context switches using custom memory allocators.

### Linear Allocator

The linear allocator stores an offset to the first unused memory address and allows for allocations of any size, each incrementing the offset by the appropriate amount. Freeing individual blocks of allocated memory is not permitted and therefore the entire block of memory must be cleared.

Allocation Complexity: O(1)  
Deallocation Complexity: N/A  
Storage Complexity: O(n), where n is the requested allocation size 

### Stack Allocator

The stack allocator also stores an offset to the first unused memory address however includes the used of the header at beginning of each allocated memory chunk which stores the block's alignment shift. The size of individual blocks is the requested allocation size plus the header size. It allows for allocations of any size and increments the offset by the appropriate amount. Unlike the linear allocator, the stack allocator allows for individual the deallocation of individual blocks in a stack-like fashion (FILO) where the most recently allocated block is freed first.

Allocation Complexity: O(1)  
Deallocation Complexity: O(1)  
Storage Complexity: O(n*h), where n is the requested allocation size, h is the header size

### Double Buffered Allocator

A double buffered allocator is constructed from two stack allocators and is useful for caching results of asynchronous processing on multicore systems. Every frame the active stack is switched and the newly active stack cleared, leaving the inactive stacks's data from last frame intact for use for use during the current frame.

Allocation Complexity: O(1)  
Deallocation Complexity: O(1)  
Storage Complexity: O(n*h), where n is the requested allocation size, h is the header size

### Pool Allocator

Unlike the linear or stack allocator, the pool allocator allows for allocations of only a single size. Upon initialization of a linked list, the complete memory block is segmented into uniform blocks whose addresses are stored in a singly-linked list called a free list. When an allocation is requested a block is removed from the free list and given to the user for use. Similarly deallocations returns the specified block to the free list for later reuse and can occur in any order.

Allocation Complexity: O(1)  
Deallocation Complexity: O(1)  
Storage Complexity: O(n), where n is the requested allocation size

### Free List Allocator

The free list allocator mimics malloc in that it allows for allocations of any size and also deallocations in any order. Like the pool allocator the free list also uses a singly-linked list to store the size of unused chunks of memory. When an allocation request is made, the free list is searched for the first block with a size equal to or greater than the requested size. If an appropriate block is found a header is inserted at the beginning of the block containing the alignment shift and block size and the address to useable memory is returned to the user. If the block of memory is larger than the requested block size, it is split, and the block containing the remaining space is added to the free list. Deallocations work similarly, with blocks of previously allocated memory being added back to the free list sorted by memory address, we then run a defragment function after dealloction to combine any two contiguous blocks into a single larger block.

Allocation Complexity: O(n), where n is the size of the free list  
Deallocation Complexity: O(n), where n is the size of the free list  
Storage Complexity: O(n*h), where n is the requested allocation size, h is the header size

