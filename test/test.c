#include "stdio.h"

void printInt(int num) {
    printf("ok\n");
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
    //changet i > 0 to i > 3
    for (int i = length; i > 2; i--) {
            divnum = divnum * 10;
            printf("%u,%u\n",divnum,i);
        }
    tempNum = 0;
    do{
        tempNum = num / divnum;
        printf("%u\n",tempNum);
        num = num % divnum;
        divnum = divnum/10;
        count++;
    }while(num != 0);  
}



int main()
{
  printInt(1234);
}