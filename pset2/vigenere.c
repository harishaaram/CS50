/* This is Vigenere Cipher
    
   by harishgandhi */
                    
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string s, key = argv[1];
        int temp, i, l, store, k = 0;
        int n = strlen(argv[1]); 
       
       /* checking the keyword for any non-alphabetic characters */        
       
        for(i = 0;i < n; i++)
        {
            if (!isalpha(key[i]))
            {
                printf("Keyword must be only A-Z and a-z");
                return 1;
            }
        }
               
        /* get the string which needs to ciphered */   

        do
        { 
            s = GetString();
        }
        while (s == false);
        
        /* loop which deciphers using the key  */ 
          
        for(i = 0, l = strlen(s); i < l; i++)
        {
            if (isalpha(s[i]))
            {   
                key[k] = tolower(key[k]);
                store = (int) key[k];
                store = (store - 97) % 26;
                
                if (islower(s[i]))
                {   
                    temp = (int) s[i];
                    temp = (temp + store - 97) % 26;
                    temp = temp + 97;
                    s[i] = (char) temp;
                }
                if (isupper(s[i]))
                {
                    temp = (int) s[i];
                    temp = (temp + store - 65) % 26;
                    temp = temp + 97;
                    s[i] = toupper((char) temp);
                }
                k = (k + 1) % n;
            }
    }
        printf("%s\n", s);
        return 0;
    }
    else
    {
        printf("please enter a keyword!!!\n");
        return 1;
    }


}
