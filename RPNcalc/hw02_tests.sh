#! /bin/bash
# Scores for different proportions of the homework
compile=5
handle_no_file=5
handle_no_open=5
easy_op=20
multiple_op=15
ignore_text=20
handle_no_values=10
handle_no_ops=10
no_mem_leak=10

if [ ! -e "hw02" ]; then
    echo "Failed to compile."
    compile=0
fi

./hw02 rpn1.txt
if [[ $? -ne 3 ]]; then
    echo "Failed rpn1."
    easy_op=0
fi

./hw02 rpn2.txt
if [[ $? -ne 84 ]]; then
    echo "Failed rpn2."
    multiple_op=0
fi

./hw02 rpn3.txt
if [[ $? -ne 11 ]]; then
    echo "Failed rpn3."
    multiple_op=0
fi

./hw02 rpn4.txt
if [[ $? -ne 0 ]]; then
    echo "Failed rpn4."
    multiple_op=0
fi

./hw02 rpn5.txt
if [[ $? -ne 5 ]]; then
    echo "Failed rpn5."
    multiple_op=0
fi

./hw02 rpn6.txt
if [[ $? -ne 126 ]]; then
    echo "Failed rpn6."
    ignore_text=0
fi

./hw02 rpn7.txt
if [[ $? -ne 1 ]]; then
    echo "Failed rpn6."
    ignore_text=0
fi

./hw02
if [[ $? -ne 254 ]]; then
    echo "Failed no file argument."
    handle_no_file=0
fi

./hw02 rpn_no_exist.txt
if [[ $? -ne 253 ]]; then
    echo "Failed file open error."
    handle_no_open=0
fi

./hw02 rpn_empty.txt
if [[ $? -ne 252 ]]; then
    echo "Failed no values."
    handle_no_values=0
fi

./hw02 rpn_many_ops.txt
if [[ $? -ne 252 ]]; then
    echo "Failed not enough values for ops."
    handle_no_values=0
fi

./hw02 rpn_no_ops.txt
if [[ $? -ne 251 ]]; then
    echo "Failed no ops."
    handle_no_ops=0
fi

valgrind ./hw02 rpn7.txt 2>&1 | grep "no leaks are possible"
if [[ $? -ne 0 ]]; then
    echo "Failed valgrind."
    no_mem_leak=0
fi

final_score=$((compile + handle_no_file + handle_no_open + easy_op + multiple_op + ignore_text + handle_no_values + handle_no_ops + no_mem_leak))
echo "Final score is $final_score/100"
