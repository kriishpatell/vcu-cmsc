#ifndef CMSC257_P1SUPPORT_INCLUDED
#define CMSC257_P1SUPPORT_INCLUDED

#define BUFSZ 35
////////////////////////////////////////////////////////////////////////////////
//
//  File          : p1-support.h
//  Description   : This is a set of functions we use
//                  for the 257 project #1.

// Functional Prototypes

// Function     : display_array
// Description  : This function prints out the array of integer values
// Inputs       : int an array of numbers to print 
// Output       : none
void display_array(unsigned int arr[], int);

// Function     : bitwise_add
// Description  : adds two integer parameters using only bitwise operations and loop and returns the result 
// Inputs       : two integers
// Output       : an integer
int bitwise_add(int, int);

// Function     : bitwise_shift_left
// Description  : shifts the first parameter to the left by the amount of second parameter. 
// Inputs       : two integers
// Output       : an integer
int bitwise_shift_left(int, int);

// Function     : count_set_bits
// Description  : returns number of 1s in bitwise representation of a number 
// Inputs       : an integer
// Output       : an integer
int count_set_bits(int);

// Function     : binary_string
// Description  : fills the char string with a binary representation of the number suitable for printing. 
// Inputs       : an unsigned integer and a mutable string
// Output       : void
void binary_string(unsigned int, char[BUFSZ]);

// Function     : bitwise_mod32
// Description  : return num%32 using bitwise ops
// Inputs       : an integer 
// Output       : an integer
int bitwise_mod32(int);

// Function     : bitwise_abs
// Description  : Returns absolute value of an integer
// Inputs       : an integer 
// Output       : an integer
int bitwise_abs(int);

// Function     : bit_get
// Description  : returns a specified bit from a given number
// Inputs       : First parameter is the integer, second parameter is position in integer 
// Output       : an integer
int bit_get(int,int);

// Function     : odd_or_even
// Description  : Returns 1 if input is odd, returns 0 else
// Inputs       : an unsigned integer 
// Output       : an integer
int odd_or_even (unsigned int);

// Function     : swap_ints
// Description  : swaps the value of two integers using only bitwise operators
// Inputs       : two integers
// Output       : void
void swap_ints(int*,int*);
     

#endif // CMSC257_A1SUPPORT_INCLUDED

