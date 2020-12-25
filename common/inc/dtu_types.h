/**
 * @file dtu_types.h
 * @brief
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-11
 * @copyright Copyright (c) 2020
 * @par Log:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-11 <td>1.0     <td>wangh     <td>内容
 * </table>
 */
#ifndef __DTU_TYPES_H__
#define __DTU_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined SIMULATOR
#include <stddef.h>
#include <stdbool.h>
#else
#ifndef M4FIRMWARE
#include <stddef.h>
#include <stdbool.h>
#else
typedef enum {
	false = 0,
	true = !false
} bool;
#endif
#endif

#ifndef TRUE
#define TRUE	true
#endif

#ifndef FALSE
#define FALSE	false
#endif

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;

typedef int int32;
typedef short int16;
typedef char int8;

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

#ifndef container_of

#define __compiler_offsetof(a,b) __builtin_offsetof(a,b)
#ifdef __compiler_offsetof
#ifndef offsetof
#define offsetof(TYPE, MEMBER) 	__compiler_offsetof(TYPE,MEMBER)
#endif
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

#define container_of(ptr, type, member) ({	    \
				const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
				(type *)( (char *)__mptr - offsetof(type,member) );})
#endif


enum address_type {
	AT_NONE,               /* no link-layer address */
	AT_ETHER,              /* MAC (Ethernet, 802.x, FDDI) address */
	AT_IPv4,               /* IPv4 */
	AT_IPv6,               /* IPv6 */
	AT_IPX,                /* IPX */
	AT_FC,                 /* Fibre Channel */
	AT_FCWWN,              /* Fibre Channel WWN */
	AT_STRINGZ,            /* null-terminated string */
	AT_EUI64,              /* IEEE EUI-64 */
	AT_IB,                 /* Infiniband GID/LID */
	AT_AX25,               /* AX.25 */
	AT_VINES,              /* Banyan Vines address */
	AT_END_OF_LIST         /* Must be last in list */
};



#ifdef __cplusplus
}
#endif
#endif