#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    // If the memory card is already opened then error msg
    if (card == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[512];
    int count = 0;
    char imgname[8];

    FILE *img = NULL;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Check the first three bytes of JPEGs
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] == 0xe0)
        {
            // Thehe first JPEG
            if (count == 0)
            {
                sprintf(imgname, "%03i.jpg", count);
                img = fopen(imgname, "w");
                fwrite(&buffer, 1, 512, img);
                count += 1;
            }
            else if (count > 0)
            {
                fclose(img);
                sprintf(imgname, "%03i.jpg", count);
                img = fopen(imgname, "w");
                fwrite(&buffer, 1, 512, img);
                count += 1;
            }
        }
        // continue writing
        else if (count > 0)
        {
            fwrite(&buffer, 1, 512, img);
        }
    }
    fclose(img);
    fclose(card);
}
