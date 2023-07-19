// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

(JUMP)
    @KBD
    D=M
    @BLACK
    D;JGT
    @WHITE
    0;JMP 

// 使用A指令后，如果用字符A则代表使用A中存的是常数
// 使用字符M则代表A中存的是地址

(WHITE)
    @R0
    M=0
    (WHITELOOP)
        @8192
        D=A
        @R0
        D=D-M
        @JUMP
        D;JEQ
        @R0
        D=M
        @R0
        M=M+1
        
        @SCREEN   // keypoint
        A=D+A     // keypoint，更新A的值
        M=0       // keypoint，改变A‘的值

        @WHITELOOP
        0; JMP

(BLACK)
    @R1
    M=0
    (BLACKLOOP)
        @8192
        D=A
        @R1
        D=D-M
        @JUMP
        D;JEQ
        @R1
        D=M
        @R1
        M=M+1

        @SCREEN
        A=D+A
        M=-1

        @BLACKLOOP
        0; JMP
