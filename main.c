////////////////////////////////////
//                                //
//                                //
//                                //
//                                //
//           MAIN FILE            //
//                                //
//                                //
//                                //
//                                //
////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"


// RUN FUNCTION
void run(const char* filePath)
{
    FILE* file = fopen(filePath, "r");
    if (file == NULL)
    {
        printf("[ERROR] Unable to find file with path: %s\n", filePath);
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* source = (char*)malloc(fileSize + 1);
    fread(source, 1, fileSize, file);
    source[fileSize] = '\0';


    /*  */
    struct Token *token = scanTokens(source);
    while(token != NULL) {
        printf("%s", token->value);
        token = token->next;
    }


    fclose(file);
    free(source);
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("[ERROR] Invalid command line argument count.\n");
        return 1;
    }

    char* filePath = argv[1];
    size_t length = strlen(filePath);
    if (length < 3 || strcmp(filePath + length - 2, ".k") != 0)
    {
        printf("[ERROR] Invalid file extension. File must have a .k extension.\n");
        return 1;
    }

    run(argv[1]);
    return 0;
}
