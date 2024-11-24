/******************************************************************************
*	AUTHOR	: RAYAN LABAY
******************************************************************************/
long Pow2(unsigned int x, unsigned int y);
int CheckPow2(unsigned int x);
int AddOne(int x);
unsigned int ByteMirror2(unsigned int x);
unsigned int ByteMirror(unsigned int b);
int CntSetBitsLoop(unsigned int x);
unsigned int BitCount(unsigned int x);
/*	ByteMirror  -------------------------------------------------------------
*	with no loop
*	-------------------------------------------------------------------------
*/
unsigned int BitCount(unsigned int x)
{
	x = (x & (0x55555555)) + ((x >> 1) & (0x55555555));
    x = (x & (0x33333333)) + ((x >> 2) & (0x33333333));
    x = (x & (0x0f0f0f0f)) + ((x >> 4) & (0x0f0f0f0f));
    x = (x & (0x00ff00ff)) + ((x >> 8) & (0x00ff00ff));
    x = (x & (0x0000ffff)) + ((x >> 16) & (0x0000ffff));
    return x;
}
unsigned int ByteMirror(unsigned int num)
{
	/* A better solution from StackOverflow ... */
	num = ((num & 0xFFFF0000) >> 16) | ((num & 0x0000FFFF) << 16);
	num = (num & 0xFF00FF00) >> 8 | (num & 0x00FF00FF) << 8;
	num = (num & 0xF0F0F0F0) >> 4 | (num & 0x0F0F0F0F) << 4;
	num = (num & 0xCCCCCCCC) >> 2 | (num & 0x33333333) << 2;
	num = (num & 0xAAAAAAAA) >> 1 | (num & 0x55555555) << 1;
	return num; 
}
/* 	ByteMirror --------------------------------------------------------------
*	with loop
*	-------------------------------------------------------------------------
*/
unsigned int ByteMirror2(unsigned int x)
{
	unsigned int rmask = 1, lmask = 0x80000000;
	unsigned int move = 0;
	unsigned int swap = 0, rmost = 0, lmost = 0;
	unsigned int mask = 0, without = 0;
	while(move < 16)
	{
		rmask = rmask << move;
		lmask = lmask >> move;
		lmost = lmask & x;
		rmost = rmask & x;
		swap = (rmost << (31 - (move*2))) | (lmost >> (31 - (move*2)));
		mask = lmask | rmask;
		mask = ~mask;		
		without = x & mask; 
		x = without | swap;
		rmask = 1;
		lmask = 0x80000000;
		swap = 0;	 
		move++;
	}
	return x;
	
}
/*	Pow2 --------------------------------------------------------------------
*	returns x*(2^y) 
*	-------------------------------------------------------------------------
*/
long Pow2(unsigned int x, unsigned int y)
{
	return x << y;
}
/* 	CheckPow2 ---------------------------------------------------------------
*	check if x is a power of 2
*	-------------------------------------------------------------------------
*/
int CheckPow2(unsigned int x)
{
	return 	!(x & (x - 1));
}
/*  CheckPow2Loop -----------------------------------------------------------
*	check if x is a power of 2 with loop.
*	-------------------------------------------------------------------------
*/
int CheckPow2Loop(unsigned int x)
{
		unsigned int i = 0;
		if(x == 1)
		{
			return x;
		}
		for(i = 1; i <= x; i = i << 1)
		{
			if((x^2) == 0)
				return 1;	
		}
		return 0;
}
/*	CountSetBitsLoop ---------------------------------------------------------
*	Count number of bits on with loop.
*	--------------------------------------------------------------------------
*/
int CntSetBitsLoop(unsigned int x)
{
	int i = 0, cnt = 0;
	for(i = 0; i < 32; i++)
	{
		cnt += (x&1);
		x = (x >> 1);
	}
	return cnt;
}
/******************************************************************************
*	AddOne adds one to a number without arithmetic operations.
******************************************************************************/
int AddOne(int b)
{
	unsigned int x = (unsigned int)b;
	int lsb = 0, steps = 0;
	unsigned int mask_ = -1;
	int ret = 0;
	if(b == 0)
	{
		return 1;
	}

	if(x%2 == 0)
	{
		return x | 1;
	}
	lsb = Find0LSB(x); /*index of where first zero from right to left*/
	steps = 32 - lsb;
	mask_ = mask_ << steps;
	mask_ = mask_ >> steps;
	mask_ = mask_ << 1;
	mask_++;
	ret = (int) x^mask_;
	return ret;
}
