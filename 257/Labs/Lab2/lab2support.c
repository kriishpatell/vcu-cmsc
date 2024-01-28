// Include Files
#include <stdio.h>
// Project Includes
#include "lab2header.h"
// Function Implementations

int reverse_number(int num)
{
	int reversed = 0;
	while(num > 0)
	{
		reversed = reversed * 10 + num % 10;
		num = num / 10;
	}
	return reversed;
}

int even_odd(int num)
{
	if(num % 2 == 0){
		return 1;
	} else {
		return 0;
	}
}

int is_prime(int num)
{
	int flag, i = 0;
	if(num == 0 || num == 1){
		flag = 1;
	}
	for(i = 2; i <= num / 2; ++i){
		if(num % i == 0){
			flag = 1;
		} else {
			flag = 0;
		}
	}
	return flag;
}

