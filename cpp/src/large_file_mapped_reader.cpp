/*
 * main.cpp
 *
 *  Created on: Feb 21, 2016
 *      Author: Can Ciloglu
 */
#include <algorithm>
#include <iostream>
#include <chrono>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>

void handleError(const char* error);
uintmax_t readFile(char const *fileName);
const char* mapFile(const char* fname, size_t& length);

int main()
{
	unsigned long start =
	    std::chrono::system_clock::now().time_since_epoch() /
	    std::chrono::milliseconds(1);

	uintmax_t lineCount = readFile("136mb.txt");

	unsigned long end =
	    std::chrono::system_clock::now().time_since_epoch() /
	    std::chrono::milliseconds(1);

    std::cout << "Number of lines = " << lineCount << " processed in " << (end-start) << " ms";
}

void handleError(const char* error) {
    perror(error);
    exit(255);
}


uintmax_t readFile(char const *fileName)
{
	size_t length;
	const char* address = mapFile("136mb.txt", length);
	const char* memLength = address + length;

    uintmax_t lineCount = 0;

	while (address && address!=memLength){
	    if ((address = static_cast<const char*>(memchr(address, '\n', memLength-address)))){
	    	lineCount++, address++;
	    }
	}

    return lineCount;
}

const char* mapFile(const char* fileName, size_t& length)
{
    int fd = open(fileName, O_RDONLY);
    if (fd == -1){
        handleError("Failed to open");
    }

    struct stat fileStat;

    if (fstat(fd, &fileStat) == -1){
        handleError("Failed to call fstat");
    }

    length = fileStat.st_size;

    char* address = (char*)mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0u);

    if (address == MAP_FAILED){
        handleError("Map failed");
    }

    madvise(address, fileStat.st_size, MADV_SEQUENTIAL|MADV_WILLNEED);

    return address;
}




