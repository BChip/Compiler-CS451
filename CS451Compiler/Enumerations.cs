﻿namespace CS451Compiler
{
    enum Character
    {
        /* Character classes */
        LETTER = 0,
        DIGIT = 1,
        UNKNOWN = 99
    }

    enum Token
    {
        /* Token codes */
        INT_LIT = 10,
        IDENT = 11,
        ASSIGN_OP = 20,
        ADD_OP = 21,
        SUB_OP = 22,
        MULT_OP = 23,
        DIV_OP = 24,
        LEFT_PAREN = 25,
        RIGHT_PAREN = 26,
        LEFT_BRACE = 27,
        RIGHT_BRACE = 28,
        LEFT_BRACKET = 29,
        RIGHT_BRACKET = 29,
        FOR_CODE = 30,
        IF_CODE = 31,
        ELSE_CODE = 32,
        WHILE_CODE = 33,
        DO_CODE = 34,
        INT_CODE = 35,
        FLOAT_CODE = 36,
        SWITCH_CODE = 37,
        STRING_LIT = 38,
        FLOAT_LIT = 39,
        CHAR_LIT= 40,
        UNKNOWN = 41
    }
}
