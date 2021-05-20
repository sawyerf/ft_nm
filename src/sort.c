typedef struct	s_symbol
{
	char		*name;
	char		symbol;
	long int	addr;
}				t_symbol;

int			sortcomp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s2 - *s1);
	}
	return (*s2 - *s1);
}

t_symbol	*decal(t_symbol *sym)
{
	t_symbol	cpy;
	int			i;
	
	i = 0;
	while (sym[i])
	{
		memcpy(sym[i], cpy, typedef(
		i++;
	}
}
t_symbol	*addsym(t_symbol *sym, char *name, char symbol, long int addr)
{
	int		i;
	
	while (sym[i])
	{
		if (sortcomp(sym[i], name) == -1)
		{
			
		}
		i++;
	}
	return sym;
}
