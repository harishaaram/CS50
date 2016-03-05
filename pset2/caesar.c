/* This is Caesar Cipher
    
   by harishgandhi */
                    
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{

    if (argc > 2)
        return 1;
    else
    {
        if (argc != 1)
        {
            string s;
            int temp, k = atoi(argv[1]);
            do
            { 
                s = GetString();
            }
            while (s == false);
            for(int i = 0, l = strlen(s); i < l; i++)
            {
                if (islower(s[i]))
                {
                    temp = (int) s[i];
                    temp = (temp + k - 97) % 26;
                    temp = temp + 97;
                    s[i] = (char) temp;
                }
                if (isupper(s[i]))
                {
                    temp = (int) s[i];
                    temp = (temp + k - 65) % 26;
                    temp = temp + 97;
                    s[i] = toupper((char) temp);
                }
        }
            printf("%s\n", s);
            return 0;
        }
        else
        {
            printf("please enter a key output!!!\n");
            return 1;
        }
    }

}
