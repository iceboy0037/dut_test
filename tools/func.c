/**
 * @file func.c
 * @brief 杰me
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-22
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-22 <td>1.0     <td>rock     <td>
 * </table>
 */
#include <stdio.h>

/**
 * @brief 映射结构
 */
struct pt_map_t {
	char	*name;
	char	*type;
	void	*base;
	void	*value;
};

#define PT_MAP_START(name)				struct pt_map_t pt_map_entry_#name = {
#define	PT_ITEM(ptname, pttype, base, value)	{(ptname), \
								(pttype), \
								(void *)&base,\
								(void *)&value, \
								}
#define	PT_MAP_END(name)

struct yc_value_t {
	float	rating;		// 额定值
	float	raw;		// 原始值
	float	output;		// 原始值1次值
	int	q;		// 品质
};
struct yc_value_t yc = {1.0, 2.0, 3.0, 4};
struct pt_map_t tmp = PT_ITEM("rating", "float", yc, yc.raw);
int main(int argc, char *argv[])
{
	printf("rating base = %d, base = %d\n", &yc.rating, &yc);
	printf("name = %s, type = %s, value addr = %d, base addr = %d\n", tmp.name, tmp.type, tmp.value, tmp.base);
	return 0;
}
