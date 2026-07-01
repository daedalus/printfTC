CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC = src

EXAMPLES = 01_counter 02_two_counter 03_fibonacci 04_calculator 05_conditional \
           06_state_machine 07_pointer_arithmetic 08_self_modifying \
           09_memory_simulation 10_ackermann 11_turing_machine \
           12_lambda_calculus 13_formal_proof 14_universal_machine \
           15_complex_example 16_self_interpreter

all: $(EXAMPLES)

# Standard examples
01_counter 02_two_counter 03_fibonacci 04_calculator 05_conditional \
06_state_machine 07_pointer_arithmetic 08_self_modifying \
09_memory_simulation 10_ackermann 11_turing_machine \
12_lambda_calculus 13_formal_proof 14_universal_machine \
15_complex_example: %: $(SRC)/%.c
	$(CC) $(CFLAGS) -o $@ $<

# Example 16: needs exec-stack and no stack protector for return-address hijack
16_self_interpreter: $(SRC)/16_self_interpreter.c
	$(CC) $(CFLAGS) -z execstack -fno-stack-protector -o $@ $<

clean:
	rm -f $(EXAMPLES)

.PHONY: all clean
