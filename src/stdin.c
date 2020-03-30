#include "ft_select.h"

#define KEY_BUF_SIZE 4
#define BUF_ESC       "\e\0\0\0"
#define BUF_UP        "\e[A\0"
#define BUF_DOWN      "\e[B\0"
#define BUF_SPACE     " \0\0\0"
#define BUF_RETURN    "\n\0\0\0"
#define BUF_BACKSPACE "\b\0\0\0"
#define BUF_DEL       "\x7f\0\0\0"
#define BUF_DELETE    "\e[3~"

static bool		buf_equ(char buf[KEY_BUF_SIZE], char *buf2)
{
	return (ft_memcmp(buf, buf2, KEY_BUF_SIZE) == 0);
}

static t_key	get_key(void)
{
	char buf[KEY_BUF_SIZE];

	ft_bzero(buf, KEY_BUF_SIZE);
	read(STDIN_FILENO, buf, 4);
	/* for (int i = 0; i < 4; i++) */
	/* 	printf("%2x %c\n", buf[i], buf[i] == '\e' ? '^' : buf[i]); */
	if (buf_equ(buf, BUF_ESC))
		return (EKEY_ESC);
	if (buf_equ(buf, BUF_UP))
		return (EKEY_UP);
	if (buf_equ(buf, BUF_DOWN))
		return (EKEY_DOWN);
	if (buf_equ(buf, BUF_SPACE))
		return (EKEY_SPACE);
	if (buf_equ(buf, BUF_RETURN))
		return (EKEY_RETURN);
	if (buf_equ(buf, BUF_BACKSPACE) || buf_equ(buf, BUF_DEL))
		return (EKEY_BACKSPACE);
	if (buf_equ(buf, BUF_DELETE))
		return (EKEY_DELETE);
	return (EKEY_EMPTY);
}

static bool		exec_key(t_state *state, t_key key)
{
	if (key == EKEY_EMPTY)
		return (true);
	if (key == EKEY_ESC)
		return (false);
	else if (key == EKEY_SPACE)
	{
		state->buf[state->current].selected =
			!state->buf[state->current].selected;
		state->current = (state->current + 1) % state->buf_size;
	}
	else if (key == EKEY_RETURN)
	{
		state_print_selected(state);
		return (false);
	}
	else if (key == EKEY_BACKSPACE || key == EKEY_DELETE)
	{
		if (state->buf_size < 1)
			return (false);
		state_erase(state);
	}
	else if (key == EKEY_UP)
	{
		if (state->current == 0)
			state->current = state->buf_size - 1;
		else
			state->current--;
	}
	else if (key== EKEY_DOWN)
		state->current = (state->current + 1) % state->buf_size;
	return (true);
}

void	stdin_loop(t_state *state)
{
	while (exec_key(state, get_key()))
		state_print(state);
}
