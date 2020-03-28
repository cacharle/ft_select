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

void	buf_print(t_buf buf, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_putchar('[');
		ft_putchar(buf[i].selected ? 'x' : ' ');
		ft_putchar(']');
		ft_putchar(' ');
		ft_putendl(buf[i].text);
		i++;
	}
}
