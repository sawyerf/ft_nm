#ifndef FT_NM_H
# define FT_NM_H

# include <stdlib.h>
# include <elf.h>
# include <sys/stat.h>
# include "libft.h"
# include <stdio.h>

# define INVCL	-2
# define NOTELF	-1
# define ISERR	0
# define ARCH	3
# define ELF32	32
# define ELF64	64

typedef struct s_64elf
{
	Elf64_Ehdr	ehdr;
	Elf64_Phdr	phdr;
	Elf64_Shdr	*shdr;
	char		*ptr;
	size_t		size;
	char		endian;
}				t_64elf;

typedef struct s_32elf
{
	Elf32_Ehdr	ehdr;
	Elf32_Phdr	phdr;
	Elf32_Shdr	*shdr;
	char		*ptr;
	size_t		size;
	char		endian;
}				t_32elf;

typedef struct s_64sym
{
	Elf64_Sym	*sym;
	int			size;
	char		*str;
}				t_64sym;

typedef struct s_32sym
{
	Elf32_Sym	*sym;
	int			size;
	char		*str;
}				t_32sym;

typedef struct s_symbol
{
	char		*name;
	char		symbol;
	long int	addr;
}				t_symbol;

char			symbol64(Elf64_Sym sym, Elf64_Shdr *shdr, t_64elf elf);
char			symbol32(Elf32_Sym sym, Elf32_Shdr *shdr, t_32elf elf);
void			elf64(char *ptr, size_t size, char *file);
void			elf32(char *ptr, size_t size, char *file);
void			arch (char *ptr, size_t size);
t_symbol		*addsym(t_symbol *sym, char *name, char symbol, long int addr);
int				amagic(char *ptr, size_t size);
uint64_t		swap64(uint64_t nbr, char endian);
uint32_t		swap32(uint32_t nbr, char endian);
uint16_t		swap16(uint16_t nbr, char endian);

#endif
