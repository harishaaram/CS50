#include <stdio.h>
#include <cs50.h>
#include <math.h>

/* Time for Change
This program that first asks the user how much change is owed and then spits out
the minimum number of coins */

int main(void)
{
    float n;
    int k = 0, amount = 0;
    // the below loop gets a non negative float value 

    do
    {
        printf("How much change is owed? \n");
        n = GetFloat();
        n = n * 100.0;
        
    }
    while(n < 0);
    
   
    k = round(n);
    
    // the below set of loop helps in calculating the number of coins required 
    while(k >= 25)
    {   
        amount = amount + 1;
        k = k - 25;
    }
    while(k >= 10)
    {   
        amount = amount + 1;
        k = k - 10;
    }
    while(k >= 5)
    {   
        amount = amount + 1;
        k = k - 5;
    }
    while(k >= 1)
    {   
        amount = amount + 1;
        k = k - 1;
    }
    printf("%d\n",amount);
}
