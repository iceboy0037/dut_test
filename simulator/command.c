/**
 * @file command.c
 * @brief Shell command implementation 
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-13
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-13 <td>1.0     <td>rock     <td>Modify Content
 * </table>
 */
#include "simulator.h"
#include "main.h"
#include "devs.h"

int shell_cmd_lsdi(int argc, char *argv)
{
	int i;

	printf("----------------DI Status----------------\n");
	printf("Seq\tStatus\n");
	for (i = 0; i < sim_di.count; i++) {
		printf("%d\t%d\n", i, sim_di.buf[i]);
	}
	printf("\n");

	return 0;
}
int shell_cmd_lsdo(int argc, char *argv)
{
	int i;

	printf("----------------DO Status----------------\n");
	printf("Seq\tStatus\n");
	for (i = 0; i < sim_do.count; i++) {
		printf("%d\t%d\n", i, sim_do.buf[i]);
	}
	printf("\n");

	return 0;
}
int shell_cmd_setdo(int argc, char *argv)
{
	return 0;
}
int shell_cmd_setdi(int argc, char *argv)
{
	return 0;
}
int shell_cmd_clrdo(int argc, char *argv)
{
	return 0;
}
int shell_cmd_clrdi(int argc, char *argv)
{
	return 0;
}
int shell_cmd_togdo(int argc, char *argv)
{
	return 0;
}
int shell_cmd_togdi(int argc, char *argv)
{
	return 0;
}
#include "command.inc"