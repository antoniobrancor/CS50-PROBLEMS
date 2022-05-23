#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    BYTE *o[100];
    BYTE c;
    BYTE *p = NULL;

    int i = 0;
    while (fread(&c, sizeof(BYTE), 1, file) == sizeof(BYTE))
    {
        BYTE *u = malloc(sizeof(BYTE *));
        i++;
        u = &c;
        p = u;
        printf("%x \n", *p);
    }

    int j = 0;
    int number[100];
    for (i = 0; i < 506368; i++)
    {
        if (p[i] == 0xff)
        {
            if (p[i + 1] == 0xd8)
            {
                if (p[i + 2] == 0xff)
                {
                    if ((p[i + 3] & 0xf0) == 0xe0)
                    {
                        o[j] = &(p[i]);
                        j++;
                    }
                }
            }
        }
        number[j]++;
    }
    for (int k = 0; k < 50; k++)
    {
        char *filename = malloc(8 * sizeof(char));
        sprintf(filename, "%03i.jpg", k);
        FILE *img = fopen(filename, "w");
        fwrite(o[k], sizeof(BYTE), number[k], img);
        free(filename);
    }
    fclose(file);
}