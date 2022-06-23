#ifndef __EvaVM_h
#define __EvaVM_h
#include <string>
#include <vector>
#include <iostream>
#include <array>
#include "../Logger.h"
#include "../bytecode/Opcode.h"
#include "EvaValue.h"

#define READ_BYTE() *ip++

/**
 * @Stack top (stack overflow after exceeding)
 *
 */
#define STACK_LIMIT 512

#define GET_CONST() constants[READ_BYTE()]

#define BINARY_OP(op)                \
    do                               \
    {                                \
        auto op2 = AS_NUMBER(pop()); \
        auto op1 = AS_NUMBER(pop()); \
        push(NUMBER(op1 op op2));    \
    } while (false)

/**
 * @Eval Virtual Machine
 *
 */
class EvaVM
{
public:
    EvaVM() {}

    void push(const EvaValue &value)
    {
        if ((size_t)(sp - stack.begin()) == STACK_LIMIT)
        {
            DIE << "push(): Stack overflow.\n";
        }
        *sp = value;
        sp++;
    }

    EvaValue pop()
    {
        if (sp == stack.begin())
        {
            DIE << "pop(): empty stack. \n";
        }

        --sp;
        return *sp;
    }

    EvaValue exec(const std::string &program)
    {
        // 1. parse the program
        // 2. Compile to bytecode

        constants.push_back(NUMBER(10));
        constants.push_back(NUMBER(2));
        constants.push_back(NUMBER(3));
        code = {OP_CONST, 0, OP_CONST, 1, OP_MUL, OP_CONST, 2, OP_SUB, OP_HALT};

        /**
         * Bytecode
         *
         */
        ip = &code[0];
        sp = &stack[0];

        return eval();
    }

    EvaValue eval()
    {
        for (;;)
        {
            auto opcode = READ_BYTE();

            switch (opcode)
            {
            case OP_HALT:
                return pop();
            case OP_CONST:
                push(GET_CONST());
                break;

            case OP_ADD:
            {
                BINARY_OP(+);
                break;
            }

            case OP_SUB:
            {
                BINARY_OP(-);
                break;
            }

            case OP_MUL:
            {
                BINARY_OP(*);
                break;
            }
            case OP_DIV:
            {
                BINARY_OP(/);
                break;
            }

            default:
                DIE << "Unknown opcode: " << std::hex << opcode;
            }
        }
    }

    uint8_t *ip;

    /**
     * @Stack pointer
     */
    EvaValue *sp;

    /**
     * @Operands stack
     */
    std::array<EvaValue, STACK_LIMIT> stack;

    /**
     * @Constant pool
     */
    std::vector<EvaValue> constants;
    std::vector<uint8_t> code;
};
#endif