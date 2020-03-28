#include "ft_select.h"

t_state	*state_new(int argc, char **argv)
{
	t_state	*state;

	if ((state = malloc(sizeof(t_state))) == NULL)
		return (NULL);
	state->buf_size = argc - 1;
	if ((state->buf = buf_new(argv + 1, state->buf_size)) == NULL)
	{
		state_destroy(state);
		return (NULL);
	}
	state->current = 0;
	return (state);
}

void	state_destroy(t_state *state)
{
	if (state == NULL)
		return ;
	free(state->buf);
	free(state);
}
