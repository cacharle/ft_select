#ifndef FT_SELECT_H
# define FT_SELECT_H
#include <stdio.h>

# include <unistd.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <curses.h>
# include <term.h>
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
	char			*term_str;
	char			*underline_start_str;
	char			*underline_end_str;
	char			*reverse_start_str;
	char			*reverse_end_str;
	char			*clear_str;
	int				rows;
	int				cols;
	int				term_fd;
}					t_state;

typedef enum
{
	EKEY_EMPTY,
	EKEY_ESC,
	EKEY_UP,
	EKEY_DOWN,
	EKEY_SPACE,
	EKEY_RETURN,
	EKEY_BACKSPACE,
	EKEY_DELETE,
}					t_key;

/*
** buf.c
*/

t_buf	buf_new(char **args, int size);

/*
** state.c
*/

int		state_init(t_state *state, int argc, char **argv);
void	state_quit(t_state *state);
void	state_print(t_state *state);
void	state_print_selected(t_state *state);
void	state_erase(t_state *state);

/*
** stdin.c
*/

void	stdin_loop(t_state *state);

/*
** term.c
*/

int		term_init(struct termios *term_saved);
int		term_quit(struct termios *term_saved);

#endif
