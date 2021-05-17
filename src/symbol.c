#include "libft.h"
#include "ft_nm.h"

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
