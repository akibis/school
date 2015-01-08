/* 
 * File:   main.c
 * Author: netdom
 *
 * Created on September 9, 2014, 5:30 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define BUF_SIZE 128

/*
 * This program uses low level POSIX calls to copy a file. 
 * OPEN, CLOSE, READ, WRITE
 */
int main(int argc, char** argv) {

    char* inputFile;
    char* copiedFile;
    char* buf;
    int input;
    int output;

    if (argc == 3) {
        mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;        
        inputFile = argv[1];
        copiedFile = argv[2];

        //printf("inputFile: %s\n", inputFile);
        //printf("copiedFile: %s\n", copiedFile);

        // OPEN FILE TO BE COPIED
        input = open(inputFile, O_RDONLY | O_CREAT);
        //printf("input: %d\n", input);

        // OPEN DESTINATION FILE, CREATE IF DOESN'T EXIST
        output = open(copiedFile, O_WRONLY | O_CREAT | O_TRUNC, mode);
        buf = malloc(BUF_SIZE * sizeof (char));       
        
        size_t nbytes;
        ssize_t bytes_read;
        ssize_t bytes_written;
        
        int totalBytes;
        
        // COPY FILE TEXT
        while (1) {
            nbytes = BUF_SIZE;
            bytes_read = read(input, buf, nbytes);
            totalBytes += bytes_read;
            //printf("Check: %d\n", (int) bytes_read);
            if (bytes_read < BUF_SIZE) {
                bytes_written = write(output, buf, (size_t) bytes_read);
                break;
            }
            //printf("chunkSize: %d\n", (int)bytes_read);
            bytes_written = write(output, buf, nbytes);
            //printf("%s", buf);

        }
        // PRINT TOTAL BYTES COPIED
        printf("copied %d bytes\n", totalBytes);
        
        // FREE RESOURCES
        free(buf);
        close(input);
        close(output);

        exit(EXIT_SUCCESS);
    } else {
        fprintf(stderr, "Please enter two arguments.\n");
        exit(EXIT_FAILURE);
    }


    return (EXIT_SUCCESS);
}

