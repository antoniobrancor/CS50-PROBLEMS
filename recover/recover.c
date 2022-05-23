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
    BYTE block[512];
    int jpgcount = 0;
    FILE *img;

    for (int i = 0; fread(&block, 512, 1, file) > 0; i++)
    {
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            if (jpgcount > 0)
            {
                fclose(img);
            }
            char *filename = malloc(8 * sizeof(char));
            sprintf(filename, "%03i.jpg", jpgcount);
            img = fopen(filename, "a");
            fwrite(&block, 1, sizeof(block), img);
            free(filename);
            jpgcount++;
        }
        else if (jpgcount > 0)
        {
            fwrite(&block, 1, sizeof(block), img);
        }
    }
    fclose(img);
}