#include "ft_select.h"

t_buf	buf_new(char **args, int size)
{
	t_buf	buf;

	if ((buf = malloc(sizeof(t_entry) * size)) == NULL)
		return (NULL);
	while (size-- > 0)
	{
		buf[size].selected = false;
		buf[size].text = args[size];
	}
	return (buf);
}
