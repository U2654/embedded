void waitcount()
{
	volatile int i = 0, j = 0;
	for (i = 0; i < 4210; i++)
	{
		if (i > 200)
		{
			j++; 
		}
		else
		{
			j--;
		}
	}
}
 