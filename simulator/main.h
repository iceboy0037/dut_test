#ifndef __MAIN_H__
#define __MAIN_H__

#define SHELL_PROMPT            	"DTU > "
#define SHELL_LINE_BUFF_LEN     	256
#define SHELL_CMD_PARAM_LEN_MAX     	16
#define SHELL_CMD_PARAM_CNT_MAX     	8
#define SHELL_CMD_SPLIT_CHAR        	' '
#define shell_printf(fmt, args...)  	do {printf(fmt, ##args); fflush(stdout);} while (0)
#define ARGV(i)             		((char *)(argv + (i) * SHELL_CMD_PARAM_LEN_MAX))
#define SHELL_VERSION           	"v1.0.0"

#define SHELL_COMMAND_SECTION       	0
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

struct cmd_tbl_s {
	char    *name;
	int 	(*cmd)(int, char *);
	char    *usage;
	char    *help;
};
#define BEGIN_COMMAND(name) struct cmd_tbl_s name##_command_array[] = {
#define ON_COMMAND(name, cmd, usage, help) {name, cmd, usage, help},
#define END_COMMAND(name)   {0, 0, 0, 0}};\
	struct cmd_tbl_s *name##_get_cmd_entry(void) {  return  name##_command_array; }\
	int name##_get_cmd_count(void) { return sizeof(name##_command_array) / sizeof(struct cmd_tbl_s) - 1;}

// Section definition
#define SHELL_COMMAND(name, cmd, usage, help)  struct cmd_tbl_s name##_shell_command_entity \
	 __attribute__((section(".shell_command_section"))) = {#name, cmd, usage, help};

#define shell_command_count()           shell_get_cmd_count_section()
extern int shell_get_cmd_count_section(void);
extern struct cmd_tbl_s *shell_get_cmd_entry_section(void);
extern struct cmd_tbl_s shell_command_array[];
extern struct cmd_tbl_s *shell_get_cmd_entry(void);
extern int shell_get_cmd_count(void);

int shell_print_args(int argc, char *argv);
void shell_task(void *param);
void shell_init(void);
int shell_cmd_help(int argc, char *argv);
int shell_cmd_quit(int argc, char *argv);
int shell_print_usage(char *name, char *detail);

#endif