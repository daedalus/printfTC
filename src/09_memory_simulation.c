/*
 * Example 9: Memory Simulation with printf
 *
 * Simulates a basic computer architecture using printf:
 * - Registers (local variables)
 * - RAM (array)
 * - Program counter (loop index)
 * - Instruction decode (if/else)
 */
#include <stdio.h>
#include <string.h>

/* Simulated registers */
int R[8] = {0};

/* Simulated RAM */
int RAM[256] = {0};

/* Instruction opcodes */
#define OP_LOAD  1
#define OP_STORE 2
#define OP_ADD   3
#define OP_SUB   4
#define OP_MUL   5
#define OP_PRINT 6
#define OP_HALT  0

int main() {
    printf("=== printf as a CPU Simulator ===\n\n");

    /* Simple program in machine code:
     * LOAD R1, 10      ; R1 = 10
     * LOAD R2, 20      ; R2 = 20
     * ADD R3, R1, R2   ; R3 = R1 + R2
     * STORE R3, 0      ; RAM[0] = R3
     * PRINT R3         ; Output R3
     * HALT
     */

    /* Program as data */
    int program[][4] = {
        {OP_LOAD,  1, 10, 0},   /* R1 = 10 */
        {OP_LOAD,  2, 20, 0},   /* R2 = 20 */
        {OP_ADD,   3, 1, 2},    /* R3 = R1 + R2 */
        {OP_STORE, 3, 0, 0},    /* RAM[0] = R3 */
        {OP_PRINT, 3, 0, 0},    /* Print R3 */
        {OP_HALT,  0, 0, 0}     /* Stop */
    };

    int pc = 0;  /* Program counter */
    int running = 1;

    printf("Executing program...\n\n");

    while (running && pc < 6) {
        int opcode = program[pc][0];

        switch (opcode) {
            case OP_LOAD: {
                int reg = program[pc][1];
                int val = program[pc][2];
                /* LOAD: set register to value via printf */
                R[reg] = 0;
                printf("%*d%n", val, 0, &R[reg]);
                printf("  PC=%d: LOAD R%d, %d => R%d=%d\n", pc, reg, val, reg, R[reg]);
                break;
            }
            case OP_ADD: {
                int dest = program[pc][1];
                int src1 = program[pc][2];
                int src2 = program[pc][3];
                /* ADD: dest = src1 + src2 */
                R[dest] = 0;
                printf("%*d%*d%n", R[src1], 0, R[src2], 0, &R[dest]);
                printf("  PC=%d: ADD R%d, R%d, R%d => R%d=%d+%d=%d\n",
                       pc, dest, src1, src2, dest, R[src1], R[src2], R[dest]);
                break;
            }
            case OP_STORE: {
                int reg = program[pc][1];
                int addr = program[pc][2];
                /* STORE: RAM[addr] = R[reg] */
                RAM[addr] = 0;
                printf("%*d%n", R[reg], 0, &RAM[addr]);
                printf("  PC=%d: STORE R%d => RAM[%d]=%d\n", pc, reg, addr, RAM[addr]);
                break;
            }
            case OP_PRINT: {
                int reg = program[pc][1];
                printf("  PC=%d: PRINT R%d => %d\n", pc, reg, R[reg]);
                break;
            }
            case OP_HALT:
                printf("  PC=%d: HALT\n", pc);
                running = 0;
                break;
        }
        pc++;
    }

    printf("\nFinal state:\n");
    for (int i = 0; i < 8; i++) {
        if (R[i] != 0) printf("  R[%d] = %d\n", i, R[i]);
    }
    if (RAM[0] != 0) printf("  RAM[0] = %d\n", RAM[0]);

    printf("\n=== printf simulates a complete CPU ===\n");
    printf("  Registers: local variables modified by %%n\n");
    printf("  RAM: array elements modified by %%n\n");
    printf("  ALU: width specifiers perform arithmetic\n");
    printf("  Control flow: C's if/switch/while (can be simulated)\n");

    return 0;
}
