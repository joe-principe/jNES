#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>

#define ZERO_PAGE_START 0x0000
#define ZERO_PAGE_END 0x00FF
#define SECOND_PAGE_END 0x01FF

enum ControlFlags
{
    CARRY_FLAG = 1,
    ZERO_FLAG = 2,
    INTERRUPT_DISABLE = 4,
    DECIMAL_MODE = 8,
    BREAK_COMMAND = 16,
    OVERFLOW_FLAG = 32,
    NEGATIVE_FLAG = 64
};

int 
main(void)
{
    unsigned char ram[65536] = { 0 };
    unsigned short pc = 0x0000;

    unsigned char sp = 0x00;
    unsigned char acc = 0x00;
    unsigned char indx = 0x00;
    unsigned char indy = 0x00;
    unsigned char status = 0x00;
    unsigned char opcode = 0x00;

    unsigned short temp = 0x0000;

    InitWindow(640, 480, "jNES");

    while (!WindowShouldClose()) {
        switch (opcode) {
            /* Load accumulator (LDA) */
            /* Immediate */
            case 0xA9:
                break;

            /* Zero page */
            case 0xA5:
                break;

            /* Zero page, X */
            case 0xB5:
                break;

            /* Absolute */
            case 0xAD:
                break;

            /* Absolute, X */
            case 0xBD:
                break;

            /* (Indirect, X) */
            case 0xA1:
                break;

            /* (Indirect), Y */
            case 0xB1:
                break;

            /* Load X register (LDX) */
            /* Immediate */
            case 0xA2:
                break;

            /* Zero page */
            case 0xA6:
                break;

            /* Zero page, Y */
            case 0xB6:
                break;

            /* Absolute */
            case 0xAE:
                break;

            /* Absolute, Y */
            case 0xBE:
                break;

            /* Load Y register (LDY) */
            /* Immediate */
            case 0xA0:
                break;

            /* Zero page */
            case 0xA4:
                break;

            /* Zero page, X */
            case 0xB4:
                break;

            /* Absolute */
            case 0xAC:
                break;

            /* Absolute, X */
            case 0xBC:
                break;

            /* Store accumulator (STA) */
            /* Zero page */
            case 0x85:
                break;

            /* Zero page, X */
            case 0x95:
                break;

            /* Absolute */
            case 0x8D:
                break;

            /* Absolute, X */
            case 0x9D:
                break;

            /* Absolute, Y */
            case 0x99:
                break;

            /* (Indirect, X) */
            case 0x81:
                break;

            /* (Indirect), Y */
            case 0x91:
                break;

            /* Store X register (STX) */
            /* Zero page */
            case 0x86:
                break;

            /* Zero page, Y */
            case 0x96:
                break;

            /* Absolute */
            case 0x8E:
                break;

            /* Store Y register (STY) */
            /* Zero page */
            case 0x84:
                break;

            /* Zero page, X */
            case 0x94:
                break;

            /* Absolute */
            case 0x8C:
                break;

            /* Transfer Accumulator to X (TAX) */
            case 0xAA:
                break;

            /* Transfer Accumulator to Y (TAY) */
            case 0xA8:
                break;

            /* Transfer X to Accumulator (TXA) */
            case 0x8A:
                break;

            /* Transfer Y to Accumulator (TYA) */
            case 0x98:
                break;

            /* Transfer Stack Pointer to X (TSX) */
            case 0xBA:
                break;

            /* Transfer X to Stack Pointer (TXS) */
            case 0x9A:
                break;

            /* Push Accumulator (PHA) */
            case 0x48:
                break;

            /* Push Processor Status (PHP) */
            case 0x08:
                break;

            /* Pull Accumulator (PLA) */
            case 0x68:
                break;

            /* Push Processor Status (PLP) */
            case 0x28:
                break;

            /* Logical AND (AND) */
            /* Immediate */
            case 0x29:
                /* The immediate value 'M' is the next byte */
                acc &= ram[pc + 1];

                if (acc == 0)
                    status |= ZERO_FLAG;

                if (acc & 0x80)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Zero Page */
            case 0x25:
                /* The value 'M' is a location in the zero page */
                acc &= ram[ram[pc + 1]];

                if (acc == 0)
                    status |= ZERO_FLAG;

                if (acc & 0x80)
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

                if (acc & 0x80)
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

                if (acc & 0x80)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* Absolute, X */
            case 0x3D:
                temp = (ram[pc + 1]) + (ram[pc + 2] << 8);

                acc &= ram[temp + indx];

                if (acc == 0)
                    status |= ZERO_FLAG;

                if (acc & 0x80)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* Absolute, Y */
            case 0x39:
                temp = (ram[pc + 1]) + (ram[pc + 2] << 8);

                acc &= ram[temp + indy];

                if (acc == 0)
                    status |= ZERO_FLAG;

                if (acc & 0x80)
                    status |= NEGATIVE_FLAG;

                pc += 3;
                break;

            /* (Indirect, X) */
            case 0x21:
                temp = (ram[pc + 1] + indx) & 0xFF;

                acc &= ram[ram[temp]];

                if (acc == 0)
                    status |= ZERO_FLAG;

                if (acc & 0x80)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* (Indirect), Y */
            case 0x31:
                temp = ram[pc + 1];

                acc &= ram[ram[temp] + indy];

                if (acc == 0)
                    status |= ZERO_FLAG;

                if (acc & 0x80)
                    status |= NEGATIVE_FLAG;

                pc += 2;
                break;

            /* Exclusive OR (EOR) */
            /* Immediate */
            case 0x49:
                break;

            /* Zero page */
            case 0x45:
                break;

            /* Zero page, X */
            case 0x55:
                break;

            /* Absolute */
            case 0x4D:
                break;

            /* Absolute, X */
            case 0x5D:
                break;

            /* Absolute, Y */
            case 0x59:
                break;

            /* (Indirect, X) */
            case 0x41:
                break;

            /* (Indirect), Y */
            case 0x51:
                break;

            /* Logical Inclusive OR */
            /* Immediate */
            case 0x09:
                break;

            /* Zero page */
            case 0x05:
                break;

            /* Zero page, X */
            case 0x15:
                break;

            /* Absolute */
            case 0x0D:
                break;

            /* Absolute, X */
            case 0x1D:
                break;

            /* Absolute, Y */
            case 0x19:
                break;

            /* (Indirect, X) */
            case 0x01:
                break;

            /* (Indirect), Y */
            case 0x11:
                break;

            /* Bit test (BIT) */
            /* Zero page */
            case 0x24:
                break;

            /* Absolute */
            case 0x2C:
                break;

            /* Add with carry (ADC) */
            /* Immediate mode */
            case 0x69:
                break;

            /* Zero Page */
            case 0x65:
                break;

            /* Zero Page, X */
            case 0x75:
                break;

            /* Absolute */
            case 0x6D:
                break;

            /* Absolute, X */
            case 0x7D:
                break;

            /* Absolute, Y */
            case 0x79:
                break;

            /* (Indirect, X) */
            case 0x61:
                break;

            /* (Indirect), Y */
            case 0x71:
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
                break;

            /* Zero page */
            case 0xC5:
                break;

            /* Zero page, X */
            case 0xD5:
                break;

            /* Absolute */
            case 0xCD:
                break;

            /* Absolute, X */
            case 0xDD:
                break;

            /* Absolute, Y */
            case 0xD9:
                break;

            /* (Indirect, X) */
            case 0xC1:
                break;

            /* (Indirect), Y */
            case 0xD1:
                break;

            /* Compare X Register */
            /* Immediate */
            case 0xE0:
                break;

            /* Zero page */
            case 0xE4:
                break;
            
            /* Absolute */
            case 0xEC:
                break;

            /* Compare Y Register */
            /* Immediate */
            case 0xC0:
                break;

            /* Zero page */
            case 0xC4:
                break;

            /* Absolute */
            case 0xCC:
                break;

            /* Increment Memory (INC) */
            /* Zero page */
            case 0xE6:
                break;

            /* Zero Page, X */
            case 0xF6:
                break;
            
            /* Absolute */
            case 0xEE:
                break;

            /* Absolute, X */
            case 0xFE:
                break;

            /* Increment X Register (INX) */
            case 0xE8:
                break;

            /* Increment Y Register (INY) */
            case 0xC8:
                break;

            /* Decrement Memory (DEC) */
            /* Zero page */
            case 0xC6:
                break;

            /* Zero page, X */
            case 0xD6:
                break;

            /* Absolute */
            case 0xCE:
                break;

            /* Absolute, X */
            case 0xDE:
                break;

            /* Decrement X Register */
            case 0xCA:
                break;

            /* Decrement Y Register */
            case 0x88:
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

            /* Rotate Left */
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
                break;

            /* Indirect */
            case 0x6C:
                break;

            /* Jump to Subroutine */
            case 0x20:
                break;

            /* Return from Subroutine (RTS) */
            case 0x60:
                break;

            /* Branch if Carry Clear (BCC) */
            case 0x90:
                break;

            /* Branch if Carry Set (BCS) */
            case 0xB0:
                break;

            /* Branch if Equal (BEQ) */
            case 0xF0:
                break;

            /* Branch if Minus (BMI) */
            case 0x30:
                break;

            /* Branch if Not Equal (BNE) */
            case 0xD0:
                break;

            /* Branch if Positive */
            case 0x10:
                break;

            /* Branch if Overflow Clear (BVC) */
            case 0x50:
                break;

            /* Branch if Overflow Set (BVS) */
            case 0x70:
                break;

            /* Clear Carry Flag (CLC) */
            case 0x18:
                break;

            /* Clear Decimal Flag (CLD) */
            case 0xD8:
                break;

            /* Clear Interrupt Disable (CLI) */
            case 0x58:
                break;

            /* Clear Overflow Flag (CLV) */
            case 0xB8:
                break;

            /* Set Carry Flag (SEC) */
            case 0x38:
                break;

            /* Set Decimal Flag (SED) */
            case 0xF8:
                break;

            /* Set Interrupt Disable (SEI) */
            case 0x78:
                break;

            /* Force interrupt (BRK) */
            case 0x00:
                break;

            /* No Operation (NOP) */
            case 0xEA:
                break;

            /* Return from Interrupt */
            case 0x40:
                break;

            default:
                fprintf(stderr, "Error: Unrecognized opcode %04x at 0x%04x\n",
                        opcode, pc);
                break;
        }

        BeginDrawing();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
/* EOF */
