
BEGIN_COMMAND(shell)
	ON_COMMAND("?", shell_cmd_help, "?", "Print all shell commands")
	ON_COMMAND("help", shell_cmd_help, "help", "Print all shell commands")
	ON_COMMAND("q", shell_cmd_quit, "q", "quit")
	ON_COMMAND("time", shell_cmd_time, "time", "Print current time stamp")

	ON_COMMAND("dbset", shell_cmd_dbset, "dbset", "Set Database key-value")
	ON_COMMAND("dbget", shell_cmd_dbget, "dbget", "Get Database key-value")

	ON_COMMAND("yxset", shell_cmd_yxset, "yxset", "Set YX value")


	ON_COMMAND("lsdi", shell_cmd_lsdi, "lsdi", "List DI status")
	ON_COMMAND("lsdo", shell_cmd_lsdo, "lsdo", "List DO status")
	ON_COMMAND("lsyc", shell_cmd_lsyc, "lsyc", "List all YC in RDB")
	ON_COMMAND("lsyx", shell_cmd_lsyx, "lsyx", "List all YX in RDB")


	ON_COMMAND("setdo", shell_cmd_setdo, "setdo", "Set DO status to 1")
	ON_COMMAND("setdi", shell_cmd_setdi, "setdi", "Set DI status to 1")
	ON_COMMAND("clrdo", shell_cmd_clrdo, "clrdo", "Clear DO status to 0")
	ON_COMMAND("clrdi", shell_cmd_clrdi, "clrdi", "Clear DI status to 0")
	ON_COMMAND("togdo", shell_cmd_togdo, "togdo", "Toggle DO status")
	ON_COMMAND("togdi", shell_cmd_togdi, "togdi", "Toggle DI status")
	ON_COMMAND("saveyc", shell_cmd_saveyc, "saveyc", "Save YC table to RDB")
	ON_COMMAND("readyc", shell_cmd_readyc, "readyc", "Read YC from RDB")
END_COMMAND(shell)