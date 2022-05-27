#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
void writeRC(char data)
{
    outportb(0x37A, 0x04);
    outport(0x378, data);
    outportb(0x37A, 0x00);
    delay(1);
    outport(0x37A, 0x04);
}
void writeRD(char data)
{
    outportb(0x37A, 0x0E);
    outportb(0x378, data);
    outport(0x37A, 0x0A);
    delay(1);
    outportb(0x37A, 0x0E);
}
char readRD()
{
    static char ans=0;
    outportb(0x37A, 0x2E);
    outportb(0x378, 0xFF);
    outportb(0x37A, 0x2F);
    delay(1);
    ans=inportb(0x378);
    outportb(0x37A, 0x04);
    return(and^0xFF);
}
void stop()
{
    writeRC(0x11);
    writeRD(0x00);
    writeRD(0x00);
}
int count(int a)
{
    unsigned char SNS0;
    unsigned char SNS1;
    unsigned char SNS2;
    int mas0[6];
    int mas1[6];
    int x=0;
    int d=0;
    do
    {
        writeRC(0x13);
        SNS0=readRD();
        SNS1=readRD();
        SNS2=readRD();
        for (int i=0; i<6; i++)
        {
            mas0[i]=(SNS0>>i)&0x01;
            mas1[i]=(SNS1>>i)&0x01;
        }
        if (a==0)
        {
            if(mas0[2]!=x)
            {
                x=mas0[2];
                d++;
            }
        }
        if (a==1)
        {
            if(mas0[5]!=x)
            {
                x=mas0[5];
                d++;
            }
        }
        if (a==2)
        {
            if(mas1[2]!=x)
            {
                x=mas1[2];
                d++;
            }
        }
        if ((mas0[0]==1)||(mas0[1]==1)||(mas0[3]==1)||(mas0[4]==1)||(mas1[0]==1)||(mas1[1]==1)) break;
    }
    while (!kbhit());
    return (d);
}
void control()
{
    int b=0;
    int x=0;
    int axis=0;
    printf("enter axis (0-M0, 1-M1, 2-M2): ");
    scanf("%d", &axis);
    printf("enter distance: ");
    scanf("%d", &x);
    writeRC(0x11);
    writeRD(0x80);
    if (axis==0)
    {
        if (x>0)
        {
            writeRD(0x02);
            if (count(0)==x)stop();
        }
        if (x<0)
        {
            writeRD(0x01);
            if (count(0)==x)stop();
        }
    }
    if (axis==1)
    {
        if (x>0)
        {
            writeRD(0x08);
            if (count(0)==x)stop();
        }
        if (x<0)
        {
            writeRD(0x04);
            if (count(0)==x)stop();
        }
    }
    if (axis==2)
    {
        if (x>0)
        {
            writeRD(0x20);
            if (count(0)==x)stop();
        }
        if (x<0)
        {
            writeRD(0x10);
            if (count(0)==x)stop();
        }
    }
}
int main()
{
    control();
    getch();
    return 0;
}
