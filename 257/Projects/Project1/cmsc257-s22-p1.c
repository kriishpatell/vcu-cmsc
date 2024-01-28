////////////////////////////////////////////////////////////////////////
//
//  File           : cmsc257-s22-p1.c
//  Description    : This is the main source code for for the first 
//                   project of CMSC257.  
//                   See the related assignment page for details.
//
//  Author         : 
//  Last Modified  :
//

// System Includes
#include <stdio.h>
#include <stdlib.h>

// Project Includes
#include "p1-support.h"


// Functions
///////////////////////////////////////////////////////////////////////
//
// Function     : main
// Description  : The main function for the CMSC257 project #1
// 
// Inputs       : argc - the number of command line parameters
//                argv - the parameters
// Output       : 0 if successful test, -1 if failure

int main() {
  int i;
  int value; 
  
  // Testing bitwise_add function
  for(i = 0; i < 11; i++){
    int rand1 = rand() % 99;
    int rand2 = rand() % 99; 
    printf("%d\n", rand1);
    printf("%d\n", rand2);
    value = bitwise_add(rand1, rand2);
    printf("%d\n\n", value);
  } 
  

  // Testing bitwise_shift_left
	for(i = 0; i < 11; i++){
    int rand1 = rand() % 99;
    int rand2 = rand() % 99; 
    printf("%d\n", rand1);
    printf("%d\n", rand2);
    value = bitwise_shift_left(rand1, rand2);
    printf("%d\n\n", value);
  } 

  // Testing count_set_bits
  for(i = 0; i < 11; i++){
    int random = (rand() % 50); 
    printf("%d\n", random);
    printf("%d\n\n", count_set_bits(random));
  } 
    
  // Testing bitwise_mod32
  for(i = 0; i < 11; i++){
    int random = rand() % 500;
    printf("%d\n", random);
    printf("%d\n\n", bitwise_mod32(random));
  } 

  // Testing bitwise_abs
  printf("The absolute value of -2 is: %d\n", bitwise_abs(-2));
  printf("The absolute value of 2 is: %d\n", bitwise_abs(2));
  printf("The absolute value of -400 is: %d\n", bitwise_abs(-400));
  printf("The absolute value of 400 is: %d\n", bitwise_abs(400));
  printf("The absolute value of -283 is: %d\n", bitwise_abs(-283));
  printf("The absolute value of 283 is: %d\n", bitwise_abs(283));
  printf("The absolute value of -10 is: %d\n", bitwise_abs(-10));
  printf("The absolute value of -76 is: %d\n", bitwise_abs(-76));
  printf("The absolute value of 41 is: %d\n", bitwise_abs(41));
  printf("The absolute value of 0 is: %d\n", bitwise_abs(0));


  /*

  // Local variables
  int int_array1[10];
  unsigned int uint_array1[10], uint_array2[10];
  int i;
  int option = 0;
  int offset = 0;
  //Add more local variables here as needed
  int add = 0;

  if (argc < 11)
  {   
  //Exit if there are less than 10 inputs
    printf("Exiting the program, missing input");
    return 0;	
  }

  // Step a - Read in the integer numbers input at 
  // the time of execution and save them into int_array1
  for (i=1; i<11; i++) {
    int_array1[i-1] = atoi(argv[i]);//converting input to integer
  }
  //You don't need to modify the code above for testing
  //Modify/uncomment the code below for testing as needed
  display_array(int_array1, 10);//display the input array
  // Step b - Reverse the order of array elements in int_array1 
  //           using swap function. 
    
  add = bitwise_add(5, 10);
  printf("%d", add);

  for(i = 0;i<5;i++){
    swap_ints(int_array1+i, (int_array1 + 9 - i));
  } 
  
	
  //Add index values of each array element on the array elements
  //test entering different offsets, maybe get input using scanf
  
  for (i=0; i<10; i++){
    int_array1[i] = bitwise_add(int_array1[i], offset);
  }
  
	
  // Step c - Convert numbers in int into positive values by taking their 
  // absolute values and save them in uint_array1. 
  // Print all numbers in a single line using display_array function
  
  for(i=0;i<10;i++){
    uint_array1[i] = bitwise_abs(int_array1[i]);
  }
	
  display_array(uint_array1, 10);
  

  // Step d - Convert these positive integers to numbers 
  // in the range 0,…,32 by implementing the  mod operation
  // save them into uint_array2. 
  // Print all numbers in a single line using display_array function
  
  
  for(i=0;i<10;i++){
    uint_array2[i] = bitwise_mod32(uint_array1[i]);
  }
	
  display_array(uint_array2, 10); 
  
  */

  // Return successfully
  return(0);
}
