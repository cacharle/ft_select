#include "ft_select.h"

int main(int argc, char **argv)
{
	struct termios	saved;
	struct termios	tmp;
	t_state *state;

	tcgetattr(STDIN_FILENO, &tmp);
	saved = tmp;
	tmp.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &tmp);

	state = state_new(argc, argv);
	buf_print(state->buf, state->buf_size);

	stdin_loop(state);

	tcsetattr(STDIN_FILENO, TCSANOW, &saved);
	state_destroy(state);
	return 0;
}

