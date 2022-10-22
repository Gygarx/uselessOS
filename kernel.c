#include "kernel.h"
#include "keyboard.h"

int VGA_BUFFER_COUNTER = 0;

/*
16 bit video buffer elements(register ax)
8 bits(ah) higher : 
  lower 4 bits - forec olor
  higher 4 bits - back color

8 bits(al) lower :
  8 bits : ASCII character to print
*/
uint16 vga_entry(unsigned char ch, uint8 fore_color, uint8 back_color) {
    uint16 ax = 0;
    uint8 ah = 0, al = 0;

    ah = back_color;
    ah <<= 4;
    ah |= fore_color;
    ax = ah;
    ax <<= 8;
    al = ch;
    ax |= al;

    return ax;
}

//clear video buffer array
void clear_vga_buffer(uint16 **buffer, uint8 fore_color, uint8 back_color){
    uint32 i;
    for(i = 0; i < BUFSIZE; i++){
        (*buffer)[i] = vga_entry(NULL, fore_color, back_color);
    }
}

//initialize vga buffer
void init_vga(uint8 fore_color, uint8 back_color){
    vga_buffer = (uint16*)VGA_ADDRESS;  //point vga_buffer pointer to VGA_ADDRESS 
    clear_vga_buffer(&vga_buffer, fore_color, back_color);  //clear buffer
}

int stringLen(char string[]){
    int i;
    for (i=0; string[i] != '\0'; ++i);
    return i;
}

// 0 -> [  OK  ] GREEN
// 1 -> [ WARN ] YELLOW
// 2 -> [ FAIL ] RED
void dontUseThisPrint(char text[],int type){
    int color;
    switch (type) {
        case 0: color = BRIGHT_GREEN;break;
        case 1: color = YELLOW;break;
        case 2: color = BRIGHT_RED;break;
    }
    int jPRINT;
    for (jPRINT = 0; jPRINT < stringLen(text); jPRINT++) {
        vga_buffer[VGA_BUFFER_COUNTER] = vga_entry(text[jPRINT], color, BLACK);
        VGA_BUFFER_COUNTER++;
    }
}

void print(char text[]){
    int jPRINT;
    for (jPRINT = 0; jPRINT < stringLen(text); jPRINT++) {
        vga_buffer[VGA_BUFFER_COUNTER] = vga_entry(text[jPRINT], WHITE, BLACK);
        VGA_BUFFER_COUNTER++;
    }
    if (stringLen(text) < 80){
        int NEED_TO_FILL = 80 - stringLen(text);
        VGA_BUFFER_COUNTER += NEED_TO_FILL;
    }
}
// 0 -> [  OK  ] GREEN
// 1 -> [ WARN ] YELLOW
// 2 -> [ FAIL ] RED
void fancyPrint(char text[], int type){
    if (type == 0) {
        dontUseThisPrint("[  OK  ] ", type);
    }
    else if (type == 1) {
        dontUseThisPrint("[ WARN ] ", type);
    }
    else if (type == 2) {
        dontUseThisPrint("[ FAIL ] ", type);
    }
    
    int jLOG;
    for (jLOG = 0; jLOG < stringLen(text); jLOG++) {
        vga_buffer[VGA_BUFFER_COUNTER] = vga_entry(text[jLOG], WHITE, BLACK);
        VGA_BUFFER_COUNTER++;
    }
    if (stringLen(text) < 80){
        int NEED_TO_FILL = 80 - (stringLen(text)+9);
        VGA_BUFFER_COUNTER += NEED_TO_FILL;
    }
}

void printInt(int num) {
    int length = 0;
    int count = 0; 
    int tempNum = num;
    int divnum = 10;
    if (num != 0) {
        while(tempNum != 0){
            tempNum = tempNum / 10;
            length++;
        } 
    }
    else{
        length = 1;
    }
    for (int i = length; i > 2; i--) {
        divnum = divnum * 10;
    }
    tempNum = 0;
    do{
        tempNum = num / divnum;
        vga_buffer[VGA_BUFFER_COUNTER] = vga_entry(tempNum+48, WHITE, BLACK);
        VGA_BUFFER_COUNTER++;
        num = num % divnum;
        divnum = divnum/10;
        count++;
    }while(num != 0);  
}

void kernel_entry(){
  init_vga(WHITE,BLACK);
  print("ok");

}
