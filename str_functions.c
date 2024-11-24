/******************************************************************************
AUTHOR : RAYAN LABAY
******************************************************************************/
#include <stdlib.h> /* tolower */
#include <stddef.h> /* size_t */
#include <string.h>
#include <ctype.h>  /* tolower */
/******************************************************************************
DESCRIPTION:
returns the length of a given string. 

RETURN VALUE:
 * length of a given string.
 * 0 if string is NULL.
 
STATUS: DONE
******************************************************************************/
size_t MyStrlen(const char *str)
{
	const char* end = str;
	while(*end++);
	return !str ? (size_t) NULL : (size_t) (end - str - 1);	
}
/****************************************************************************** 
DESCRIPTION:
Compares 2 strings lexicographically. 

RETURN VALUE:
 * 0  if str1 == str2
 * <0 if str1 < str2
 * >0 if str1 > str2  
STATUS: DONE
******************************************************************************/
int MyStrcmp (const char *str1, const char *str2)
{
	while(*str1 && *str1++ == *str2++ );
	return *str1 - *str2;	
}
/****************************************************************************** 
DESCRIPTION:
Copies one src string to dst. 

RETURN VALUE:
 * pointer to dst, where copied value is.
STATUS: DONE
******************************************************************************/
char *MyStrcpy(char *dest, const char *src)
{
	char* dest_t = dest;
	while(*src)
	{
		*dest++ = *src++;
	}
	*dest = '\0';
	return dest_t;
}
/****************************************************************************** 
DESCRIPTION:
Copies one src string to dst, up to n elements. 

RETURN VALUE:
 * pointer to dst, where copied value is.
 * if n > len(src), then dst will be padded untill length is n.
STATUS: DONE
******************************************************************************/
char *MyStrncpy(char *dest, const char *src, size_t n)
{
	char *dest_t = dest;
	size_t i = 0;
	for(i = 0; i < n; i++)
	{
		if(!*src)
			break;
		*dest++ = *src++;	
	}
	while(*src++) *dest++ = '\0';
	return dest_t;	
}
/****************************************************************************** 
DESCRIPTION:
Compares 2 strings neglecting lower or upper case.


RETURN VALUE:
 * 0  if str1 == str2
 * <0 if str1 < str2
 * >0 if str1 > str2 
STATUS: DONE
******************************************************************************/
int MyStrcasecmp(const char *str1, const char *str2)
{
	while(tolower(*(str1++)) == tolower(*(str2++)) && !( *str1 == '\0' || 
	*str2 == '\0'));
	return *str1 > *str2 ? 1 : *str1 < *str2 ? -1 : 0;	
}
/****************************************************************************** 
DESCRIPTION:
returns pointer to the first location where c appears in str.


RETURN VALUE:
 * pointer to the first location where c appears in str.
 * NULL if c doesnt appear in str. 
STATUS: DONE
******************************************************************************/
char *MyStrchr( const char *str, int c )
{
	while(*str != c && *str != '\0')
	{
		str++;
	}
	return (char*)str;
}
/****************************************************************************** 
DESCRIPTION:
duplicates str to another location, allocates new memory and pastes it there. 


RETURN VALUE:
 * pointer to the allocated memory where the duplicated value is.
 * NULL if str is NULL. 
STATUS: DONE
NOTE: test doesnt work
******************************************************************************/
char * MyStrdup( const char *str )
{
	int len = strlen(str) + 1;
	char* newstr = (char*)malloc(len);
	if(str == NULL) return NULL;
	return strcpy(newstr, str);
}
/****************************************************************************** 
DESCRIPTION:
Concatenates two strings, src at the end of dest, doesnt allocate new memory.


RETURN VALUE:
 * pointer to dest. 
STATUS: DONE
******************************************************************************/
char *MyStrcat(char *dest, const char *src)
{
	char *dest_t = dest;
	if(!src) return dest;
	while(*++dest);
	*dest++ = *src++;	
	strcpy(dest, src);
	return dest_t;	
}
/****************************************************************************** 
DESCRIPTION:
Concatenates two strings, src at the end of dest, up to n elements.
Doesnt allocate new memory.


RETURN VALUE:
 * pointer to dest. 
STATUS: DONE
******************************************************************************/
char *MyStrncat(char *dest, const char *src, size_t n)
{
	char *dest_t = dest;
	if(!src) return NULL;
	while(*++dest);
	*dest++ = *src++;	
	strncpy(dest, src, n - 1);
	return dest_t;	
}
/****************************************************************************** 
DESCRIPTION:
Finds the location of the substring needle in haystack and returns pointer to
it.


RETURN VALUE:
 * pointer to first appearance of needle in haystack. 
 * NULL if needle not found in haystack.
STATUS: DONE
******************************************************************************/
char *MyStrstr(const char *haystack, const char *needle)
{
	int j = 0, needle_len = strlen(needle);
	while(*haystack++)
	{
		if(*haystack == *(needle + j))
		{
			j++;
			if( j == needle_len )
				return (char*) (haystack - needle_len + 1);
		}else
		{
			j = 0;
		}
	}
	return NULL;
}
/****************************************************************************** 
DESCRIPTION:
static function, finds if c is in str.

RETURN VALUE:
 * 1 if c found.
 * 0 if c was not found.
******************************************************************************/
static int IsInStr(char* str, char c)
{
	while(*str != c && *str != '\0' ) str++;
	return *str == '\0' ? 0 : 1;
}
/****************************************************************************** 
DESCRIPTION:
Counts how many characters from the begining of str1 are from the set of 
unique(str2), if str2 = "ABB", set(str2) = {A,B}.

RETURN VALUE:
 * as described above.
STATUS: DONE
******************************************************************************/
size_t MyStrspn(const char *str1, const char *str2)
{
	int seen = 0;
	while(*str1)
	{
		if(! IsInStr((char*)str2, *str1++))
		{
			if(seen > 0)
				return seen;
			seen = 0;
		}
		else
		{
			
			seen++;
		}
	}
	return seen == 0 ? 0 : seen;
}
