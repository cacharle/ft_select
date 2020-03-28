#ifndef FT_SELECT_H
# define FT_SELECT_H
#include <stdio.h>

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <termios.h>
# include "libft_io.h"

typedef struct
{
	bool			selected;
	char			*text;
}					t_entry;

typedef t_entry*	t_buf;

typedef struct
{
	t_buf			buf;
	int				buf_size;
	int				current;
}					t_state;

/*
** buf.c
*/

t_buf	buf_new(char **args, int size);
void	buf_print(t_buf buf, int size);

/*
** state.c
*/

t_state	*state_new(int argc, char **argv);
void	state_destroy(t_state *state);

/*
** stdin.c
*/

void	stdin_loop(t_state *state);

#endif
