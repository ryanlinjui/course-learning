// Morse Code Display for 'c' and 's'
// 'dit' (.) should be 2-pixel thick and 1-pixel wide
// 'dah' (-) should be 2-pixel thick and 3-pixel wide
// 'blank' should be 1-pixel between 'dit' & 'dah'
// Note: Each encoded character will be 16 pixels wide because of padding

// c: -.-. pattern = 1495 decimal
/* 
1 1 1 0 1 0 1 1 1 0 1 0 0 0 0 0 // 1495
1 1 1 0 1 0 1 1 1 0 1 0 0 0 0 0 // 1495
*/

// s: ...  pattern = 21 decimal 
/*
1 0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 // 21
1 0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 // 21
*/

// Print at SCREEN + 128 & Keyboard I/O
// SCREEN = 16384
// SCREEN + 128 = 16384 + 128 * 16 = 18432
// SCREEN + 128 + 32-bits = 18432 + 32 = 18464 (for pixel thick)
// KEYBOARD = 24576

(LOOP)
    // keyboard input
    @24576
    D=M

    // check if 'c' (ASCII: 99)
    @99
    D=D-A
    @PRINT_C
    D;JEQ
    
    // keyboard input
    @24576
    D=M
    
    // check if 's' (ASCII: 115)
    @115
    D=D-A
    @PRINT_S
    D;JEQ

    // otherwise, clear all
    @CLEAR
    0;JMP

(PRINT_C)
    // first line
    @1495
    D=A
    @18432
    M=D

    // second line
    @1495
    D=A
    @18464
    M=D

    // return
    @LOOP
    0;JMP

(PRINT_S)    
    // first line
    @21
    D=A
    @18432
    M=D

    // second line
    @21
    D=A
    @18464
    M=D

    // return
    @LOOP
    0;JMP

(CLEAR)    
    // first line
    @0
    D=A
    @18432
    M=D

    // second line
    @0
    D=A
    @18464
    M=D

    // return
    @LOOP
    0;JMP