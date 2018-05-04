#include<stdio.h>
void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}
int main(){

    unsigned char a = 'N';
    unsigned char hide = 1;
    unsigned char temp = 0;
    unsigned char store = 0, tempStore = 0;
    printf("%d %d\n",hide<<7,hide<<8);
    for(int i=0;i<8;i++){
        //Hiding
        temp = a&hide;
        store>>=1;
        a>>=1;
        temp <<= (7);
        printBits(sizeof(temp),&temp);
        printf("Store and temp = %d\n",store|temp);
        store = store | temp;
       
        
        printf("Store = %d ",store);
        printBits(sizeof(store),&store);
        printf("\n");
        temp = 0;
        //End Hiding
    }
    //TODO: 
    //Extraction of data
    unsigned char c = 0;
    unsigned char unhide = 1;
    for(int i=0;i<8;i++){
        //Hiding
        c>>=1;
        temp = store&unhide;
        store>>=1;
        // a>>=1;
        temp <<= (7);
        printBits(sizeof(temp),&temp);
        printf("Store and temp = %d\n",store|temp);
        c = c|temp;
        
       
        
       
        temp = 0;
        //End Hiding
    }

    //End extraction
    printf("%d\n", c);
    return 0;
}
