#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

int main (int argc, char** argv){
    //Error 1) No input filename provided: return 254
    if (argc < 2) {
        printf("This Program Requires an Input File!\n");
        return 254;
    }
    //open input file to read
    FILE* inputFile = fopen(argv[1], "r");
    //Error 2) Provided filename fails to open: return 253
    if (inputFile == NULL){
        printf("This File Failed to Open!\n");
        return 253;
    }
    //create a stack 
    Stack s = newStack(10);

    //A buffer to store each token as we read them (a word or number surrounded by spaces) 
    //we use this instead of reading each char in the cases where we have multiple digit inputs (ex: 10 2 +)
    size_t buf_size = 1000;
    char* line_buffer = calloc(buf_size, sizeof(char));
    //read one token at a time from input file
    int line_length = getline(&line_buffer, &buf_size, inputFile);
    while (line_length > -1){
        // A buffer to store each token 
        char token[101];
        size_t line_offset = 0;
        int consumed = 0;

        //read tokens one by one 
        int success = sscanf(line_buffer+line_offset, "%100s%n", token, &consumed);
        while (success == 1 && line_offset < line_length) {
            line_offset += consumed;
            //If the input is a digit/number  
            if (token[0] >= '0' && token[0] <= '9'){
                //convert the token into a int (so we can do the operations)
                int number = atoi(token);
                //push it onto the stack
                push(&s, number);
            } else if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/' ){ //If the input is one of -, +, *, or /
                //Error 3) The stack runs out of values at any time: return 252
                //we check this to make sure we have at least 2 values in the stack to pop 
                if (len(s) < 2){
                    printf("The stack ran out of values!\n");
                    freeStack(s);
                    free(line_buffer);
                    return 252;
                }
                //pop the top two values, perform the operation, and then push the result back onto the stack
                int b = pop(&s);
                int a = pop(&s);
                int result;
                if (token[0] == '+'){
                    result = a + b; 
                } else if (token[0] == '-'){
                    result = a - b;
                } else if (token[0] == '*'){
                    result = a * b;
                } else {
                    result = a / b;
                }
                push(&s, result);
            }
            //If there are more tokens, continue parsing by reading the next token
            success = sscanf(line_buffer+line_offset, "%100s%n", token, &consumed);
        } 
        // Get the next line
        line_length = getline(&line_buffer, &buf_size, inputFile);   
    }

    // Finished with the file
    fclose(inputFile);
    free(line_buffer);

    //Error 4) The stack has excess values (more than 1) at the end: return 251
    if (len(s) > 1){ //this checks if the stack has more than one value
        printf("The Stack has excess values!!\n");
        freeStack(s);
        return 251;
    }
    //Error 3) recheck if the stack is empty before popping final result (this handles the cases where input file is empty)
    if (len(s) == 0){
        freeStack(s);
        return 252;
    }

    //pop the last value on the stack. It is the result
    int finalResult = pop(&s);
    //free the stack's memory
    freeStack(s);

    return finalResult;
}