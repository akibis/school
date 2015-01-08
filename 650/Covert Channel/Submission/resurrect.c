/* 
 * File:   resurrect.c
 * Author: Aleksandr Kibis
 *
 * Compile: gcc -o run resurrect.c -lm
 * Run: ./run <secret html file>
 * Output: current working directory/secret.txt
 *
 * Created on October 30, 2014, 12:15 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int bin2str(char* input, int size);
int resurrect(char* html, int htmlSize);


char* messageBin;
char* messageStr;

/*
 * 
 */
int main(int argc, char** argv) {

    // exit if incorrect usage
    if (argc != 2) {
        printf("Usage: ./run <secret html file>\n");
        exit(EXIT_FAILURE);
    }

    printf("Dr. Grimm - A simple HTML covert channel extraction program.\n"
            "************** by: Aleksandr Kibis *************\n\n");

    // open files
    FILE *html = fopen(argv[1], "r");
    FILE *message = fopen("secret.txt", "w+");

    // declare vars
    long int htmlSize;
    size_t htmlRead;

    // get input file size
    fseek(html, 0L, SEEK_END);
    htmlSize = ftell(html);
    fseek(html, 0L, SEEK_SET);

    //printf("HTML Size: %d\tCONF Size: %d\n", (int) htmlSize, (int) confSize);

    // allocate buffer memory for files
    char* htmlFile = malloc(htmlSize * sizeof (char));

    htmlRead = fread(htmlFile, 1, htmlSize, html);

    //printf("HTML Size: %d\tCONF Size: %d\n", (int) htmlRead, (int) confRead);

    // close files
    fclose(html);

    // grab secret message from file
    int messageSize;
    messageSize = resurrect(htmlFile, htmlSize);

    printf("Embedded Message: %s\n", messageStr);

    // write secret message to new file
    int i, character;
    for (i = 0; i < messageSize - 1; i++) {
        character = messageStr[i];
        //putchar(character);
        fprintf(message, "%c", character);
    }

    printf("Message written to secret.txt. Exiting.\n");

    // free resources
    fclose(message);
    free(htmlFile);
    free(messageBin);
    free(messageStr);

    return (EXIT_SUCCESS);
}

int bin2str(char* input, int size) {

    //printf("Passed message: %s\n\n", input);

    int numberOfChars = size / 8;

    messageStr = malloc(numberOfChars * sizeof (char));

    int i, j;
    int val = 0;
    int power = 0;

    for (j = 0; j < numberOfChars; j++) {

        for (i = 8 * j; i < 8 * j + 8; i++) {
            //printf("%c", input[i]);
            if (input[i] == '1') {
                val += pow(2, 7 - power);
            }
            power++;
        }
        //printf("%c\n", (char) val);
        messageStr[j] = (char) val;
        val = 0;
        power = 0;
    }

    //printf("Encoded Message: %s\n", messageStr);

    return numberOfChars;
}

int resurrect(char* html, int htmlSize) {

    char* start;
    char* end;
    int messageLength, convertedLength;
    char firstTag[7] = "<!--;)";
    char secondTag[6] = "(;-->";


    // calculate message length
    end = strstr(html, secondTag);
    start = strstr(html, firstTag);
    messageLength = strlen(start) - strlen(end);

    messageBin = malloc(messageLength * sizeof (char));

    // get binary message
    int i;
    for (i = 6; i < messageLength; i++) {
        messageBin[i - 6] = start[i];
    }

    //printf("Binary Message: %s\n", message);

    convertedLength = bin2str(messageBin, messageLength - 6);

    return convertedLength;
}