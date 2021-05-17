#ifndef FT_NM_H
# define FT_NM_H

#include <stdlib.h>
#include <elf.h>
#include <sys/stat.h>
#include "libft.h"
#include <stdio.h>

# define NOTELF 0
# define INVCL 1
# define ELF32 32
# define ELF64 64

typedef struct	s_64elf
{
	Elf64_Ehdr ehdr;
	Elf64_Phdr phdr;
	Elf64_Shdr *shdr;
	char		*ptr;
	size_t		size;
}				t_64elf;

typedef struct	s_32elf
{
	Elf32_Ehdr ehdr;
	Elf32_Phdr phdr;
	Elf32_Shdr *shdr;
}				t_32elf;

typedef struct	s_64sym
{
	Elf64_Sym	*sym;
	int			size;
	char		*str;
}				t_64sym;

char	symbol(char *str, Elf64_Sym sym, Elf64_Shdr *shdr);
void	elf64(char *ptr, struct stat st);

#endif
