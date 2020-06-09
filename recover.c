#include <stdio.h>
#include <stdlib.h>

// Recovers image

int main(int argc, char *argv[])
{
    // Check number of passing arguments
    if (argc != 2)
    {
        printf("%s\n", "You should input name of the file.");
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "r");

    // Check if file can be opened
    if (file == NULL)
    {
        printf("%s\n", "Cannot open a file!");
        return 1;
    }

    int jpgs_counter = 0;
    unsigned char buffer[512];
    FILE *img;
    int n;

    // Read file till the end
    while ((n = fread(buffer, sizeof(unsigned char), 512, file)) != 0)
    {

        // Find start of the JPG file and recover it
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (jpgs_counter == 0)
            {
                char filename[8];
                sprintf(filename, "%03i.jpg", jpgs_counter);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(unsigned char), n, img);
                jpgs_counter += 1;
            }
            else
            {
                fclose(img);
                char filename[8];
                sprintf(filename, "%03i.jpg", jpgs_counter);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(unsigned char), n, img);
                jpgs_counter += 1;
            }
        }

        else
        {
            fwrite(buffer, sizeof(unsigned char), n, img);
        }
    }
}
