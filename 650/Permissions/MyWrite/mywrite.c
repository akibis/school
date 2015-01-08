/* 
 * File:   mywrite.c
 * Author: Aleksandr Kibis
 * 
 * Compile: gcc -o run mywrite.c
 * Run: ./run <text file name>       *** NOTE: FILE NAME CANNOT START WITH A NUMBER
 * 
 * 
 * This program opens a requested file for writing, given that the user
 * has permissions to do so. 1 command line argument is taken, that is the
 * name of the file wished to be opened for writing.
 * 
 * PERMISSIONS:
 *  none    = 0
 *  r       = 1
 *  w       = 2
 *  rw      = 3
 * 
 * PERMISSIONS FILE:
 * <file name 1>
 * <user id 1> 
 * <permissions>
 * <user id 2> 
 * <permissions>
 * ...
 * <file name 2>
 * <user id 1>
 * <permissions>
 * <user id 2>
 * <permissions>
 * ...
 * ...
 *
 * Created on November 17, 2014, 8:23 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

FILE loadPermissionsFile();
int allowedAccess(int userId, const char* name);

/*
 * 
 */
int main(int argc, char** argv) {

    int isAllowed;
    int userId = getuid();
    //printf("user id: %d\n", userId);

    isAllowed = allowedAccess(userId, argv[1]);

    if (isAllowed) {
        //printf("Write is allowed.\n");
        ssize_t bytesWritten;
        int fd;
        char* fileName = argv[1];
        char writeString[29] = "Test string to write to file\n";
        //printf("file name: %s\n", fileName);
        fd = open(fileName, O_WRONLY | O_CREAT | O_APPEND, S_IWUSR);
        bytesWritten = write(fd, writeString, 29);
        //printf("%s\n", writeString);
        printf("Bytes written: %d\n", (int)bytesWritten);
        close(fd);
        
    } else {
        printf("Permission denied.\n");
        exit(EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}
// scans permissions file for user id
// returns 1 if access is allowed, 0 if not

int allowedAccess(int userId, const char* name) {
    FILE *fd;
    char* buf;
    char* token;
    char userIdString[20];
    char user[5];
    char tokenDelim[2] = "\n";
    int retval, ch;
    int fileSize = 0;

    // convert int to string
    sprintf(userIdString, "%d", userId);

    //printf("BLAH: %s\n", name);

    // read permissions file into memory
    fd = fopen("permissions", "r");
    while (1) {
        ch = fgetc(fd);
        if (ch == EOF)
            break;
        ++fileSize;
    }
    rewind(fd);
    buf = malloc(fileSize * sizeof (char));

    size_t readCount;
    readCount = fread(buf, 1, fileSize, fd);

    //printf("File: %s\n", buf);
    fclose(fd);

    // tokenize file, scan for user id, return permissions
    retval = sprintf(user, "%d", userId);

    // break up permissions file into file-chunks
    int foundFlag = 0; // 0 not found, 1 at uid, 2 at permissions
    token = strtok(buf, tokenDelim);
    while (token != NULL) {


        // find file name in permissions
        if (strcmp(token, name) == 0) {
            //printf("FILE RULE FOUND!\n");
            //printf("**** token: %s ****\n", token);
            token = strtok(NULL, tokenDelim);
            //printf("token: %s\n", token);
            foundFlag = 1;

        }

        // return permissions if user id is found within 
        // specific file block
        if ((strcmp(token, userIdString) == 0) && foundFlag) {
            token = strtok(NULL, tokenDelim);
            //printf("Permissions: %s\n", token);
            break;
        }

        // reset found flag if next file is reached
        if ((int) (token[0]) > 65 && (int) (token[0]) < 122) {
            foundFlag = 0;
        }
        //printf("token: %s\n", token); 

        // grab next token    
        token = strtok(NULL, tokenDelim);
    }

    // return whether user can write to file
    switch (atoi(token)) {
        case 0:
            //printf("User has no permissions.\n");
            return 0;
        case 1:
            //printf("User has read permissions.\n");
            return 0;
        case 2:
            //printf("User has write permissions.\n");
            return 1;
        case 3:
            //printf("User has read and write permissions.\n");
            return 1;
        default:
            return 0;
    }

}