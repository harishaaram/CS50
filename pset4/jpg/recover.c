/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 * by HARISHGANDHI
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    int jpgname = 0;
    char title[10];
    uint8_t buffer[512];
    
    FILE* file = fopen("card.raw", "r");
    FILE* img = NULL;
    
    //Check for file content
    if (file == NULL)
    {
        printf("Could not open %s.\n", "card.raw");
        return 2;
    }

    //check till end of file
    while(!feof(file))
    {
    
    //jpeg signature condition
    if((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] == 0xe0) || (buffer[3] == 0xe1)))
    {
        if(img != NULL)
            fclose(img);
            
        // naming the jpg file
        sprintf(title,"%03d.jpg",jpgname);
        img = fopen(title, "a");
        jpgname++;
        
        //writing new file buffer
        fwrite(buffer, 512, 1, img);
    }
    else if(jpgname > 0)
        fwrite(buffer, 512, 1, img);            
    
    fread(buffer, sizeof(buffer), 1, file);
    }
        
    fclose(file);
    return 0;
    }


