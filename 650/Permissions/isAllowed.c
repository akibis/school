// scans permissions file for user id
// returns 1 if found, 0 if not

int allowedAccess(int userId, const char* name) {
    FILE *fd;
    char* buf;
    char* token;
    char userIdString[20];
    char user[5];
    char tokenDelim[2] = "\n";
    int retval, ch;
    int fileSize = 0;
    
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
            if(strcmp(token, name) == 0){
                //printf("FILE RULE FOUND!\n");
                //printf("**** token: %s ****\n", token);
                token = strtok(NULL, tokenDelim);
                //printf("token: %s\n", token);
                foundFlag = 1;
                
            }
            
            // return permissions if user id is found within 
            // specific file block
            if ((strcmp(token, userIdString) == 0) && foundFlag){
                token = strtok(NULL, tokenDelim);
                printf("Permissions: %s\n", token);
                break;
            }
            
            // reset found flag if next file is reached
            if((int)(token[0]) > 65 && (int)(token[0]) < 122){
                foundFlag = 0;
            }
            //printf("token: %s\n", token); 
            
        // grab next token    
        token = strtok(NULL, tokenDelim);
    }

    // return whether user can write to file
        switch (atoi(token)){
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
