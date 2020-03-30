#include "ft_select.h"

static t_state	*state_update(t_state *state)
{
	struct winsize	window_size;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &window_size);
	state->rows = window_size.ws_row;
	state->cols = window_size.ws_col;
	return (state);
}

static int	open_stdin_tty(void)
{
	char	*tty_filename;

	if ((tty_filename = ttyname(STDIN_FILENO)) == NULL)
		return (-1);
	return (open(tty_filename, O_WRONLY));
}

int		state_init(t_state *state, int argc, char **argv)
{
	state->buf_size = argc - 1;
	state->current = 0;
	if ((state->buf = buf_new(argv + 1, state->buf_size)) == NULL
		|| (state->term_str = getenv("TERM")) == NULL
		|| tgetent(state->term_str, NULL) != 1
		|| (state->term_fd = open_stdin_tty()) < 0
		|| (state->underline_start_str = tgetstr("us", NULL)) == NULL
		|| (state->underline_end_str = tgetstr("ue", NULL)) == NULL
		|| (state->reverse_start_str = tgetstr("mr", NULL)) == NULL
		|| (state->reverse_end_str = tgetstr("me", NULL)) == NULL
		|| (state->clear_str = tgetstr("cl", NULL)) == NULL)
		return (-1);
	state_update(state);
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
	ft_putstr_fd(state->clear_str, state->term_fd);
	i = -1;
	while (++i < state->buf_size)
	{
		if (state->buf[i].selected)
			ft_putstr_fd(state->reverse_start_str, state->term_fd);
		if (i == state->current)
			ft_putstr_fd(state->underline_start_str, state->term_fd);
		ft_putstr_fd(state->buf[i].text, state->term_fd);
		if (i == state->current)
			ft_putstr_fd(state->underline_end_str, state->term_fd);
		if (state->buf[i].selected)
			ft_putstr_fd(state->reverse_end_str, state->term_fd);
		ft_putchar_fd('\n', state->term_fd);
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
