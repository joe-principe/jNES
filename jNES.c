#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <raylib.h>

#define ZERO_PAGE_START 0x0000
#define ZERO_PAGE_END 0x00FF
#define SECOND_PAGE_START 0x0100
#define SECOND_PAGE_END 0x01FF

enum ControlFlags
{
    CARRY_FLAG        = 1,
    ZERO_FLAG         = 2,
    INTERRUPT_DISABLE = 4,
    DECIMAL_MODE      = 8,
    BREAK_COMMAND     = 16,
    OVERFLOW_FLAG     = 64,
    NEGATIVE_FLAG     = 128
};

/* TODO: Check if the flags should be set to 0 if they aren't set to 1 */

/**
 * TODO: Am I supposed to increment the program counter by one for each
 * instruction?
 */

/* TODO: How do I draw anything? Also, audio and controllers */

int 
main(void)
{
    uint8_t ram[65536] = { 0 };
    uint16_t pc = 0x0000;

    uint8_t sp = 0xFF;
    uint8_t acc = 0x00;
    uint8_t indx = 0x00;
    uint8_t indy = 0x00;
    uint8_t status = 0x00;
    uint8_t opcode = 0x00;

    uint16_t temp = 0x0000;

    /* TODO: ROM loading */

    InitWindow(640, 480, "jNES");

    while (!WindowShouldClose()) {
        switch (opcode) {
            /* Load accumulator (LDA) */
            /* Immediate */
            case 0xA9:
                acc = ram[pc + 1];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Zero page */
            case 0xA5:
                acc = ram[ram[pc + 1]];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Zero page, X */
            case 0xB5:
                temp = (ram[pc + 1] + indx) & 0xFF;

                acc = ram[temp];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Absolute */
            case 0xAD:
                temp = (ram[pc + 1]) + (ram[pc + 2] << 8);

                acc = ram[temp];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* Absolute, X */
            case 0xBD:
                temp = (ram[pc + 1]) + (ram[pc + 2] << 8);

                acc = ram[temp + indx];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* Absolute, Y */
            case 0xB9:
                temp = (ram[pc + 1]) + (ram[pc + 2] << 8);

                acc = ram[temp + indy];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* (Indirect, X) */
            case 0xA1:
                temp = (ram[pc + 1] + indx) & 0xFF;

                acc = ram[ram[temp]];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* (Indirect), Y */
            case 0xB1:
                temp = ram[pc + 1];

                acc = ram[ram[temp] + indy];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Load X register (LDX) */
            /* Immediate */
            case 0xA2:
                indx = ram[pc + 1];

                if (indx == 0)
                    status |= ZERO_FLAG;
                else if ((indx & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Zero page */
            case 0xA6:
                indx = ram[ram[pc + 1]];

                if (indx == 0)
                    status |= ZERO_FLAG;
                else if ((indx & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Zero page, Y */
            case 0xB6:
                temp = (ram[pc + 1] + indy) & 0xFF;

                indx = ram[temp];

                if (indx == 0)
                    status |= ZERO_FLAG;
                else if ((indx & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Absolute */
            case 0xAE:
                temp = (ram[pc + 1]) + (ram[pc + 2] << 8);

                indx = ram[temp];

                if (indx == 0)
                    status |= ZERO_FLAG;
                else if ((indx & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* Absolute, Y */
            case 0xBE:
                temp = (ram[pc + 1]) + (ram[pc + 2] << 8);

                indx = ram[temp + indy];

                if (indx == 0)
                    status |= ZERO_FLAG;
                else if ((indx & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* Load Y register (LDY) */
            /* Immediate */
            case 0xA0:
                indy = ram[pc + 1];

                if (indy == 0)
                    status |= ZERO_FLAG;
                else if ((indy & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Zero page */
            case 0xA4:
                indy = ram[ram[pc + 1]];

                if (indy == 0)
                    status |= ZERO_FLAG;
                else if ((indy & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Zero page, X */
            case 0xB4:
                temp = (ram[pc + 1] + indx) & 0xFF;

                indy = ram[temp];

                if (indy == 0)
                    status |= ZERO_FLAG;
                else if ((indy & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Absolute */
            case 0xAC:
                temp = (ram[pc + 1]) + (ram[pc + 2] << 8);

                indy = ram[temp];

                if (indy == 0)
                    status |= ZERO_FLAG;
                else if ((indy & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* Absolute, X */
            case 0xBC:
                temp = (ram[pc + 1]) + (ram[pc + 2] << 8);

                indy = ram[temp + indx];

                if (indy == 0)
                    status |= ZERO_FLAG;
                else if ((indy & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* Store accumulator (STA) */
            /* Zero page */
            case 0x85:
                ram[ram[pc + 1]] = acc;
                pc += 2;
                break;

            /* Zero page, X */
            case 0x95:
                temp = (ram[pc + 1] + indx) & 0xFF;
                ram[temp] = acc;
                pc += 2;
                break;

            /* Absolute */
            case 0x8D:
                temp = (ram[pc + 1]) + (ram[pc + 2] << 8);
                ram[temp] = acc;
                pc += 3;
                break;

            /* Absolute, X */
            case 0x9D:
                temp = (ram[pc + 1]) + (ram[pc + 2] << 8);
                ram[temp + indx] = acc;
                pc += 3;
                break;

            /* Absolute, Y */
            case 0x99:
                temp = (ram[pc + 1]) + (ram[pc + 2] << 8);
                ram[temp + indy] = acc;
                pc += 3;
                break;

            /* (Indirect, X) */
            case 0x81:
                temp = (ram[pc + 1] + indx) & 0xFF;
                ram[temp] = acc;
                pc += 2;
                break;

            /* (Indirect), Y */
            case 0x91:
                temp = ram[pc + 1];
                ram[ram[temp] + indy] = acc;
                pc += 2;
                break;

            /* Store X register (STX) */
            /* Zero page */
            case 0x86:
                ram[ram[pc + 1]] = indx;
                pc += 2;
                break;

            /* Zero page, Y */
            case 0x96:
                temp = (ram[pc + 1] + indy) & 0xFF;
                ram[temp] = indx;
                pc += 2;
                break;

            /* Absolute */
            case 0x8E:
                temp = (ram[pc + 1]) + (ram[pc + 2] << 8);
                ram[temp] = indx;
                pc += 3;
                break;

            /* Store Y register (STY) */
            /* Zero page */
            case 0x84:
                ram[ram[pc + 1]] = indy;
                pc += 2;
                break;

            /* Zero page, X */
            case 0x94:
                temp = (ram[pc + 1] + indx) & 0xFF;
                ram[temp] = indy;
                pc += 2;
                break;

            /* Absolute */
            case 0x8C:
                temp = (ram[pc + 1]) + (ram[pc + 2] << 8);
                ram[temp] = indy;
                pc += 3;
                break;

            /* Transfer Accumulator to X (TAX) */
            case 0xAA:
                indx = acc;

                if (indx == 0)
                    status |= ZERO_FLAG;
                else if ((indx & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc++;
                break;

            /* Transfer Accumulator to Y (TAY) */
            case 0xA8:
                indy = acc;

                if (indy == 0)
                    status |= ZERO_FLAG;
                else if ((indy & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc++;
                break;

            /* Transfer X to Accumulator (TXA) */
            case 0x8A:
                acc = indx;

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc++;
                break;

            /* Transfer Y to Accumulator (TYA) */
            case 0x98:
                acc = indy;

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc++;
                break;

            /* Transfer Stack Pointer to X (TSX) */
            case 0xBA:
                indx = sp;

                if (indx == 0)
                    status |= ZERO_FLAG;
                else if ((indx & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc++;
                break;

            /* Transfer X to Stack Pointer (TXS) */
            case 0x9A:
                sp = indx;

                if (sp == 0)
                    status |= ZERO_FLAG;
                else if ((sp & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc++;
                break;

            /* Push Accumulator (PHA) */
            /* TODO: Give a CLI warning if there's a stack overflow */
            case 0x48:
                ram[sp + 0x0100] = acc;
                sp--;
                pc++;
                break;

            /* Push Processor Status (PHP) */
            case 0x08:
                ram[sp + 0x0100] = status;
                sp--;
                pc++;
                break;

            /* Pull Accumulator (PLA) */
            case 0x68:
                acc = ram[sp + 0x0100];
                sp++;

                if (acc == 0)
                    status |= CARRY_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc++;
                break;

            /* Pull Processor Status (PLP) */
            case 0x28:
                status = ram[sp + 0x0100];
                sp++;
                pc++;
                break;

            /* Logical AND (AND) */
            /* Immediate */
            case 0x29:
                /* The immediate value 'M' is the next byte */
                acc &= ram[pc + 1];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Zero Page */
            case 0x25:
                /* The value 'M' is a location in the zero page */
                acc &= ram[ram[pc + 1]];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Zero Page, X */
            case 0x35:
                /**
                 * The value 'M' is a location in the zero page plus the value
                 * in index X.
                 * 
                 * ANDing with 0xFF is to ensure it can "overflow" like the
                 * hardware does
                 */
                temp = (ram[pc + 1] + indx) & 0xFF;

                acc &= ram[temp];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Absolute */
            case 0x2D:
                /* TODO: Check if this has the proper endianness */
                temp = (ram[pc + 1]) + (ram[pc + 2] << 8);

                acc &= ram[temp];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* Absolute, X */
            case 0x3D:
                temp = (ram[pc + 1]) + (ram[pc + 2] << 8);

                acc &= ram[temp + indx];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* Absolute, Y */
            case 0x39:
                temp = (ram[pc + 1]) + (ram[pc + 2] << 8);

                acc &= ram[temp + indy];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* (Indirect, X) */
            case 0x21:
                temp = (ram[pc + 1] + indx) & 0xFF;

                acc &= ram[ram[temp]];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* (Indirect), Y */
            case 0x31:
                temp = ram[pc + 1];

                acc &= ram[ram[temp] + indy];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Exclusive OR (EOR) */
            /* Immediate */
            case 0x49:
                acc ^= ram[pc + 1];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Zero page */
            case 0x45:
                acc ^= ram[ram[pc + 1]];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Zero page, X */
            case 0x55:
                temp = (ram[pc + 1] + indx) & 0xFF;

                acc ^= ram[temp];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Absolute */
            case 0x4D:
                temp = (ram[pc + 1]) + (ram[pc + 2] << 8);

                acc ^= ram[temp];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Absolute, X */
            case 0x5D:
                temp = (ram[pc + 1]) + (ram[pc + 2] << 8);

                acc ^= ram[temp + indx];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Absolute, Y */
            case 0x59:
                temp = (ram[pc + 1]) + (ram[pc + 2] << 8);

                acc ^= ram[temp + indy];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* (Indirect, X) */
            case 0x41:
                temp = (ram[pc + 1] + indx) & 0xFF;

                acc ^= ram[ram[temp]];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* (Indirect), Y */
            case 0x51:
                temp = ram[pc + 1];

                acc ^= ram[ram[temp] + indy];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Logical Inclusive OR (ORA) */
            /* Immediate */
            case 0x09:
                acc |= ram[pc + 1];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Zero page */
            case 0x05:
                acc |= ram[ram[pc + 1]];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Zero page, X */
            case 0x15:
                temp = (ram[pc + 1] + indx) & 0xFF;

                acc |= ram[temp];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Absolute */
            case 0x0D:
                temp = (ram[pc + 1]) + (ram[pc + 2] << 8);

                acc |= ram[temp];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Absolute, X */
            case 0x1D:
                temp = (ram[pc + 1]) + (ram[pc + 2] << 8);

                acc |= ram[temp + indx];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Absolute, Y */
            case 0x19:
                temp = (ram[pc + 1]) + (ram[pc + 2] << 8);

                acc |= ram[temp + indy];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* (Indirect, X) */
            case 0x01:
                temp = (ram[pc + 1] + indx) & 0xFF;

                acc |= ram[ram[temp]];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* (Indirect), Y */
            case 0x11:
                temp = ram[pc + 1];

                acc |= ram[ram[temp] + indy];

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Bit test (BIT) */
            /* Zero page */
            case 0x24:
                temp = ram[ram[pc + 1]];

                if ((acc & temp) == 0)
                    status |= ZERO_FLAG;
                else
                    status &= ~ZERO_FLAG;

                /* TODO: Is this even correct? */
                status |= (temp & 0x40) << 1;
                status |= (temp & NEGATIVE_FLAG) << 1;

                pc += 2;
                break;

            /* Absolute */
            case 0x2C:
                temp = (ram[pc + 1]) + (ram[pc + 2] << 8);

                if ((acc & temp) == 0)
                    status |= ZERO_FLAG;
                else
                    status &= ~ZERO_FLAG;

                /* TODO: Is this even correct? */
                status |= (temp & 0x40) << 1;
                status |= (temp & NEGATIVE_FLAG) << 1;

                pc += 3;
                break;

            /* TODO: Overflow flag */
            /* Add with carry (ADC) */
            /* Immediate mode */
            case 0x69:
                temp = acc + ram[pc + 1] + (status & CARRY_FLAG);

                if (temp > 0xFF)
                    status |= CARRY_FLAG;

                acc = temp;

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Zero Page */
            case 0x65:
                temp = acc + ram[ram[pc + 1]] + (status & CARRY_FLAG);

                if (temp > 0xFF)
                    status |= CARRY_FLAG;

                acc = temp;

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Zero Page, X */
            case 0x75:
                temp = acc + (ram[ram[pc + 1] + indx] & 0xFF)
                       + (status & CARRY_FLAG);

                if (temp > 0xFF)
                    status |= CARRY_FLAG;

                acc = temp;

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Absolute */
            case 0x6D:
                temp = acc + (ram[pc + 1] + (ram[pc + 2] << 8))
                       + (status & CARRY_FLAG);

                if (temp > 0xFF)
                    status |= CARRY_FLAG;

                acc = temp;

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* Absolute, X */
            case 0x7D:
                temp = acc + (ram[pc + 1] + (ram[pc + 2] << 8) + indx)
                       + (status & CARRY_FLAG);

                if (temp > 0xFF)
                    status |= CARRY_FLAG;

                acc = temp;

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* Absolute, Y */
            case 0x79:
                temp = acc + (ram[pc + 1] + (ram[pc + 2] << 8) + indy)
                       + (status & CARRY_FLAG);

                if (temp > 0xFF)
                    status |= CARRY_FLAG;

                acc = temp;

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* (Indirect, X) */
            case 0x61:
                temp = acc + (ram[ram[(ram[pc + 1] + indx) & 0xFF]])
                       + (status & CARRY_FLAG);

                if (temp > 0xFF)
                    status |= CARRY_FLAG;

                acc = temp;

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* (Indirect), Y */
            case 0x71:
                temp = acc + (ram[ram[ram[pc + 1]] + indy])
                       + (status & CARRY_FLAG);

                if (temp > 0xFF)
                    status |= CARRY_FLAG;

                acc = temp;

                if (acc == 0)
                    status |= ZERO_FLAG;
                else if ((acc & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Subtract with Carry (SBC) */
            /* Immediate */
            case 0xE9:
                break;

            /* Zero page */
            case 0xE5:
                break;

            /* Zero page, X */
            case 0xF5:
                break;

            /* Absolute */
            case 0xED:
                break;

            /* Absolute, X */
            case 0xFD:
                break;

            /* Absolute, Y */
            case 0xF9:
                break;

            /* (Indirect, X) */
            case 0xE1:
                break;

            /* (Indirect), Y */
            case 0xF1:
                break;

            /* Compare (CMP) */
            /* Immediate */
            case 0xC9:
                temp = ram[pc + 1];

                if (acc >= temp)
                    status |= CARRY_FLAG;
                else if (acc == temp)
                    status |= ZERO_FLAG;

                if ((temp & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Zero page */
            case 0xC5:
                temp = ram[ram[pc + 1]];

                if (acc >= temp)
                    status |= CARRY_FLAG;
                else if (acc == temp)
                    status |= ZERO_FLAG;

                if ((temp & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Zero page, X */
            case 0xD5:
                temp = ram[(ram[pc + 1] + indx) & 0xFF];

                if (acc >= temp)
                    status |= CARRY_FLAG;
                else if (acc == temp)
                    status |= ZERO_FLAG;

                if ((temp & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Absolute */
            case 0xCD:
                temp = ram[pc + 1] + (ram[pc + 2] << 8);

                if (acc >= temp)
                    status |= CARRY_FLAG;
                else if (acc == temp)
                    status |= ZERO_FLAG;

                if ((temp & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* Absolute, X */
            case 0xDD:
                temp = ram[pc + 1] + (ram[pc + 2] << 8) + indx;

                if (acc >= temp)
                    status |= CARRY_FLAG;
                else if (acc == temp)
                    status |= ZERO_FLAG;

                if ((temp & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* Absolute, Y */
            case 0xD9:
                temp = ram[pc + 1] + (ram[pc + 2] << 8) + indy;

                if (acc >= temp)
                    status |= CARRY_FLAG;
                else if (acc == temp)
                    status |= ZERO_FLAG;

                if ((temp & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* (Indirect, X) */
            case 0xC1:
                temp = ram[ram[(ram[pc + 1] + indx) & 0xFF]];

                if (acc >= temp)
                    status |= CARRY_FLAG;
                else if (acc == temp)
                    status |= ZERO_FLAG;

                if ((temp & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* (Indirect), Y */
            case 0xD1:
                temp = ram[ram[ram[pc + 1] + indy]];

                if (acc >= temp)
                    status |= CARRY_FLAG;
                else if (acc == temp)
                    status |= ZERO_FLAG;

                if ((temp & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Compare X Register (CPX) */
            /* Immediate */
            case 0xE0:
                temp = ram[pc + 1];

                if (indx >= temp)
                    status |= CARRY_FLAG;
                else if (indx == temp)
                    status |= ZERO_FLAG;

                if ((temp & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Zero page */
            case 0xE4:
                temp = ram[ram[pc + 1]];

                if (indx >= temp)
                    status |= CARRY_FLAG;
                else if (indx == temp)
                    status |= ZERO_FLAG;

                if ((temp & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;
            
            /* Absolute */
            case 0xEC:
                temp = ram[pc + 1] + (ram[pc + 2] << 8);

                if (indx >= temp)
                    status |= CARRY_FLAG;
                else if (indx == temp)
                    status |= ZERO_FLAG;

                if ((temp & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* Compare Y Register (CPY) */
            /* Immediate */
            case 0xC0:
                temp = ram[pc + 1];

                if (indy >= temp)
                    status |= CARRY_FLAG;
                else if (indy == temp)
                    status |= ZERO_FLAG;

                if ((temp & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Zero page */
            case 0xC4:
                temp = ram[ram[pc + 1]];

                if (indy >= temp)
                    status |= CARRY_FLAG;
                else if (indy == temp)
                    status |= ZERO_FLAG;

                if ((temp & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Absolute */
            case 0xCC:
                temp = ram[pc + 1] + (ram[pc + 2] << 8);

                if (indy >= temp)
                    status |= CARRY_FLAG;
                else if (indy == temp)
                    status |= ZERO_FLAG;

                if ((temp & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* Increment Memory (INC) */
            /* Zero page */
            case 0xE6:
                temp = ram[pc + 1];
                ram[temp]++;
                temp = ram[temp];

                if (temp == 0)
                    status |= ZERO_FLAG;
                else if ((temp & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Zero Page, X */
            case 0xF6:
                temp = (ram[pc + 1] + indx) & 0xFF;
                ram[temp]++;
                temp = ram[temp];

                if (temp == 0)
                    status |= ZERO_FLAG;
                else if ((temp & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;
            
            /* Absolute */
            case 0xEE:
                temp = ram[pc + 1] + (ram[pc + 2] << 8);
                ram[temp]++;
                temp = ram[temp];

                if (temp == 0)
                    status |= ZERO_FLAG;
                else if ((temp & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* Absolute, X */
            case 0xFE:
                temp = ram[pc + 1] + (ram[pc + 2] << 8) + indx;
                ram[temp]++;
                temp = ram[temp];

                if (temp == 0)
                    status |= ZERO_FLAG;
                else if ((temp & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* Increment X Register (INX) */
            case 0xE8:
                indx++;

                if (indx == 0)
                    status |= ZERO_FLAG;
                else if ((indx & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc++;
                break;

            /* Increment Y Register (INY) */
            case 0xC8:
                indy++;

                if (indy == 0)
                    status |= ZERO_FLAG;
                else if ((indy & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc++;
                break;

            /* Decrement Memory (DEC) */
            /* Zero page */
            case 0xC6:
                temp = ram[pc + 1];
                ram[temp]--;
                temp = ram[temp];

                if (temp == 0)
                    status |= ZERO_FLAG;
                else if ((temp & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Zero page, X */
            case 0xD6:
                temp = (ram[pc + 1] + indx) & 0xFF;
                ram[temp]--;
                temp = ram[temp];

                if (temp == 0)
                    status |= ZERO_FLAG;
                else if ((temp & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Absolute */
            case 0xCE:
                temp = ram[pc + 1] + (ram[pc + 2] << 8);
                ram[temp]--;
                temp = ram[temp];

                if (temp == 0)
                    status |= ZERO_FLAG;
                else if ((temp & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* Absolute, X */
            case 0xDE:
                temp = ram[pc + 1] + (ram[pc + 2] << 8) + indx;
                ram[temp]--;
                temp = ram[temp];

                if (temp == 0)
                    status |= ZERO_FLAG;
                else if ((temp & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* Decrement X Register (DEX) */
            case 0xCA:
                indx--;

                if (indx == 0)
                    status |= ZERO_FLAG;
                else if ((indx & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc++;
                break;

            /* Decrement Y Register (DEY) */
            case 0x88:
                indy--;

                if (indy == 0)
                    status |= ZERO_FLAG;
                else if ((indy & NEGATIVE_FLAG) != 0)
                    status |= NEGATIVE_FLAG;

                pc++;
                break;

            /* Arithmetic Shift Left (ASL) */
            /* Accumulator */
            case 0x0A:

                break;

            /* Zero page */
            case 0x06:
                break;

            /* Zero page, X */
            case 0x16:
                break;

            /* Absolute */
            case 0x0E:
                break;

            /* Absolute, X */
            case 0x1E:
                break;

            /* Logical Shift Right (LSR) */
            /* Accumulator */
            case 0x4A:
                break;

            /* Zero page */
            case 0x46:
                break;

            /* Zero page, X */
            case 0x56:
                break;

            /* Absolute */
            case 0x4E:
                break;

            /* Absolute, X */
            case 0x5E:
                break;

            /* Rotate Left (ROL) */
            /* Accumulator */
            case 0x2A:
                break;

            /* Zero page */
            case 0x26:
                break;

            /* Zero page, X */
            case 0x36:
                break;

            /* Absolute */
            case 0x2E:
                break;

            /* Absolute, X */
            case 0x3E:
                break;

            /* Rotate Right (ROR) */
            /* Accumulator */
            case 0x6A:
                break;

            /* Zero page */
            case 0x66:
                break;

            /* Zero page, X */
            case 0x76:
                break;

            /* Absolute */
            case 0x6E:
                break;

            /* Absolute, X */
            case 0x7E:
                break;

            /* Jump (JMP) */
            /* Absolute */
            case 0x4C:
                pc = ram[pc + 1] + (ram[pc + 2] << 8);
                break;

            /* Indirect */
            case 0x6C:
                pc = ram[ram[pc + 1]] + (ram[ram[pc + 1] + 1] << 8);
                break;

            /* Jump to Subroutine (JSR) */
            case 0x20:
                ram[sp] = pc;
                sp--;
                pc = ram[pc + 1] + (ram[pc + 2] << 8);
                break;

            /* Return from Subroutine (RTS) */
            case 0x60:
                pc = ram[sp] - 1;
                sp++;
                break;

            /* Branch if Carry Clear (BCC) */
            case 0x90:
                if ((status & CARRY_FLAG) == 0)
                    pc += (int8_t)ram[pc + 1];

                pc += 2;
                break;

            /* Branch if Carry Set (BCS) */
            case 0xB0:
                if ((status & CARRY_FLAG) != 0)
                    pc += (int8_t)ram[pc + 1];

                pc += 2;
                break;

            /* Branch if Equal (BEQ) */
            case 0xF0:
                if ((status & ZERO_FLAG) != 0)
                    pc += (int8_t)ram[pc + 1];

                pc += 2;
                break;

            /* Branch if Minus (BMI) */
            case 0x30:
                if ((status & NEGATIVE_FLAG) != 0)
                    pc += (int8_t)ram[pc + 1];

                pc += 2;
                break;

            /* Branch if Not Equal (BNE) */
            case 0xD0:
                if ((status & ZERO_FLAG) == 0)
                    pc += (int8_t)ram[pc + 1];

                pc += 2;
                break;

            /* Branch if Positive (BPL) */
            case 0x10:
                if ((status & NEGATIVE_FLAG) == 0)
                    pc += (int8_t)ram[pc + 1];

                pc += 2;
                break;

            /* Branch if Overflow Clear (BVC) */
            case 0x50:
                if ((status & OVERFLOW_FLAG) == 0)
                    pc += (int8_t)ram[pc + 1];

                pc += 2;
                break;

            /* Branch if Overflow Set (BVS) */
            case 0x70:
                if ((status & OVERFLOW_FLAG) != 0)
                    pc += (int8_t)ram[pc + 1];

                pc += 2;
                break;

            /* Clear Carry Flag (CLC) */
            case 0x18:
                status &= ~CARRY_FLAG;
                pc++;
                break;

            /* Clear Decimal Flag (CLD) */
            case 0xD8:
                status &= ~DECIMAL_MODE;
                pc++;
                break;

            /* Clear Interrupt Disable (CLI) */
            case 0x58:
                status &= ~INTERRUPT_DISABLE;
                pc++;
                break;

            /* Clear Overflow Flag (CLV) */
            case 0xB8:
                status &= ~OVERFLOW_FLAG;
                pc++;
                break;

            /* Set Carry Flag (SEC) */
            case 0x38:
                status |= CARRY_FLAG;
                pc++;
                break;

            /* Set Decimal Flag (SED) */
            case 0xF8:
                status |= DECIMAL_MODE;
                pc++;
                break;

            /* Set Interrupt Disable (SEI) */
            case 0x78:
                status |= INTERRUPT_DISABLE;
                pc++;
                break;

            /* Force interrupt (BRK) */
            case 0x00:
                /* TODO: wtf am I supposed to do with this for an emulator? */
                status |= BREAK_COMMAND;
                ram[sp + 0x0100] = pc;
                sp--;

                ram[sp + 0x0100] = status;
                sp--;

                pc = 0xFFFE;
                break;

            /* No Operation (NOP) */
            case 0xEA:
                pc++;
                break;

            /* Return from Interrupt (RTI) */
            case 0x40:
                status = ram[sp + 0x0100];
                sp++;

                pc = ram[sp + 0x0100];
                sp++;
                break;

            /* TODO: Add the non-standard opcodes here */
            default:
                fprintf(stderr, "Error: Unrecognized opcode %04x at 0x%04x\n",
                        opcode, pc);
                pc++;
                break;
        }

        BeginDrawing();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
/* EOF */
