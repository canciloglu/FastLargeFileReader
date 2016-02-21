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
    static const size_t BUFFER_SIZE = 16*1024;
    int fd = open(fileName, O_RDONLY);
    if(fd == -1){
    	handleError("Failed to open");
    }

    char buffer[BUFFER_SIZE + 1];
    uintmax_t lineCount = 0;

    while(size_t byteCount = read(fd, buffer, BUFFER_SIZE))
    {
        if(byteCount == (size_t)-1){
            handleError("Failed to read");
        }

        if (!byteCount){
            break;
        }

        for(char *bytePointer = buffer; (bytePointer = (char*) memchr(bytePointer, '\n', (buffer + byteCount) - bytePointer)); ++bytePointer){
            lineCount++;
        }
    }

    return lineCount;
}




