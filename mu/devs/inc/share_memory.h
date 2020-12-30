/**
 * @file share_memory.h
 * @brief share memory zone
 * @author jiashipeng (1060728573@qq.com)
 * @version 1.0
 * @date 2020-12-16
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-16 <td>1.0     <td>jiashipeng     <td>share memory zone
 * </table>
 */
#ifndef __SHARE_MEMORY_H__
#define __SHARE_MEMORY_H__

#ifndef SIMULATOR
#ifdef M4FIRMWARE
#define OCRAM_ADDR (0x20901000)
#else
#define OCRAM_ADDR (0x901000)
#endif

#define OCRAM_SIZE (0xf000)

#define SHARE_MEM_BASE OCRAM_ADDR

/* ADC queue start */
#define ADC_QUEUE_STRUCT_ADDR SHARE_MEM_BASE
#define ADC_QUEUE_STRUCT_ADDR_OFFSET (0)
#define ADC_QUEUE_STRUCT_SIZE (64)

#define ADC_QUEUE_BUFF_ADDR (ADC_QUEUE_STRUCT_ADDR + ADC_QUEUE_STRUCT_SIZE)
#define ADC_QUEUE_BUFF_ADDR_OFFSET (ADC_QUEUE_STRUCT_ADDR_OFFSET + ADC_QUEUE_STRUCT_SIZE)
#define ADC_QUEUE_BUFF_SIZE (1024)
/* ADC queue end */

/* MSG queue start */
#define MSG_QUEUE_STRUCT_ADDR (ADC_QUEUE_BUFF_ADDR + ADC_QUEUE_BUFF_SIZE)
#define MSG_QUEUE_STRUCT_ADDR_OFFSET (ADC_QUEUE_BUFF_ADDR_OFFSET + ADC_QUEUE_BUFF_SIZE)
#define MSG_QUEUE_STRUCT_SIZE (64)

#define MSG_QUEUE_BUFF_ADDR (MSG_QUEUE_STRUCT_ADDR + MSG_QUEUE_STRUCT_SIZE)
#define MSG_QUEUE_BUFF_ADDR_OFFSET (MSG_QUEUE_STRUCT_ADDR_OFFSET + MSG_QUEUE_STRUCT_SIZE)
#define MSG_QUEUE_BUFF_SIZE (20480)
/* MSG queue end */

/* MUTEX LOCK start */
#define MUTEX_LOCK_A9_ADDR (MSG_QUEUE_BUFF_ADDR + MSG_QUEUE_BUFF_SIZE)
#define MUTEX_LOCK_A9_ADDR_OFFSET (MSG_QUEUE_BUFF_ADDR_OFFSET + MSG_QUEUE_BUFF_SIZE)
#define MUTEX_LOCK_SIZE (4)
#define MUTEX_LOCK_M4_ADDR (MUTEX_LOCK_A9_ADDR + MUTEX_LOCK_SIZE)
#define MUTEX_LOCK_M4_ADDR_OFFSET (MUTEX_LOCK_A9_ADDR_OFFSET + MUTEX_LOCK_SIZE)
/* MUTEX LOCK end */

/* DIO start */
#define DI_ADDR (MUTEX_LOCK_M4_ADDR + MUTEX_LOCK_SIZE)
#define DI_ADDR_OFFSET (MUTEX_LOCK_M4_ADDR_OFFSET + MUTEX_LOCK_SIZE)
#define DI_SIZE (384) /* 96 * 4 */
#define DO_ADDR (DI_ADDR + DI_SIZE)
#define DO_ADDR_OFFSET (DI_ADDR_OFFSET + DI_SIZE)
#define DO_SIZE (384)
/* DIO end */

/* YX start */
#define YX_ADDR (DO_ADDR + DO_SIZE)
#define YX_OFFSET (DO_ADDR_OFFSET + DO_SIZE)
#define YX_SIZE (4000)
/* YX end */

/* YC start */
#define YC_ADDR (YX_ADDR + YX_SIZE)
#define YC_OFFSET (YX_OFFSET + YX_SIZE)
#define YC_SIZE (2000)
/* YC end */

/* BHYC start */
#define BHYC_ADDR (YC_ADDR + YC_SIZE)
#define BHYC_OFFSET (YC_OFFSET + YC_SIZE)
#define BHYC_SIZE (2000)
/* BHYC end */

/* YK start */
#define YK_ADDR (BHYC_ADDR + BHYC_SIZE)
#define YK_OFFSET (BHYC_OFFSET + BHYC_SIZE)
#define YK_SIZE (160)
/* YK end */

/* YM start */
#define YM_ADDR (YK_ADDR + YK_SIZE)
#define YM_OFFSET (YK_OFFSET + YK_SIZE)
#define YM_SIZE (256)
/* YM end */

/* SET start */
#define SET_ADDR (YM_ADDR + YM_SIZE)
#define SET_OFFSET (YM_OFFSET + YM_SIZE)
#define SET_SIZE (600)
/* SET end */

/* SOE start */
#define SOE_ADDR (SET_ADDR + SET_SIZE)
#define SOE_OFFSET (SET_OFFSET + SET_SIZE)
#define SOE_SIZE (8200)
/* SOE end */

/* COS start */
#define COS_ADDR (SOE_ADDR + SOE_SIZE)
#define COS_OFFSET (SOE_OFFSET + SOE_SIZE)
#define COS_SIZE (4200)
/* COS end */

/* YCC start */
#define YCC_ADDR (COS_ADDR + COS_SIZE)
#define YCC_OFFSET (COS_OFFSET + COS_SIZE)
#define YCC_SIZE (350)
/* YCC end */

#define SHARE_MEM_END (YCC_ADDR + YCC_SIZE)

#if (SHARE_MEM_END > (OCRAM_ADDR + OCRAM_SIZE))
#error "Share memory not enough !"
#endif

#endif
#endif