#include <ar.h>

#include "libft.h"
#include "ft_nm.h"

void	filename(char *name, char *funcs, int err)
{
	char	*cpy;
	int		i;

	i = 0;
	while (name[i] != '/')
		i++;
	if (!i && funcs)
		filename(funcs + ft_atoi(name + 1), NULL, err);
	else if (i)
	{
		cpy = ft_fstrndup(name, i);
		if (!err)
			printf("\n%s:\n", cpy);
		else
			dprintf(2, "ft_nm: %s: file truncated\n", cpy);
		free(cpy);
	}
}

void	arch(char *ptr, size_t size)
{
	struct ar_hdr	arc;
	int				class;
	char			*func;

	ft_memcpy(&arc, ptr + SARMAG, sizeof(arc));
	ptr += SARMAG;
	size -= SARMAG;
	func = NULL;
	while (size >= sizeof(arc))
	{
		ft_memcpy(&arc, ptr, sizeof(arc));
		ptr += sizeof(arc);
		if (size < ft_atoi(arc.ar_size) + sizeof(arc))
		{
			filename(arc.ar_name, func, 1);
			return ;
		}
		size -= ft_atoi(arc.ar_size) + sizeof(arc);
		class = amagic(ptr, ft_atoi(arc.ar_size));
		if (class == ELF32 || class == ELF64)
			filename(arc.ar_name, func, 0);
		if (class == ELF32)
			elf32(ptr, ft_atoi(arc.ar_size), "");
		else if (class == ELF64)
			elf64(ptr, ft_atoi(arc.ar_size), "");
		else if (!func && !ft_strncmp("//              ", arc.ar_name, 16))
			func = ptr;
		ptr += ft_atoi(arc.ar_size);
	}
}
