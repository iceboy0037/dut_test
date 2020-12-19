/**
 * @file dbg.h
 * @brief some debug definition
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-16
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-16 <td>1.0     <td>rock     <td>
 * </table>
 */
#ifndef __DBG_H__
#define __DBG_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined SIMULATOR
	#define println				printf
	#define logd				printf
	#define flushout			fflush
#else
	#if defined M4FIRMWARE
		#define	println
		#define logd
		#define flushout
	#elif defined A9APP
		#define println			printf
		#define logd			printf	
		#define flushout
	#endif
	#ifdef A9KERNEL
		#define println			printk
		#define logd			printf
		#define flushout
	#endif
#endif
//
#define LOG_EMERG	"<0>"
#define LOG_ALERT	"<1>"
#define LOG_CRIT	"<2>"
#define LOG_ERR		"<3>"
#define LOG_WARNING	"<4>"
#define LOG_NOTICE	"<5>"
#define LOG_INFO	"<6>"
#define LOG_DEBUG	"<7>"

#define DEFAULT_MESSAGE_LOGLEVEL

int plog(int level, char *fmt, ...);

#define __DEBUG__		1

#if __DEBUG__
#define dbg(fmt, args...)       do {\
		println("[Line:%d]Func-%s:", __LINE__, __FUNCTION__);\
		println(fmt, ##args);\
		fflush(stdout);\
	} while (0)
#else
#define dbgInit(name)
#define dbg
#endif

#define PRINT_HEX	0
#define PRINT_DEC 	1

/**
 * @brief Printf float array
 * @param  buf memory buffer entry
 * @param  len size in floats
 * @return int
 */
extern int print_float(float *buf, int len);

/**
 * @brief Print memory buffer
 * @param  buf	memory buffer entry
 * @param  len	size in ints
 * @param  type	PRINT_DEC or PRINT_HEX
 * @return int 0 - success
 */
extern int print_int32(int *buf, int len, int type);

/**
 * @brief Print memory buffer
 * @param  buf	memory buffer entry
 * @param  len	size in short
 * @param  type	PRINT_DEC or PRINT_HEX
 * @return int 0 - success
 */
extern int print_int16(short *buf, int len, int type);

/**
 * @brief Print memory buffer
 * @param  buf	memory buffer entry
 * @param  len	size in bytes
 * @param  type	PRINT_DEC or PRINT_HEX
 * @return int 0 - success
 */
extern int print_buf(char *buf, int len, int type);

#ifdef __cplusplus
}
#endif
#endif
