/*
 * File: main.c
  * Author: Julia Arrington
   */

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

   /*
	 *Program to detect and correct bit stream using Hamming Error Code
	 *Input should have 64 bits max
	   */
int main(int argc, char** argv)
{
	//the part about reading is from https://www.geeksforgeeks.org/input-an-integer-array-without-spaces-in-c/
	int bitStream[64];
	int finalStream[71]; //64 bits only need 7 parity bits thus 71
	int i, p, length = 0, j = 0, k = 0, bit = 2, position = 0;
	//initializing the final stream with non-binary numbers (3)
	for (i = 0; i < 71; i++) {
		finalStream[i] = 3;
	}
	printf("How many bits are in your stream? ");
	scanf_s("%d", &length);
	while (length > 64) {
		printf("That is too long! Try again");
		scanf_s("%d", &length);
	}
	printf("Type your bit stream: ");
	int test = 0;
	for (i = 0; i < length; i++) {
		scanf_s("%1d", &bitStream[i]);
		test = test ^ bitStream[i];
	}
	//making sure input is binary
	while (test != (0 || 1)) {
		printf("Error! That is not binary! Try again!");
		test = 0;
		for (i = 0; i < length; i++) {
			scanf_s("%1d", &bitStream[i]);
			test = test ^ bitStream[i];
		}
	}
	
	//testing how many parity bits are needed (p)
	p = 0;
	while (length >= pow(2, p)) {
		length++;
		p++;
	}
	// p is used later for calculations so I made add keep track of the bits added
	p = -1;
	int add = p;
	//prepping result stream; all spaces that are not parity bits have the values from the input stream
	for (i = 0; i < length; i++) {
		if (i + 1 != pow(2, j)) {
			finalStream[i] = bitStream[k];
			k++;
			continue;
		}
		else {
			j++;
		}
	}

	//calculating parity bits
	//check keeps track of how many bits in a row should be XORed
	int check;
	int count = 0;
	for (i = 0; i < length; i++) {
		if (finalStream[i] == 3) {
			position = i + 1;
			p++;
			//first bit is a special case
			if (position == 1) {
				bit = finalStream[2];
				for (j = 5; j <= length; j += 2) {
					if (finalStream[j - 1] == 1) {
						count++;
					}
				}
				if ((count % 2) == 0) {
					bit = 0;
				}
				else {
					bit = 1;
				}
				finalStream[0] = bit;
			}
			//I think 2 should also be a special case
			else if (position == 2 && length > 1) {
				bit = finalStream[2];
				for (j = 6; j < length; j += 4) {
					if (finalStream[j - 1] == 1) {
						count++;
					}
				}
				if ((count % 2) == 0) {
					bit = 0;
				}
				else {
					bit = 1;
				}
				finalStream[1] = bit;
							}
			//other bits
			else if (length > 2) {
				bit = finalStream[position];
				check = p + 1;
				//I don't even know what j is
				j = position;
				//first make sure its not the end of the stream
				while (j <= (length +add)) {
					//then make sure its not the end of the stream and that there are still bits to check
					while (check > 0 && j <= (length+add)) {
						if (finalStream[j - 1] == 1) {
							count++;
						}
						j++;
					}
					if ((count % 2) == 0 && (count != 0)) {
						bit = 0;
					}
					else {
						bit = 1;
					}
					finalStream[position - 1] = bit;
				}
			}
		}
	}
	//print final array
	printf("Final frame is: ");
	for (i = 0; i < length; i++) {
		printf("%d", finalStream[i]);
	}
	return (EXIT_SUCCESS);
}