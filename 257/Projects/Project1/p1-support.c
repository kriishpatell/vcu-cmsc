#include "p1-support.h"
#include <stdio.h>
#include <string.h>

/* *********************************************************************
* File          : p1support.c
* Description   : This is a set of general-purpose utility functions
*                 we use for the 257 project #1. Fall 2022
* Author        : Krish Patel
* Date          : 10/9/2022
* Notes         : 
* **********************************************************************/

// this function prints out the array of integer values
void display_array(unsigned int arr[], int size){
  int i;
  printf("{");
  for(i = 0; i < size; i++){
    printf("%4d%s",arr[i],(i==9)?"":",");
  }
  printf("}\n");
}

// this function adds two integer parameters together
int bitwise_add(int num1, int num2)
{
  while(num2 != 0){
    unsigned carry = num1 & num2;
    num1 = num1 ^ num2;
    num2 = carry << 1;
  }
  return num1; 
}

// this function shifts the first parameter to the left by the amount of the second parameter
int bitwise_shift_left(int num1, int num2){
  return num1 << num2; 
}

// this function returns the number of 1s in the binary representation of the number
int count_set_bits(int num){
  unsigned int sum = 0;
  while(num){
    sum += num & 1;
    num >>= 1;
  }
  return sum; 
}

// fills the char string with a binary representation of the number suitable for printing
void binary_string(unsigned int num, char str[BUFSZ]){
  str[0] = '0';
  str[1] = 'b';
  int i = 2; 
  long long int bits = 2147483648;
  while(bits > 0){
    if ((num & bits) == 0){
      str[i] = '0';
    } else {
      str[i] = '1';
    }
    i++;
    bits = bits >> 1;
  } 
  str[34] = '\0';
} 

// this function returns the modulo of the integer parameter and 32
int bitwise_mod32(int num){
  int mod32 = (num & 31);
  return mod32; 
}

// this function returns the absolute value of the integer parameter
int bitwise_abs(int num){
  int abs; 
  int m = num >> (sizeof(int) * 8 - 1);
  abs = ((num ^ m) - m);
  return abs; 
}

// this function extracts the specified bit from a given number
int bit_get(int num, int offset){
  return ((num >> offset) & 1); 
}

// this function returns a 0 or 1 determining if the integer parameter is even or odd, respectively
int odd_or_even(unsigned int num){
  return bit_get(num, 0);
}

// this function swaps the inputs without using a temporary variable
void swap_ints(int *a, int *b){
  *a = *a ^ *b;
  *b = *a ^ *b;
  *a = *a ^ *b;
}

