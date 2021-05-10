#include "encoding.h"
#include "platform.h"
#include "proto.h"

#define SIZE 256

int a[SIZE];

void PROFILE loop()
{
	volatile int n = 0;
	int i=0;
	for (i = 0; i < SIZE; ++i)
	{
		a[i] = i;
		n += a[i];
	}
}

void PROFILE unroll4()
{
	volatile int n = 0;
	int i=0;
	for (i = 0; i < SIZE; i+=4)
	{
		a[i] = i;
		a[i+1] = i+1;
		a[i+2] = i+2;
		a[i+3] = i+3;
		n += a[i];
		n += a[i+1];
		n += a[i+2];
		n += a[i+3];
	}
}

void PROFILE unroll8()
{
	volatile int n = 0;
	int i=0;
	for (i = 0; i < SIZE; i+=8)
	{
		a[i] = i;
		a[i+1] = i+1;
		a[i+2] = i+2;
		a[i+3] = i+3;
		a[i+4] = i+4;
		a[i+5] = i+5;
		a[i+6] = i+6;
		a[i+7] = i+7;
		n += a[i];
		n += a[i+1];
		n += a[i+2];
		n += a[i+3];
		n += a[i+4];
		n += a[i+5];
		n += a[i+6];
		n += a[i+7];
	}
}


int PROFILE main(int argc, char **argv)
{
	for (int i = 0; i < 1000; ++i)
	{
		loop();
		unroll4();
		unroll8();
	}
	return 0;
}
