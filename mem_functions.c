/*******************************************************************************
*	AUTHOR:		Rayan Labay
*******************************************************************************/
#include <stddef.h>	 	/* size_t			*/
#include <stdio.h> 		/* printf			*/
#include <assert.h>		/* assert 			*/
#include <string.h> 	/* strcmp, strcpy 	*/
/*******************************************************************************
*	DEFINES 
*******************************************************************************/
#define ALIGN_OFFSET(dest) (((size_t)dest % WORD_SIZE) % WORD_SIZE)
#define MIN(a, b) ((a < b) ? a : b)
#define CHAR_BIT 8 		/* 8 bits */
#define WORD_SIZE 8		/* 8 bytes */

/*******************************************************************************
*	DECLARATIONS 
*******************************************************************************/
static size_t InitWordMask(unsigned char c);

void *Memset(void *dest, int c, size_t n_bytes);
void *Memcpy(void *dest, const void *src, size_t n_bytes);
void *Memmove(void *dest, const void *src, size_t n_bytes);

/*******************************************************************************
*	DESCRIPTION:	static function that initializes a word size duplication
*					of the character c. 
*******************************************************************************/
static size_t InitWordMask(unsigned char c)
{
	size_t res = c;
	res = res | (res << CHAR_BIT) | (res << 2*CHAR_BIT) | res << (3*CHAR_BIT);
	res = res | (res << WORD_SIZE/2);  
	return res;
}

void *Memset(void *dest, int c, size_t n_bytes)
{
	unsigned char *char_ptr = (unsigned char*)dest;
	size_t *word_ptr = (size_t*)dest;
	
	/*	num_left_chars 	- number of bytes to copy before alignment 
		num_words 		- number of words to copy 
		num_right_chars	- number of bytes after we copied all words  */
	size_t num_left_chars = MIN(ALIGN_OFFSET(dest), n_bytes);
	size_t num_words = (n_bytes - num_left_chars)/8;
	size_t num_right_chars = (n_bytes - num_left_chars)%8;
	
	/* words_mask - word size duplication of the character c */
	size_t word_mask = InitWordMask(c); 
	

	while(num_left_chars)
	{	
		*char_ptr = c;
		
		++char_ptr;
		--num_left_chars;
	}
	
	word_ptr = (size_t*)char_ptr;
	while(num_words)
	{
		*word_ptr = word_mask;
		
		--num_words;
		--word_ptr;
	}
	
	char_ptr = (unsigned char*)word_ptr;
	while(num_right_chars)
	{
		*char_ptr = c;
		
		++char_ptr;
		--num_right_chars;
	}
	
	return dest;
}
void *Memcpy(void *dest, const void *src, size_t n_bytes)
{
	unsigned char *dest_char_ptr = (unsigned char*)dest;
	unsigned char *src_char_ptr = (unsigned char*)src;
	size_t *dest_word_ptr = (size_t*)dest;
	size_t *src_word_ptr = (size_t*)src;
	 
	 
	 /*	num_words 		- number of words to copy 
		num_right_chars	- number of bytes after we copied all words  */
	size_t num_words = n_bytes/WORD_SIZE;
	/* without remainder */
	size_t num_right_chars = n_bytes%WORD_SIZE;
	
	while(num_words)
	{
		*dest_word_ptr = *src_word_ptr;
		
		++dest_word_ptr;
		++src_word_ptr;
		--num_words;
	}
	
	dest_char_ptr = (unsigned char*)dest_word_ptr;
	src_char_ptr = (unsigned char*)src_word_ptr;
	while(num_right_chars)
	{
		*dest_char_ptr = *src_char_ptr;
		
		++dest_char_ptr;
		++src_char_ptr;
		--num_right_chars;
	}
	
	return dest;
}

void *Memmove(void *dest, const void *src, size_t n_bytes)
{
	unsigned char *dest_char_ptr = (unsigned char*)dest;
	unsigned char *src_char_ptr = (unsigned char*)src;
	
	   
	if(dest_char_ptr < src_char_ptr)
	{
		return Memcpy(dest, src, n_bytes);
	}
	
	while(n_bytes)
	{
		*dest_char_ptr = *src_char_ptr;
		
		++dest_char_ptr;
		++src_char_ptr;
		--n_bytes;
	}

	return dest;
}































