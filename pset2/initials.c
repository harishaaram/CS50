/* 
    Program to find the intials of the given name
    
    written by - harishgandhi */
                        
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string s;
    do
    {
        s = GetString();
    }
    while(s == false);
    printf("%c", toupper(s[0]));
    for(int i = 0, n = strlen(s);i < n;i++)
        if (s[i] == ' ')
            printf("%c", toupper(s[i + 1]));
    printf("\n");
        
}

