//#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>
#include "libft.h"


typedef struct	s_elf
{
	Elf64_Ehdr ehdr;
	Elf64_Phdr phdr;

}				t_elf;

char	symbol(char *str, Elf64_Sym sym, Elf64_Shdr *shdr)
{
	char	c;
	
	if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
		c = 'u';
	else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK)
	{
		c = 'W';
		if (sym.st_shndx == SHN_UNDEF)
			c = 'w';
	}
	else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK &&
			ELF64_ST_TYPE(sym.st_info) == STT_OBJECT)
	{
		c = 'V';
		if (sym.st_shndx == SHN_UNDEF)
			c = 'v';
	}
	else if (sym.st_shndx == SHN_UNDEF)
		c = 'U';
	else if (sym.st_shndx == SHN_ABS)
		c = 'A';
	else if (sym.st_shndx == SHN_COMMON)
		c = 'C';
	else if (!ft_strcmp(".bss", str + shdr[sym.st_shndx].sh_name))
		c = 'B';
	else if (!ft_strcmp(".rodata", str + shdr[sym.st_shndx].sh_name) ||
		!ft_strcmp(".eh_frame_hdr", str + shdr[sym.st_shndx].sh_name) ||
		!ft_strcmp(".eh_frame", str + shdr[sym.st_shndx].sh_name))
		c = 'R';
	else if (!ft_strcmp(".data", str + shdr[sym.st_shndx].sh_name) ||
		!ft_strcmp(".got", str + shdr[sym.st_shndx].sh_name) ||
		!ft_strcmp(".dynamic", str + shdr[sym.st_shndx].sh_name))
		c = 'D';
	else if (!ft_strcmp(".text", str + shdr[sym.st_shndx].sh_name) ||
		!ft_strcmp(".fini_array", str + shdr[sym.st_shndx].sh_name) ||
		!ft_strcmp(".fini", str + shdr[sym.st_shndx].sh_name) ||
		!ft_strcmp(".init", str + shdr[sym.st_shndx].sh_name) ||
		!ft_strcmp(".init_array", str + shdr[sym.st_shndx].sh_name))
		c = 'T';
	else
	{
		c = '?';
		printf("name        : %s\n",    str + shdr[sym.st_shndx].sh_name);
	}
	if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && c != '?')
		c += 32;
	return c;
}
void	print_self(char *all, t_elf elf, Elf64_Shdr *shdr, int len)
{
	char		*str;
	char		*sstr;
	Elf64_Sym	*sym;
	int			len_sym;

	str = all + shdr[elf.ehdr.e_shstrndx].sh_offset;
	sstr = all + shdr[elf.ehdr.e_shstrndx - 1].sh_offset;
	for (int i = 0; i < len; i++)
	{
		if (shdr[i].sh_type == 2)
		{
			sym = (Elf64_Sym*)(all + shdr[i].sh_offset);
			len_sym = shdr[i].sh_size / sizeof(Elf64_Sym);
		}
	}
	int ttype;
	for (int y = 0; y < len_sym; y++)
	{
		ttype = ELF64_ST_TYPE(sym[y].st_info);
		if (ttype != 4 && ttype != 3)
		{
			if (sym[y].st_value)
				printf("%.16lx %c %s\n", sym[y].st_value, symbol(str, sym[y], shdr), sstr + sym[y].st_name);
			else
				printf("%16c %c %s\n", ' ', symbol(str, sym[y], shdr), sstr + sym[y].st_name);
		}
	}
}

int main(int argi, char **argv)
{
	int fd;
	struct stat st;
	t_elf		elf;
	(void)argi;

	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return 1;
	if (fstat(fd, &st) < 0)
		return 1;
	char	 all[st.st_size + 1];
	read(fd, &elf, sizeof(t_elf));
	read(fd, all + sizeof(elf), st.st_size - sizeof(elf));
	print_self(all, elf, (Elf64_Shdr*)(all + elf.ehdr.e_shoff), (st.st_size - elf.ehdr.e_shoff) / sizeof(Elf64_Shdr));
}
