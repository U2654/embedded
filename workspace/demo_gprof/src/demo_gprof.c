// See LICENSE for license details.

#include "encoding.h"
#include "platform.h"
#include "proto.h"

#define SIZE 128

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
	for (i = 0; i < SIZE/4; i+=4)
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

int PROFILE main(int argc, char **argv)
{
	for (int i = 0; i < 1000; ++i)
	{
		loop();
		unroll4();
	}

	return 0;
}
