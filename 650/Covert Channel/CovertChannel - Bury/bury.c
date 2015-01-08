/* 
 * File:   bury.c
 * Author: Aleksandr Kibis
 *
 * Compile: gcc -o run bury.c
 * Run: ./run <html file> <confidential file>
 * Output: current working directory/output.html 
 *
 * Created on October 30, 2014, 12:15 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int str2bin(char* input, int size);
int bury(char* html, char* secret, int htmlSize, int secretSize);

char* binaryFile;
char* ourSecret;

/*
 * 
 */
int main(int argc, char** argv) {

    // exit if incorrect usage
    if (argc != 3) {
        printf("Usage: ./run <html file> <confidential file>\n");
        exit(EXIT_FAILURE);
    }

    printf("Dr. Grimm - A simple HTML covert channel program.\n"
            "************** by: Aleksandr Kibis *************\n\n");

    // open files
    FILE *html = fopen(argv[1], "r");
    FILE *conf = fopen(argv[2], "rb");

    // declare vars
    long int htmlSize, confSize;
    size_t htmlRead, confRead;

    // get input file size
    fseek(html, 0L, SEEK_END);
    fseek(conf, 0L, SEEK_END);
    htmlSize = ftell(html);
    confSize = ftell(conf);
    fseek(html, 0L, SEEK_SET);
    fseek(conf, 0L, SEEK_SET);

    //printf("HTML Size: %d\tCONF Size: %d\n", (int) htmlSize, (int) confSize);

    // allocate buffer memory for files
    char* htmlFile = malloc(htmlSize * sizeof (char));
    char* confFile = malloc(confSize * sizeof (char));

    htmlRead = fread(htmlFile, 1, htmlSize, html);
    confRead = fread(confFile, 1, confSize, conf);

    //printf("HTML Size: %d\tCONF Size: %d\n", (int) htmlRead, (int) confRead);

    // close files
    fclose(html);
    fclose(conf);

    // check whether confidential file is binary or not
    printf("Is the confidential file binary? (1 for YES or 2 for NO): ");
    int ch;


    // if yes, continue
    int loop = 1;
    int scanSize, binarySize, secretWritten;

    do {
        scanSize = scanf(" %d", &ch);
        //printf("Chars scanned: %d\n", scanSize);
        if (ch == 1) {
            printf("Confidential file is binary.\n");
            sleep(1);
            printf("Burying in HTML file.");
            secretWritten = bury(htmlFile, binaryFile, htmlSize, binarySize);
            printf("Burial complete!\n");            
            loop = 0;
        }// if no, convert to binary first
        else if (ch == 2) {
            printf("Confidential file is NOT binary.\n");
            sleep(1);
            binarySize = str2bin(confFile, (int) confSize);
            sleep(1);
            printf("Burying in HTML file.\n");
            sleep(1);
            secretWritten = bury(htmlFile, binaryFile, htmlSize, binarySize);
            printf("\nBurial complete! New File: output.html\n");
            loop = 0;
        } else {
            printf("Incorrect input, please choose 1 or 2.\n");
            loop = 1;
        }
    } while (loop);

    // free resources
    free(htmlFile);
    free(confFile);
    free(binaryFile);
    free(ourSecret);

    return (EXIT_SUCCESS);
}

int str2bin(char* input, int size) {
    //printf("String: %s\nSize: %d\n", input, size);
    int* binbuf = malloc(8 * sizeof (int));
    char* charbuf = malloc(8 * sizeof (char) + 1);
    binaryFile = (char*)calloc((8 * size) + 1, sizeof (char));
    int i, j;

    memset(binaryFile, '\0', 8 * size + 1);

    printf("Converting to binary.\n");

    for (i = 0; i < size; i++) {

        char a = input[i];
        //printf("char: %c\n", a);


        // logic borrowed from http://stackoverflow.com/questions/18327439/printing-binary-representation-of-a-char-in-c#
        for (j = 0; j < 8; j++) {
            // shift a left by i, and with most significant bit, flip twice
            binbuf[j] = !!((a << j) & 0x80);
            charbuf[j] = '0' + binbuf[j];
        }
        charbuf[8] = '\0';
        //printf("Char buf: %s\n", charbuf);

        strcat(binaryFile, charbuf);
    }
    sleep(1);
    printf("Conversion complete!\n");


    free(binbuf);
    free(charbuf);

    return 8 * size + 1;
}

int bury(char* html, char* secret, int htmlSize, int secretSize){    

    int outputSize = htmlSize + secretSize + 11;       
    //printf("htmlSize: %d\tsecretSize: %d\tourSecret: %d\n", htmlSize, secretSize, outputSize);
    
    // allocate memory for appended html file
    char* ourSecret = (char*)calloc(outputSize, sizeof(char));
    memset(ourSecret, '\0', outputSize);

    // write comment tag + signature
    char part1[7] = "<!--;)";
    strcat(ourSecret, part1);
    
    // write secret message
    strcat(ourSecret, secret);
    char part2[6] = "(;-->";
    
    // append closing tag and rest of html code
    strcat(ourSecret, part2);
    strcat(ourSecret, html);
    //printf("Our Secret: %s\n", ourSecret);
    
    FILE *output = fopen("output.html", "w+");
    
    // write to html file
    int i, character;
    for(i=0; i < outputSize-1; i++){
        character = ourSecret[i];
        //putchar(character);
        fprintf(output, "%c", character);
    }

    fclose(output);
    
    return outputSize;
}