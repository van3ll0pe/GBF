#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*          PROTOTYPES         */
int read_file(char *file_name, char **buffer);
int brainfuck(char *file_name);
int count_loop(char *buffer, int **saveLoop);
/*******************************/

int read_file(char *file_name, char **buffer) {
    FILE *file = NULL;
    struct stat info_file;
    int sizeBuffer = 0;

    stat(file_name, &info_file);
    sizeBuffer = info_file.st_size;
    (*buffer) = malloc(sizeof(char) * (sizeBuffer)+1);
    if (*buffer == NULL) {
        return (1);
    }
    file = fopen(file_name, "r");
    if (file == NULL) {
        return (1);
    }
    fread((*buffer),sizeBuffer,1, file);
    (*buffer)[sizeBuffer] = '\0';
    fclose(file);
    
    return (0);
}

int count_loop(char *buffer, int **saveLoop) {
    int sizeLoop = 0;
    for (int i = 0; buffer[i]; i++) {
        if (buffer[i] == '[') {
            sizeLoop++;
        }
    }

    (*saveLoop) = malloc(sizeof(int) * sizeLoop);
    if (*saveLoop == NULL) {
        return (1);
    }
    return (0);
}

int brainfuck(char *file_name) {
    int memory[30000] = {0};    //stock les valeurs
    int *ptr = memory;          //se promène dans le tableau memory
    char *buffer = NULL;        //stock ce qu'il y a dans le fichier
    int *saveLoop = NULL;       //stock les entrées de boucles
    int iLoop = -1;             //se promène dans saveLoop
    int i = 0;                  //Se promène dans buffer

    if (read_file(file_name, &buffer) == 1) {
        return (1);
    }
    if (count_loop(buffer, &saveLoop) == 1) {
        return (1);
    }

    while (buffer[i] != '\0') {
        switch(buffer[i]) {
            case '+':   if ((*ptr) < 128) {
                            (*ptr)++;
                        }
                        break;

            case '-':   if ((*ptr) > 0) {
                            (*ptr)--;
                        }
                        break;

            case '>':   if (ptr < &memory[30000]) {
                            ptr++;
                        }
                        break;

            case '<':   if (ptr > &memory[0]) {
                            ptr--;
                        }
                        break;

            case '.':   putchar((*ptr));
                        break;

            case ',':   (*ptr) = getchar();
                        break;

            case '[':   if ((*ptr) == 0) {
                            int count = 1;
                            while (count != 0) {
                                i++;
                                if (buffer[i] == '[') {
                                    count++;
                                }
                                else if (buffer[i] == ']') {
                                    count--;
                                }  
                            }
                        } else {
                            iLoop++;
                            saveLoop[iLoop] = i;
                        }
                        break;

            case ']':   i = saveLoop[iLoop]-1;
                        iLoop--;
                        break;

            default :   break;
        }
        i++;
    }
    printf("\n");

    saveLoop = NULL;
    buffer = NULL;
    return (0);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return (EXIT_FAILURE);
    } else {
        if (brainfuck(argv[1]) == 1) {
            return (EXIT_FAILURE);
        }
    }
    return (EXIT_SUCCESS);
}