
BEGIN_COMMAND(shell)
	ON_COMMAND("?", shell_cmd_help, "?", "Print all shell commands")
	ON_COMMAND("help", shell_cmd_help, "help", "Print all shell commands")
	ON_COMMAND("q", shell_cmd_quit, "q", "quit")

	ON_COMMAND("dbset", shell_cmd_dbset, "dbset", "Set Database key-value")
	ON_COMMAND("dbget", shell_cmd_dbget, "dbget", "Get Database key-value")

	ON_COMMAND("lsdi", shell_cmd_lsdi, "lsdi", "List DI status")
	ON_COMMAND("lsdo", shell_cmd_lsdo, "lsdo", "List DO status")

	ON_COMMAND("setdo", shell_cmd_setdo, "setdo", "Set DO status to 1")
	ON_COMMAND("setdi", shell_cmd_setdi, "setdi", "Set DI status to 1")
	ON_COMMAND("clrdo", shell_cmd_clrdo, "clrdo", "Clear DO status to 0")
	ON_COMMAND("clrdi", shell_cmd_clrdi, "clrdi", "Clear DI status to 0")
	ON_COMMAND("togdo", shell_cmd_togdo, "togdo", "Toggle DO status")
	ON_COMMAND("togdi", shell_cmd_togdi, "togdi", "Toggle DI status")
END_COMMAND(shell)