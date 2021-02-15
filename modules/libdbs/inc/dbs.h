#ifndef __DBS_H__
#define __DBS_H__

#ifdef __cplusplus
extern "C" {
#endif


#define	PT_TYPE_FLOAT		(0L)
#define	PT_TYPE_INT		(1L)
#define	PT_TYPE_UINT		(2L)
#define PT_TYPE_SHORT		(3L)
#define PT_TYPE_USHORT		(4L)
#define PT_TYPE_CHAR		(5L)
#define	PT_TYPE_UCHAR		(6L)
#define PT_TYPE_DOUBLE		(7L)
#define PT_TYPE_STRING		(8L)
#define PT_TYPE_STRUCT		(9L)
#define PT_TYPE_INVALID		(-1L)


#include "rdb.h"
#include "sdb.h"
#include "sqlite3.h"

#ifdef __cplusplus
}
#endif

#endif