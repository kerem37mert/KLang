#include <stdio.h>

int main(int argc, char *argv[]) {

    if(argc != 2) {
        printf("ERROR! Invalid command line argument count.\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("[ERROR] Unable to find file with path:.\n");
        return 1;
    }



    fclose(file);

    return 0;
}

