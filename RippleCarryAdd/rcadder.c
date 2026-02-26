#include <stdio.h>
#include <stdlib.h>
#include "rcadder.h"

//will use this function for the Carry Add one
void bitAdd(BitResult* result, unsigned int bit_a, unsigned int bit_b, unsigned int carry_in){
    //compute sum and carry out using formulas using the bitwise operators
    unsigned int bit_sum = bit_a ^ bit_b ^ carry_in;
    unsigned int carry_out = (bit_a & bit_b) | (carry_in & (bit_a ^ bit_b));

    //now assign the sum and carry out to the pointer struct
    result->sum = bit_sum;
    result->carry = carry_out;
}
//will use this function for the Carry Subtract one
void bitSub(BitResult* result, unsigned int bit_a, unsigned int bit_b, unsigned int borrow){
    //compute diff and borrow out using formulas using the bitwise operators
    unsigned int bit_diff = bit_a ^ bit_b ^ borrow;
    unsigned int borrow_out = (~bit_a & bit_b) | (borrow & (~bit_a | bit_b));

    //now assign the diff and borrow out to the pointer struct
    result->sum = bit_diff;
    result->carry = borrow_out;
}

void rippleCarryAdd(BitResult* results, unsigned int width, unsigned int a, unsigned int b){
    unsigned int carry = 0; //initial carry is always 0
    unsigned int index = width;
    //loop through the bits
    for (unsigned int i = 0; i < width; i++){
        unsigned int bit_a = (a >> i) & 1; //get the first bit of a by getting the right most bit using shifting and masking
        unsigned int bit_b = (b >> i) & 1; //repeat for b 
        //We need to store the bits in reverse order printing MSB first
        index--;
        //using the bitAdd function compute the sum and carryout
        bitAdd(&results[index], bit_a, bit_b, carry);
        //now we update the carry in for the next bits
        carry = results[index].carry;
    }
}

void rippleCarrySubtract(BitResult* results, unsigned int width, unsigned int a, unsigned int b){
    //same way previous function was implemented
    unsigned int borrow = 0; //initial borrow is always 0
    unsigned int index = width;
    //loop through the bits
    for (unsigned int i = 0; i < width; i++){
        unsigned int bit_a = (a >> i) & 1; //get the first bit of a by getting the right most bit using shifting and masking
        unsigned int bit_b = (b >> i) & 1; //repeat for b 
        //We need to store the bits in reverse order printing MSB first
        index--;
        //using the bitSub function compute the diff and borrowout
        bitSub(&results[index], bit_a, bit_b, borrow);
        //now we update the carry in for the next bits
        borrow = results[index].carry;
    }

}
void rippleMultiply(BitResult* results, unsigned int width, unsigned int a, unsigned int b){
    //Begin with the 0 valued array of bit results
    for (int i = 0; i < width; i++){
        results[i].sum = 0;
        results[i].carry = 0;
    }

    //we need a temporary array holding the results of each loops add
    //ex: if we do 2 times 4 = 2 plus 2 plus 2 plus 2, loop 0 should be 2 plus 0=2 loop 1 should be 2 plus 2=4, loop 2 should be 2 plus 4=6, and loop 3 should be 2 plus 6=8 
    BitResult temp[width];

    //add a into it b times (loop b times)
    for (unsigned int i = 0; i < b; i++){ 
        unsigned int index = width;
        //copy the current addition result into temp
        for (int i = 0; i < width; i++){
            temp[i] = results[i]; //since we zeroed the array it starts out with all 0s
        }
        //need to convert to int to use in CarryAdd function
        unsigned int current_result = 0;
        for (int i = 0; i < width; i++){
            index--;
            if (temp[i].sum == 1){
                current_result = (1 << (index)) | current_result;
                //ex: 8 0x1 0x2, loop 0: current result = 0, loop 1: current result = 1
                //so then the first time carryAdd is called its 0 plus 1 = 1 then the 2nd time its 1 plus 1 = 2 (00000010)

            }
        }
        rippleCarryAdd(results, width, current_result, a); //adds a to itself (b times) so the same thing as a times b
    }

}
