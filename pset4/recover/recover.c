#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // read the file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }

    // allocate 512 BYTEs for each block
    BYTE *storage = malloc(sizeof(BYTE) * 512);

    // initialize img count, current img file and filename
    int count = 0;
    FILE *img = NULL;
    char filename[7];

    // read until EOF
    while (fread(storage, sizeof(BYTE), 512, file))
    {
        // check header for JPG signature
        // 1st byte == 0xff, 2nd byte == 0xd8, 3rd byte == 0xff  Last byte: 0xe?
        if (storage[0] == 0xff && storage[1] == 0xd8 && storage[2] == 0xff && (storage[3] & 0xf0) == 0xe0)
        {
            // if new jpg
            if (img != NULL)
            {
                // close previous file
                fclose(img);
            }

            // create new filename ###.jpg
            sprintf(filename, "%03i.jpg", count);

            // open an image file for writing
            img = fopen(filename, "w");

            // write data to the file
            fwrite(storage, sizeof(BYTE), 512, img);

            // add a counter for filename
            count++;
        }
        else
        {
            if (img != NULL)
            {
                // write data to the file
                fwrite(storage, sizeof(BYTE), 512, img);
            }
        }
    }

    // free up storage
    free(storage);

    // close final writing file
    fclose(img);

    // close read file
    fclose(file);
}
