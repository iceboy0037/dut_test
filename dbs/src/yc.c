/**
 * @file yc.c
 * @brief yc
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-19
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-19 <td>1.0     <td>rock     <td>Create
 * </table>
 */

#include "dtu.h"

static struct yc_desc_t yc_desc_list[DTU_YC_LIST_MAX];	// 本机遥测描述列表

/**
 * @brief Create YC desc list from DB
 * @param  dev_id	Device ID
 * @return int		0 - success
 */
int init_desc_list(int dev_id)
{
	return 0;
}

int yc_save(struct yc_value_t *item, enum yc_id id)
{
	return 0;
}

int yc_read_item(struct yc_value_t *item, int pt_id)
{
	return 0;
}

int yc_read_list(struct yc_value_t *list, int start, int len)
{
	return 0;
}

int yc_save_all(struct yc_table_t *tbl)
{
	return 0;
}