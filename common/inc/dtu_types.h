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

#ifndef BOOL
#define BOOL	int
#endif

#ifndef TRUE
#define TRUE	(-1)
#endif

#ifndef FALSE
#define FALSE	(0)
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

#if defined SIMULATOR
#include <stddef.h>
#else
#if defined M4FIRMWARE
#elif (defined A9APP)
#include <stddef.h>
#elif
#endif
#endif

#ifdef __cplusplus
}
#endif
#endif