#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

int token;            // current token
char *src, *old_src;  // pointer to source code string;
int poolsize;         // default size of text/data/stack
int line;             // line number

int *text,            // text segment
    *old_text,        // for dump text segment
    *stack;           // stack
char *data;           // data segment

int *pc, *bp, *sp, ax, cycle; // virtual machine registers

// instructions
enum { LEA ,IMM ,JMP ,CALL,JZ  ,JNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PUSH,
       OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,
       OPEN,READ,CLOS,PRTF,MALC,MSET,MCMP,EXIT };


void next() {
    token = *(src++);
    return;
}

void expression(int level) {
    // do nothing
}

void program() {
    next();                  // get next token
    while (token > 0) {
        printf("token is: %c\n", token);
        next();
    }
}


int eval() { // do nothing yet
    return 0;
}

int main(int argc, char **argv)
{
    int i;
    FILE* fd;
    argc--;
    argv++;

    poolsize = 256 * 1024; // arbitrary size
    line = 1;

    //看看能不能打开文件
    if ((fd = fopen(*argv, "r")) == NULL) {
        printf("could not open(%s)\n", *argv);
        return -1;
    }

    //分配内存
    if (!(src = old_src = (char*)malloc(poolsize))) {
        printf("could not malloc(%d) for source area\n", poolsize);
        return -1;
    }


    // read the source file
    if ((i = fread(src, 1, poolsize-1, fd)) <= 0) {
        printf("read() returned %d\n", i);
        return -1;
    }
    src[i] = 0; // add EOF character
    fclose(fd);


    // allocate memory for virtual machine
    if (!(text = old_text = (int*)malloc(poolsize))) {
        printf("could not malloc(%d) for text area\n", poolsize);
        return -1;
    }
    if (!(data = (char*)malloc(poolsize))) {
        printf("could not malloc(%d) for data area\n", poolsize);
        return -1;
    }
    if (!(stack = (int*)malloc(poolsize))) {
        printf("could not malloc(%d) for stack area\n", poolsize);
        return -1;
    }

    memset(text, 0, poolsize);
    memset(data, 0, poolsize);
    memset(stack, 0, poolsize);


    bp = sp = (int *)((int)stack + poolsize);
    ax = 0;







    program();
    return eval();
}