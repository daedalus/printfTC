CC = gcc
CFLAGS = -Wall -Wextra -std=c11

EXAMPLES = 01_counter 02_two_counter 03_fibonacci 04_calculator 05_conditional \
           06_state_machine 07_pointer_arithmetic 08_self_modifying \
           09_memory_simulation 10_ackermann 11_turing_machine \
           12_lambda_calculus 13_formal_proof 14_universal_machine \
           15_complex_example

all: $(EXAMPLES)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXAMPLES)

.PHONY: all clean
