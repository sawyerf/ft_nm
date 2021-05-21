#include <ar.h>

#include "libft.h"
#include "ft_nm.h"

void	arch(char *ptr, struct stat st)
{
	struct ar_hdr	arc;
	int				class;

	(void)st;
	ft_memcpy(&arc, ptr + SARMAG, sizeof(arc));
	ptr += SARMAG + sizeof(arc) + ft_atoi(arc.ar_size);
	for (int i; i < 10; i++)
	{
		ft_memcpy(&arc, ptr, sizeof(arc));
		ptr += sizeof(arc);
		class = c32or64(ptr);
		if (class == ELF32)
		{
			elf32(ptr, st);
		printf("32\n");
		}
		else if (class == ELF64)
		{
			elf64(ptr, st);
		printf("64\n");
		}
		ptr += ft_atoi(arc.ar_size);
	}
}
