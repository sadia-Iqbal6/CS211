#! /bin/bash
# Scores for different sections of the homework
compile=10
addition=25
subtraction=25
multiplication=25
no_sub=5
no_add=5
no_mult=5

rm hw5
make hw5
if [ ! -e "hw5" ]; then
    echo "Failed to compile."
    compile=0
fi


grep -P "[^-]\-[^->]" rcadder.c
if [[ $? -ne 1 ]]; then
    echo "Subtraction operator used."
    no_sub=0
fi

grep -P "[^+]\+[^+]" rcadder.c
if [[ $? -ne 1 ]]; then
    echo "Addition operator used."
    no_add=0
fi

sed "s/BitResult\*//g" rcadder.c |grep "\*"
if [[ $? -ne 1 ]]; then
    echo "Multiplication operator used."
    no_mult=0
fi

for test in `seq 1 7`; do
    test_args=$(grep hw5_test_$test hw5_test_results.txt | cut -d " " -f 2,3,4)
    echo "Testing with arg $test_args"
    add_result=$(grep -A 1 hw5_test_$test hw5_test_results.txt | tail -n 1)
    sub_result=$(grep -A 2 hw5_test_$test hw5_test_results.txt | tail -n 1)
    mul_result=$(grep -A 3 hw5_test_$test hw5_test_results.txt | tail -n 1)
    actual_add=$(./hw5 $test_args | head -n 1 | tail -n 1)
    actual_sub=$(./hw5 $test_args | head -n 2 | tail -n 1)
    actual_mul=$(./hw5 $test_args | tail -n 1)
    if [[ "$add_result" != "$actual_add" ]]; then
        echo "Failed addition test."
        echo "Expected $add_result, but got $actual_add"
        addition=0
    fi
    if [[ "$sub_result" != "$actual_sub" ]]; then
        echo "Failed subtraction test."
        echo "Expected $sub_result, but got $actual_sub"
        subtraction=0
    fi
    if [[ "$mul_result" != "$actual_mul" ]]; then
        echo "Failed multiplication test."
        echo "Expected $mul_result, but got $actual_mul"
        multiplication=0
    fi
done

echo "Score is $(( compile + addition + subtraction + multiplication + no_sub + no_add + no_mult))"
