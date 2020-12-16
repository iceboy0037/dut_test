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

#define __DEBUG__			1

#if __DEBUG__
#define dbg(fmt, args...)       do {\
		printf("[Line:%d]Func-%s:", __LINE__, __FUNCTION__);\
		printf(fmt, ##args);\
		fflush(stdout);\
	} while (0)
#else
#define dbgInit(name)
#define dbg
#endif

#ifdef __cplusplus
}
#endif
#endif
