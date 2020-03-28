#include "ft_select.h"

#define ASCII_ESC 0x1B

void	stdin_loop(t_state *state)
{
	char c;

	c = 0;
	while (read(STDIN_FILENO, &c, 1) > 0)
	{
		/* handler() */
		buf_print(state->buf, state->buf_size);
		/* ft_putchar('a'); */
		/* write(STDOUT_FILENO, "a", 1); */
	}
}
