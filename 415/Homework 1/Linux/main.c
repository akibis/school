/* 
 * File:   main.c
 * Author: netdom
 *
 * Created on August 29, 2014, 5:49 AM
 */

#include <unistd.h>
#include <stdio.h>

#define NAME "Aleksandr Kibis"
int main() {
    char buf[50]; // create array to hold string
    int n;  // number of bytes written to buffer and by write function
    ssize_t check; // error check

    n = sprintf(buf, "Hello %s, welcome to 415!", NAME);
    
 //   printf("%d\n", n);

    check = write(1,buf,n);

    return (0);
}
