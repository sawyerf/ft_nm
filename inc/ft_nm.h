#ifndef FT_NM_H
# define FT_NM_H

#include <stdlib.h>
#include <elf.h>
#include <sys/stat.h>
#include "libft.h"
#include <stdio.h>

# define NOTELF 0
# define INVCL 1
# define ARCH 3
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
	char		*ptr;
	size_t		size;
}				t_32elf;

typedef struct	s_64sym
{
	Elf64_Sym	*sym;
	int			size;
	char		*str;
}				t_64sym;

typedef struct	s_32sym
{
	Elf32_Sym	*sym;
	int			size;
	char		*str;
}				t_32sym;

typedef struct	s_symbol
{
	char		*name;
	char		symbol;
	long int	addr;
}				t_symbol;

char		symbol64(char *str, Elf64_Sym sym, Elf64_Shdr *shdr);
char		symbol32(char *str, Elf32_Sym sym, Elf32_Shdr *shdr);
void		elf64(char *ptr, size_t size);
void		elf32(char *ptr, size_t size);
void		arch (char *ptr, size_t size);
t_symbol	*addsym(t_symbol *sym, char *name, char symbol, long int addr);
int		c32or64(char *ptr);
void	print_elf(Elf64_Ehdr elf);
void	print_pelf(Elf64_Phdr pelf);
void	print_sym(char *all, char *sstr, Elf64_Sym sym);
void	print_oself(char *str, Elf64_Shdr shdr);

#endif
