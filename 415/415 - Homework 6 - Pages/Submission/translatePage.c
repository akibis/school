/* 
 * File:   translatePage.c
 * Author: Aleksandr Kibis
 * 
 * Compile: gcc -o run translatePage.c
 * Run: ./run <0x00000000>
 * 
 * This program takes in a 32-bit signed hex number. Outputs page number 
 * and offset for 8KB page size.
 *
 * Created on November 8, 2014, 2:10 PM
 */

#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define PAGE_SIZE 8192

void getInfo(const char* virtualAddress);

/*
 * 
 */
int main(int argc, char** argv) {

    if (argc != 2){
        printf("Usage: ./run <0x00000000>\n");
        exit(EXIT_FAILURE);
    }
    
    // get paging and offset info 
    const char* hexstring = argv[1];
    getInfo(hexstring);
       
    return (EXIT_SUCCESS);
}

void getInfo(const char* virtualAddress){
    int address = (int)strtol(virtualAddress, NULL, 0);

    // page number
    int pageNumber = address / PAGE_SIZE;
    
    // offset
    int offset = address % PAGE_SIZE;
    
    // virtual address: used to check correct calculation
    int virtual = PAGE_SIZE * pageNumber + offset;
        
    // write back as hex
    printf("Virtual Address: 0x%x\nPage Size: %dKB\nPage Number: 0x%x\nOffset: 0x%x\n", 
            virtual, PAGE_SIZE / 1024, pageNumber, offset);
}

