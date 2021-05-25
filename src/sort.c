#include "libft.h"
#include "ft_nm.h"

int			sortcomp(char *s1, char *s2)
{
	int	i;
	int y;

	i = 0;
	y = 0;
	while (s1[i] && s2[y])
	{
		while (!ft_isalnum(s1[i]) && s1[i + 1])
			i++;
		while (!ft_isalnum(s2[y]) && s2[y + 1])
			y++;
		if (ft_toupper(s1[i]) != ft_toupper(s2[y]))
			return (ft_toupper(s2[y]) - ft_toupper(s1[i]));
		i++;
		y++;
	}
	if (!(ft_toupper(s1[i]) != ft_toupper(s2[y])))
		return (-1 * ft_strcmp(s1, s2));
	return (ft_toupper(s2[y]) - ft_toupper(s1[i]));
}

t_symbol	symcpy(t_symbol dst, t_symbol cpy)
{
	dst.name = cpy.name;
	dst.addr = cpy.addr;
	dst.symbol = cpy.symbol;
	return (dst);
}

t_symbol	*decal(t_symbol *sym)
{
	t_symbol	cpy0;
	t_symbol	cpy1;
	int			i;
	
	ft_memset(&cpy0, 0, sizeof(t_symbol));
	ft_memset(&cpy1, 0, sizeof(t_symbol));
	cpy0 = symcpy(cpy0, sym[0]);
	i = 0;
	while (sym[i].name)
	{
		cpy1 = symcpy(cpy1, sym[i + 1]);
		sym[i + 1] = symcpy(sym[i + 1], cpy0);
		cpy0 = symcpy(cpy0, cpy1);
		i++;
	}
	return (sym);
}

t_symbol	*addsym(t_symbol *sym, char *name, char symbol, long int addr)
{
	int		i;
	
	i = 0;
	if (!name[0])
		return sym;
	while (sym[i].name)
	{
		if (sortcomp(sym[i].name, name) < 0)
		{
			decal(sym + i);
			sym[i].name = name;
			sym[i].symbol = symbol;
			sym[i].addr = addr;
			return sym;
		}
		i++;
	}
	sym[i].name = name;
	sym[i].symbol = symbol;
	sym[i].addr = addr;
	return sym;
}
