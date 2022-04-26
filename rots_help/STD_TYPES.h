/****************************************************************************/
#ifndef STD_TYPES_H
#define STD_TYPES_H
/****************************************************************************/
#define NULL_PTR ( (void*)0 )
#define NULL_CHAR '\0'


typedef char				CHAR_t;
typedef unsigned char 		UINT8_t;
typedef unsigned short 		UINT16_t;
typedef unsigned long 		UINT32_t;
typedef unsigned long long 	UINT64_t;

typedef signed char 	 	SINT8_t;
typedef signed short 	 	SINT16_t;
typedef signed long 	 	SINT32_t;
typedef signed long long 	SINT64_t;

typedef float 				FLOAT32_t;
typedef double 				FLOAT64_t;

typedef enum{
	FALSE = 0,
	TRUE
}BOOL_t;

/****************************************************************************/
#endif
/****************************************************************************/
