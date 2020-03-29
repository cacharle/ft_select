#include "ft_select.h"

int		term_init(struct termios *term_saved)
{
	struct termios	tmp;

	tcgetattr(STDIN_FILENO, &tmp);
	*term_saved = tmp;
	tmp.c_lflag &= ~(ICANON | ECHO);
	/* tmp.c_cc[VTIME] = 0; // ?hmmm */
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &tmp);
	return (0);
}

int		term_quit(struct termios *term_saved)
{
	tcsetattr(STDIN_FILENO, TCSANOW, term_saved);
	return (0);
}
