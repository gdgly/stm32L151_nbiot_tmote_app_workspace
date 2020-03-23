#ifndef __RADIO_COMPILER_DEFS_H
#define   __RADIO_COMPILER_DEFS_H

#include "sys.h"

#ifndef NULL
#define NULL					0
#endif

#define LSB					0
#define MSB					1

#define b0					0
#define b1					1
#define b2					2
#define b3					3

typedef bool					BIT;
typedef unsigned char			U8;
typedef unsigned int			U16;
typedef unsigned long			U32;

typedef signed char				S8;
typedef signed int				S16;
typedef signed long				S32;

typedef union UU16
{
	U16		U16;
	S16		S16;
	U8		U8[2];
	S8		S8[2];
} UU16;

typedef union UU32
{
	U32		U32;
	S32		S32;
	UU16		UU16[2];
	U16		U16[2];
	S16		S16[2];
	U8		U8[4];
	S8		S8[4];
} UU32;

#endif /* __RADIO_COMPILER_DEFS_H */
