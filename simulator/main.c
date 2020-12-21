/**
 * @file main.c
 * @brief
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-11
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-11 <td>1.0     <td>rock     <td>Modify Content
 * </table>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "devs.h"
#include "rdb.h"
#include "dio.h"
#include "dtu_yc.h"

static char line_buffer[SHELL_LINE_BUFF_LEN];
static char cmd_buffer[SHELL_CMD_PARAM_CNT_MAX][SHELL_CMD_PARAM_LEN_MAX];
void split(char *src, char separator, char *dest, int *num, int lenmax)
{
	char *tmp = dest;

	if (src == NULL || strlen(src) == 0) {
		return;
	}

	*num = 0;

	while (*src) {
		while (*src == separator) {     // find first NON space
			src++;
		}

		while (*src != separator && *src != '\0') {
			*tmp++ = *src++;    // copy to dest
		}

		*tmp = '\0';
		(*num) ++;
		dest += SHELL_CMD_PARAM_LEN_MAX;    // next param buffer
		tmp = dest;
	}
}

int shell_on_command(int argc, char *argv)
{
#if SHELL_COMMAND_SECTION
	struct cmd_tbl_s *entry = shell_get_cmd_entry_section();
	int count = shell_command_count();
#else
	int count = shell_get_cmd_count();
	struct cmd_tbl_s *entry = shell_get_cmd_entry();
#endif
	int i;

	for (i = 0; i < count; i++, entry++) {
		if (strcmp(entry->name, ARGV(0)) != 0) {
			continue;
		}

		if (argc == 1) {
			// NO param. execuate default command
			if (entry->cmd != 0) {
				return (*entry->cmd)(argc, argv);
			}

			continue;
		}

		// execute default command
		if (entry->cmd != 0) {
			return (*entry->cmd)(argc, argv);
		} else {
			shell_printf("\nUsage: %s <q7/q15/q31>\n", entry->name);
			return -1;
		}
	}

	// Comand NOT found
	shell_printf("\nInvalid commands! Print help or ? to get help!\n");
	return -1;
}

void safe_flush(FILE *fp)
{
	int ch;

	while ((ch = fgetc(fp)) != EOF && ch != '\n');
}
/**
 * @brief
 * @param 	 param 	Desc.
 */
void shell_task(void *param)
{
	int argc;

	shell_printf((char *)"\n------ DTU Simulator %s (%s %s) ------\n", SHELL_VERSION, __DATE__, __TIME__);
	while (1) {
		shell_printf(SHELL_PROMPT);
		if (scanf("%[^\n]%*c", line_buffer) == 0) {
			// read line with ENTER end, and flush input buffer
			//continue;
		}

		if (strlen(line_buffer) == 0) {
			safe_flush(stdin);
			continue;
		}

		split(line_buffer, SHELL_CMD_SPLIT_CHAR, (char *)cmd_buffer, &argc, SHELL_CMD_PARAM_LEN_MAX);

		if (argc > 0) {
			shell_on_command(argc, (char *)cmd_buffer);
		}

		memset(line_buffer, 0, SHELL_LINE_BUFF_LEN);
	}
}
/**
 * @brief
 * @param 	 argc 	Desc.
 * @param 	 argv 	Desc.
 * @return int
 */
int shell_print_args(int argc, char *argv)
{
	int i;

	shell_printf("\nargc = %d\n", argc);
	for (i = 0; i < argc; i ++) {
		shell_printf("argv[%d]: %s\n", i, ARGV(i));
	}

	return 0;
}

int shell_print_usage(char *name, char *detail)
{
	struct cmd_tbl_s *entry = shell_get_cmd_entry();
	int count = shell_get_cmd_count();
	int i;

	for (i = 0; i < count; i++, entry++) {
		if (strcmp(entry->name, name) == 0) {
			shell_printf("\nUsage:\n");
			shell_printf("\t\%-8s - %s\n", entry->name, entry->usage);

			if (detail != NULL) {
				shell_printf("%s\n", detail);
			}

			return 0;
		}
	}

	return 0;
}

int shell_cmd_help(int argc, char *argv)
{
#if SHELL_COMMAND_SECTION
	struct cmd_tbl_s *entry = shell_get_cmd_entry_section();
	int count = shell_command_count();
#else
	int count = shell_get_cmd_count();
	struct cmd_tbl_s *entry = shell_get_cmd_entry();
#endif
	int i;

	for (i = 0; i < count; i++, entry++) {
		shell_printf("%-8s - %s\n", entry->name, entry->help);
	}

	return 0;
}

int shell_cmd_hello(int argc, char *argv)
{
	shell_printf("Hello world!\n");
	return 0;
}

int shell_cmd_quit(int argc, char *argv)
{
	exit(0);
	return 0;
}

void shell_init(void)
{
}

void simulator_init(void)
{
	rdb_init();
	sim_devs_init();
}

#if SHELL_COMMAND_SECTION > 0
struct cmd_tbl_s cmd_tbl_end  __attribute__((section(".shell_command_section")))  = {0};
struct cmd_tbl_s cmd_tbl_start  __attribute__((section(".shell_command_section")))  = {0};
int shell_get_cmd_count_section(void)
{
	struct cmd_tbl_s *entry = shell_get_cmd_entry_section();
	int count = 0;

	while (entry->name != 0) {
		count++;
		entry++;
	}

	return count;
}

struct cmd_tbl_s *shell_get_cmd_entry_section(void)
{
	struct cmd_tbl_s *p = &cmd_tbl_start;
	return ++p;
}
#endif

/**
 * @brief Simulator entry point
 * @param  argc
 * @param  argv
 * @return int
 */
int main(int argc, char *argv[])
{
	for (int i = 0; i < 10; i++) {
		printf("%s\n", YC_ID(i));
	}
	simulator_init();
	shell_init();
	shell_task(NULL);
	return 0;
}