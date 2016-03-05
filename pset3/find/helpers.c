/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include<stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // binary search

    sort(values, n);
    int first = 0, last = n, mid;
    do
    {
        mid = (first + last)/2;
        if( value < values[mid])
            last = mid - 1;
        else if( value > values[mid])
            first = mid + 1;
        
    }while(values[mid] != value && first <= last);
    
    if( values[mid] == value)
        return true;
    else
        return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    for(int i = 0, temp; i < n; i++ )
    {
        for(int j = 0 ; j < n - i - 1; j++)
        {
            if( values[j] > values[j+1])
                {
                    temp = values[j];
                    values[j] = values[j+1];
                    values[j+1] = temp;               
                }
        }
    }
    return;
}
