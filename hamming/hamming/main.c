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
	   */
int main(int argc, char** argv)
{
	//the part about reading is from https://www.geeksforgeeks.org/input-an-integer-array-without-spaces-in-c/
	int bitStream[64];
	int finalStream[71]; //64 bits only need 7 parity bits thus 71
	int i, p, length, j = 0, k = 0, bit = 2, position = 0;
	//initializing the final stream with non-binary numbers (3)
	for (i = 0; i < 71; i++) {
		finalStream[i] = 3;
	}
	printf("How many bits are in your stream? ");
	scanf_s("%d", &length);
	printf("Type your bit stream: ");

	for (i = 0; i < length; i++) {
		scanf_s("%1d", &bitStream[i]);
	}
	//testing how many parity bits are needed (p)
	p = 0;
	while (length > pow(2, p)) {
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
	for (i = 0; i < length; i++) {
		if (finalStream[i] == 3) {
			position = i + 1;
			p++;
			//first bit is a special case
			if (position == 1) {
				bit = finalStream[2];
				for (j = 5; j <= length; j += 2) {
					bit = bit ^ finalStream[j - 1];
				}
				finalStream[0] = bit;
			}
			//I think 2 should also be a special case
			else if (position == 2) {
				bit = finalStream[2];
				for (j = 6; j < length; j += 4) {
					bit = bit ^ finalStream[j - 1];
					bit = bit ^ finalStream[j];
				}
				finalStream[1] = bit;
			}
			//other bits
			else {
				bit = finalStream[position];
				check = p + 1;
				j = position;
				//first make sure its not the end of the stream
				while (j < (length + add)) {
					//then make sure its not the end of the stream and that there are still bits to check
					while (check > 0 && j < (length + add)) {
						bit = bit ^ finalStream[j];
						check--;
						j++;
					}
					check = p + 2;
					j = j + check;
				}
				finalStream[position - 1] = bit;
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