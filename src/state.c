#include "ft_select.h"

static t_state	*state_update(t_state *state)
{
	struct winsize	window_size;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &window_size);
	state->rows = window_size.ws_row;
	state->cols = window_size.ws_col;
	return (state);
}

int		state_init(t_state *state, int argc, char **argv)
{
	state->buf_size = argc - 1;
	if ((state->buf = buf_new(argv + 1, state->buf_size)) == NULL)
		return (-1);
	if ((state->term_str = getenv("TERM")) == NULL)
		return (-1);
	tgetent(state->term_str, NULL);
	state_update(state);
	state->underline_start_str = tgetstr("us", NULL);
	state->underline_end_str = tgetstr("ue", NULL);
	state->reverse_start_str = tgetstr("mr", NULL);
	state->reverse_end_str = tgetstr("me", NULL);
	state->clear_str = tgetstr("cl", NULL);
	state->current = 0;
	return (0);
}

void	state_quit(t_state *state)
{
	if (state == NULL)
		return ;
	free(state->buf);
}

void	state_print(t_state *state)
{
	int	i;

	state_update(state);
	/* ft_putstr(state->clear_str); */
	i = -1;
	while (++i < state->buf_size)
	{
		if (state->buf[i].selected)
			ft_putstr(state->reverse_start_str);
		if (i == state->current)
			ft_putstr(state->underline_start_str);
		ft_putstr(state->buf[i].text);
		if (i == state->current)
			ft_putstr(state->underline_end_str);
		if (state->buf[i].selected)
			ft_putstr(state->reverse_end_str);
		ft_putchar('\n');
	}
}

void	state_print_selected(t_state *state)
{
	int	i;

	i = -1;
	while (++i < state->buf_size)
	{
		if (state->buf[i].selected)
			ft_putstr(state->buf[i].text);
		if (i != state->buf_size - 1)
			ft_putchar(' ');
	}
}

void	state_erase(t_state *state)
{
	if (state->buf_size < 1)
		return ;
	ft_memmove(state->buf + state->current,
				state->buf + state->current + 1,
				state->buf_size - state->current - 1);
	state->buf_size--;
}
