#include <stdio.h>
#include <cs50.h>

// This is a half pyramid for mario

int main(void)
{
// marker indentifies the location of the cursor for a given row  
    int n, marker;
    
// the below loop gets a integer within 0 to 23  

    do
    {
        printf("Enter a non negative height value, no greater than 23 \n");
        n = GetInt();
        
    }
    while(n < 0 || n > 23);
    
// this for-loop prints the required pyramid of height n 

    for(int i=0;i < n;i++)
    {
        marker = 0;
        while(marker < (n - i - 1))
        {
            printf(" ");
            marker = marker + 1;
        }
        marker = 0;
        while(marker < (i + 2))
        {
            marker = marker + 1;
            printf("#");
        }
        printf("\n");
    }
}

