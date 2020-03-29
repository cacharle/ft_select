#include "ft_select.h"

int main(int argc, char **argv)
{
	t_state			state;
	struct termios	term_saved;

	if (!isatty(STDIN_FILENO))
	{
		ft_putendl_fd("Error: stdin must be a tty", STDERR_FILENO);
		return (1);
	}
	if (argc < 2)
	{
		ft_putstr("Usage: ");
		ft_putstr(argv[0]);
		ft_putendl(" options...");
		return (1);
	}
	state_init(&state, argc, argv);
	term_init(&term_saved);
	state_print(&state);
	stdin_loop(&state);
	term_quit(&term_saved);
	state_quit(&state);
	return 0;
}

