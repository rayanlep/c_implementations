/*******************************************************************************
*	AUTHOR: 	Rayan Labay
*******************************************************************************/
/*******************************************************************************
*	DEFINES
*******************************************************************************/
#define NUM_TO_ASCII 	48
#define CHAR_BIT 		8
#define BIT_ARRAY_LEN 	(sizeof(size_t)*CHAR_BIT)

typedef size_t bit_array_t;
/*******************************************************************************
description:  return bit array with all the bits set
*****************************************************************************/
bit_array_t TurnOnAllBits(bit_array_t bit_arr)
{
	size_t zero = 0;
	UNUSED(bit_arr);
	return ~zero;
}

/*******************************************************************************
description:  return bit array with all the bits off
*******************************************************************************/
bit_array_t TurnOffAllBits(bit_array_t bit_arr)
{
	UNUSED(bit_arr);
	return 0;
}

/*******************************************************************************
description:  return bit array with bit in index i on.
*******************************************************************************/
bit_array_t TurnOnBit(bit_array_t bit_arr, size_t idx)
{
	return bit_arr | ((size_t	)1 << idx);
}

/*******************************************************************************
description:   return bit array with bit in index "idx" off.
*******************************************************************************/
bit_array_t TurnOffBit(bit_array_t bit_arr, size_t idx)
{
	return bit_arr & (~((size_t)1 << idx));
}

/*******************************************************************************
description:  changes the set value of a bit by index "idx" in given bit array
              to the given "boolean_val".
*******************************************************************************/ 
bit_array_t TurnBitOnOrOff(bit_array_t bit_arr, size_t idx, int boolean_val)
{
	return boolean_val ? BitArrSetOn(bit_arr, idx) : BitArrSetOff(bit_arr, idx);
}

/*******************************************************************************
description:  get the  value of the bit by index "idx" in given bit array.
return value: boolean 1/0. 
*******************************************************************************/
int BitVal(bit_array_t bit_arr, size_t idx)
{
	return (bit_arr >> idx)&1;
}

/*******************************************************************************
description:  change the value of a bit in index "idx" in given "bit_arr".
*******************************************************************************/ 
bit_array_t FlipBit(bit_array_t bit_arr, size_t idx)
{
	return bit_arr ^ ((size_t)1 << idx);
}

/*******************************************************************************
description:  reverses all bits in given "bit_arr".
arguments:    bit array pointer.
*******************************************************************************/
bit_array_t Mirror(bit_array_t bit_arr)
{
	bit_array_t mask_1_left       = 0xAAAAAAAAAAAAAAAA;    /* odd and even  */
	bit_array_t mask_1_right      = 0x5555555555555555;    /* odd and even  */
	bit_array_t mask_2_left       = 0xCCCCCCCCCCCCCCCC;    /* pairs 		*/
	bit_array_t mask_2_right      = 0x3333333333333333;    /* pairs 		*/
	bit_array_t mask_4_left       = 0xF0F0F0F0F0F0F0F0;    /* fours  		*/
	bit_array_t mask_4_right      = 0x0F0F0F0F0F0F0F0F;    /* fours  		*/
	bit_array_t mask_8_left       = 0xFF00FF00FF00FF00;	   /* 8s	 		*/
	bit_array_t mask_8_right      = 0x00FF00FF00FF00FF;	   /* 8s	 		*/
	bit_array_t mask_16_left      = 0xFFFF0000FFFF0000;	   /* 16s			*/
	bit_array_t mask_16_right     = 0x0000FFFF0000FFFF;	   /* 16s			*/
	bit_array_t mask_32_left      = 0xFFFFFFFF00000000;	   /* 16s			*/
	bit_array_t mask_32_right     = 0x00000000FFFFFFFF;	   /* 16s			*/
	
	
	bit_arr = ((bit_arr & mask_32_left) >> 32) | 
    								((bit_arr & mask_32_right) << 32);
    bit_arr = (bit_arr & mask_16_left) >> 16 | 
    								(bit_arr & mask_16_right) << 16;
    bit_arr = (bit_arr & mask_8_left) >> 8 | 
    								(bit_arr & mask_8_right) << 8;
    bit_arr = (bit_arr & mask_4_left) >> 4 | 
    								(bit_arr & mask_4_right) << 4;
    bit_arr = (bit_arr & mask_2_left) >> 2 | 
    								(bit_arr & mask_2_right) << 2;
    bit_arr = (bit_arr & mask_1_left) >> 1 | 
    								(bit_arr & mask_1_right) << 1;
	
    
    return bit_arr;
}

/*******************************************************************************
description:  rotate right "shifts" times the bits in given bit array.
arguments:    shifts- number of rotations.
*******************************************************************************/
bit_array_t RotateR(bit_array_t bit_arr, size_t shifts)
{
	shifts = shifts % BIT_ARRAY_LEN;
	return (bit_arr << (BIT_ARRAY_LEN - shifts)) | (bit_arr >> shifts);
}

/*******************************************************************************
description:  rotate left n times the bits in given bit array.
arguments:    bit array pointer, size_t number of rotations.
*******************************************************************************/
bit_array_t RotateL(bit_array_t bit_arr, size_t shifts)
{
	shifts = shifts % BIT_ARRAY_LEN;
	return (bit_arr >> (BIT_ARRAY_LEN - shifts)) | (bit_arr << shifts);
}


size_t CountOnBits(bit_array_t bit_arr)
{
	bit_array_t mask_1 = 0x5555555555555555;    /* odd and even */
	bit_array_t mask_2 = 0x3333333333333333;    /* pairs 		*/
	bit_array_t mask_4 = 0x0F0F0F0F0F0F0F0F;    /* fours  		*/
	bit_array_t mask_8 = 0x00FF00FF00FF00FF;	/* 8s	 		*/
	bit_array_t mask_16= 0x0000FFFF0000FFFF;	/* 16s			*/
	bit_array_t mask_32= 0x00000000FFFFFFFF;	/* 16s			*/
	
	
	bit_arr = (bit_arr & mask_1) + ((bit_arr >> 1) & mask_1);
    bit_arr = (bit_arr & mask_2) + ((bit_arr >> 2) & mask_2);
    bit_arr = (bit_arr & mask_4) + ((bit_arr >> 4) & mask_4);
    bit_arr = (bit_arr & mask_8) + ((bit_arr >> 8) & mask_8);
    bit_arr = (bit_arr & mask_16) + ((bit_arr >> 16) & mask_16);
    bit_arr = (bit_arr & mask_32) + ((bit_arr >> 32) & mask_32);
    
    return bit_arr;
}

/*******************************************************************************
description:  returns number of unset (off) bits in given "bit_arr" 
*******************************************************************************/
size_t CountOffBits(bit_array_t bit_arr)
{
	return BIT_ARRAY_LEN - BitArrCountOn(bit_arr);
}











