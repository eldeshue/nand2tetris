// define the type of VM commands.
#ifndef _COMMAND_TYPE_
#define _COMMAND_TYPE_ 

#define C_ADD 1 
#define C_SUB 2
#define C_NEG 3
#define C_EQ 4 
#define C_GT 5 
#define C_LT 6
#define C_AND 7
#define C_OR 8
#define C_NOT 9

#define C_PUSH 10
#define C_POP 11

#define C_LABEL 12

#define C_GOTO 13
#define C_IF 14
#define C_FUNCTION 15
#define C_RETURN 16
#define C_CALL 17

#endif