# Homework Set 3

By Deng Yufan.

## Prob 1: Virtual Memory

Consider a virtual memory scheme that uses multi-level page tables, with the following format for virtual addresses: Virtual Page (10 bits), Virtual Page (10 bits), Offset (12 bits).

That means, the first-level page table uses the highest 10 bits of virtual address. The second-level page table uses the next 10 bits of virtual address.

Virtual addresses are translated into physical addresses of the following form: Physical Page (20 bits), Offset (12 bits).

Page table entries (PTE) are 32 bits in the following format, stored in big-endian form (i.e. the most significant byte has the lowest address) in memory: Physical Page (20 bits), OS Defined (3 bits), 0, Large Page, Dirty, Accessed, Nocache, Write Through, User, Writeable, Valid.

Here, "Valid" means that a translation is valid; "Writeable" means that the page is writeable; "User" means that the page is accessible by the user (rather than only by the Kernel). Note: the phrase "page table" in the following questions means the entire multi-level data structure that maps virtual addresses to physical addresses.

How big is a page?

> $2^{12}$ bytes, or 4 kB.

What is the maximum size of physical memory this system can support?

> $2^{32}$ bytes, or 4 GB.

For this scheme, what is the maximum size that a page table of a process can be (in bytes)?

> $32 * (2^{10}+2^{20})$ bits, or 4100 MB, or 4198400 bytes.

Suppose that a process has an address space with one page at the top of the address space and one page at the bottom of the address space. How big would the page table be (in bytes)?

> $32 * 1024 * 3$ bits, or 12 kB, or 12288 bytes.

Assume a process uses 512 kB of physical memory. What is the minimum size of its page table (in bytes)? What is the maximum size of its page table (in bytes)?

> #Pages: 128.
>
> Min: $32 * 1024 * 2$ bits, or 8 kB, or 8192 bytes.
>
> Max: $32 * 1024 * (1+128)$ bits, or 516 kB, or 528384 bytes.

Now we would like to add a fully-associative TLB into this system to make address translation faster. Recall that each TLB entry treats the PTE as the data, and also needs a tag and a valid bit. How many bits would each entry of such a fully-associative TLB have? Show your progress to reach the answer.

> Tag: 20 bits, Valid Bit: 1bit, Info: 32 bits. Total: 53 bits.

## Prob 2: Paging

A main memory consists of four physical pages (frames), denoted as i, ii, iii, iv. Assume the LRU page replacement algorithm, and initially all physical frames are empty.

Consider the following access stream of virtual pages A, B, C, D, E, C, A, B, C, D, F.

Fill in the following table showing all page faults. In each column, if a page fault occurs for this access, fill the virtual page name (e.g., A, B) in the cell of the row that corresponds to the physical frame (e.g., i, ii) to which this page will be paged to.

What is the total number of page faults?

> $\space$ | A | B | C | D | E | C | A | B | C | D | F
> :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---:
> i | A | A | A | A | E | E | E | E | E | D | D
> ii | | B | B | B | B | B | A | A | A | A | F
> iii | | | C | C | C | C | C | C | C | C | C
> iv | | | | D | D | D | D | B | B | B | B
>
> 9 times.

What is the minimum memory size (in number of physical frames) such that the number of faults to be no larger than 6? Explain.

> The answer is 5. Since A-F is exactly 6, we can't forget a unfinished page. Since the leading sequence is A, B, C, D, E, C, A, we need to remember A-E until A is hit again. So at least 5, and easy to see 5 is valid since F only occor in the last.

## Prob 3: Disks

Average and minimum times for reading and writing to storage devices are common measurements used to compare devices. Calculate values related to read and write times for disks with the following characteristics. These latencies start from the access request is issued to the device controller, until the data transfer is completed. Disk transfer and controller transfer are not pipelined.

$\space$ | Average seek time | RPM | Disk transfer rate | Controller transfer rate
:---: | :---: | :---: | :---: | :---:
a. | 11ms | 7200 | 36 MB/s | 500 Mbit/s
b. | 9ms | 7200 | 32 MB/s | 520 Mbit/s

Calculate the average time to read or write a 1024 byte sector for each disk listed in the table.

> a. $11 + 1/2 * 60000/7200 + 1000/36k + 8000/500k$, or 15.209 ms.
>
> b. $9 + 1/2 * 60000/7200 + 1000/32k + 8000/520k$, or 13.212 ms.

Calculate the minimum time to read or write a 2048 byte sector for each disk listed in the table.

> a. $0 + 0 + 2000/36k + 16000/500k$, or 85.503 $\mu$s.
>
> b. $0 + 0 + 2000/32k + 16000/520k$, or 91.083 $\mu$s.

For each disk in the table, determine the dominant factor for performance. Specifically, if you could make an improvement to any aspect of the disk, what would you choose? If there is no dominant factor, explain why. Hint: consider different access patterns.

> If access pattern is randomly, dominant is seek time.
>
> If access pattern is sequential, dominant is RPM (maybe also disk transfer rate if access a huge data like 1MB).

## Prob 4: I/O Notification

An important advantage of interrupts over polling is the ability of the processor to perform other tasks while waiting for communication from an I/O device. Suppose that a 1 GHz processor needs to read 1000 bytes of data from a particular I/O device. The I/O device supplies 1 byte of data every 0.02 ms. The code to process each byte of data after receiving and store it in a buffer takes 100 cycles.

If the processor detects whether a byte of data is ready by keeping polling without sleep, and one poll takes 50 cycles, how many cycles does the entire operation (i.e., reading all 1000 bytes) take? How many polls will the processor do in total? Assume that only after one byte arrives can one poll successfully find the byte, and the first byte arrives right before the first poll.

> Take: $999 * 20000 + 150 = 19980150$ cycles.
>
> Polls occurs: $1+999*(20000-100)/50=397603$ times.

If instead, the processor is interrupted when a byte is ready, and the processor spends the time between interrupts on another task, how many cycles of this other task can the processor complete while the I/O communication is taking place? The overhead for handling an interrupt is 200 cycles. During each interrupt, we process the byte and store it in a buffer as mentioned above.

> $999*19700=19680300$ cycles.

## Prob 5: File Systems

Consider a UNIX file system. Disk blocks are 4096 bytes. Sectors are 512 bytes long. All block pointers are 32-bit long. An inode has 12 direct block pointers, one indirect block pointer, and one double-indirect block pointer. Both indirect and double-indirect blocks take up an entire disk block. The total inode size is 256 bytes.

How much disk space, including metadata and data blocks, is needed to store a 4 GB DVD image file? Show your calculation.

Give your answer in bytes. When accounting for the inode, because multiple inodes can share a single block, we only count 256 bytes rather than a full block.

> #Blocks for DVD: $2^{20}$.
>
> #Pointers for a block: $2^{10}$.
>
> Block store: 4kB.
>
> Indirect block store: 4MB.
>
> Double-indirect block store: 4GB.
>
> Answer: $256+(2^{20}+2^{10}+1)*4096=4299165952$ bytes.

What is the maximum file size (in bytes) that can be stored in this file system?

> $(2^{20}+2^{10}+12)*4096=4299210752$ bytes.

Assume that there is no buffer cache, i.e., no filesystem structures or data are cached by OS in main memory. starting from the i-number, how many disk accesses will be required to read only the last byte in this file? How about to overwrite it? Show your calculations. Each access can get an entire disk block.

> Read: Inode, Double-indirect block, indirect block, block. 4 accesses.
>
> Overwrite: 5 accesses, need to write back the block.

Suppose that among all files in the file system, half of them are 3 kB and the other half are 8 kB. Considering only disk space used to store data and ignoring metadata and directory structures, what is the space overhead, in terms of the ratio of allocated space vs. actual data size? How about on a disk with 2 kB block size?

> 4kB block size: 12/11.
>
> 2kB block size: Also 12/11.

In UNIX-like operating systems, the command ``mv`` can move a file from one directory to another. For example, "``mv /a/b/c /d/e/f``". Please explain how many blocks are changed in this ``mv`` command, and what are they? You do not need to consider timestamp changes in this question.

> Only the blocks stored file pointer before and after, 2 blocks.

Consider the following set of file system metadata: directory, file metadata (e.g., inode + (double-)indirect blocks), free map. Which one(s) need to be changed to add link supports in a file system? How?

1. To support soft (symbolic) links.

   > Directory: A new file.
   > 
   > File metadata: A new inode and so on correspond to the new file.
   > 
   > Free map: Delete just used blocks by new file and new metadata.

2. To support hard links.

   > Directory: A new name.
   >
   > File metadata: Add 1 to inode link count.
