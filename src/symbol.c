#include "libft.h"
#include "ft_nm.h"

char	symbol64(char *str, Elf64_Sym sym, Elf64_Shdr *shdr)
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
	else if (!ft_strncmp(".bss", str + shdr[sym.st_shndx].sh_name, 4))
		c = 'B';
	else if (!ft_strcmp(".rodata", str + shdr[sym.st_shndx].sh_name) ||
		!ft_strncmp(".eh_frame", str + shdr[sym.st_shndx].sh_name, 8))
		c = 'R';
	else if (!ft_strcmp(".data", str + shdr[sym.st_shndx].sh_name) ||
		!ft_strncmp(".got", str + shdr[sym.st_shndx].sh_name, 4) ||
		!ft_strcmp(".dynamic", str + shdr[sym.st_shndx].sh_name))
		c = 'D';
	else if (!ft_strcmp(".text", str + shdr[sym.st_shndx].sh_name) ||
		!ft_strncmp(".fini", str + shdr[sym.st_shndx].sh_name, 5) ||
		!ft_strncmp(".init", str + shdr[sym.st_shndx].sh_name, 5))
		c = 'T';
	else
		c = '?';
	if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && c != '?')
		c += 32;
	return c;
}

char	symbol32(char *str, Elf32_Sym sym, Elf32_Shdr *shdr)
{
	char	c;
	
	if (ELF32_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
		c = 'u';
	else if (ELF32_ST_BIND(sym.st_info) == STB_WEAK)
	{
		c = 'W';
		if (sym.st_shndx == SHN_UNDEF)
			c = 'w';
	}
	else if (ELF32_ST_BIND(sym.st_info) == STB_WEAK &&
			ELF32_ST_TYPE(sym.st_info) == STT_OBJECT)
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
	else if (!ft_strncmp(".bss", str + shdr[sym.st_shndx].sh_name, 4))
		c = 'B';
	else if (!ft_strcmp(".rodata", str + shdr[sym.st_shndx].sh_name) ||
		!ft_strncmp(".eh_frame", str + shdr[sym.st_shndx].sh_name, 8))
		c = 'R';
	else if (!ft_strcmp(".data", str + shdr[sym.st_shndx].sh_name) ||
		!ft_strncmp(".got", str + shdr[sym.st_shndx].sh_name, 4) ||
		!ft_strcmp(".dynamic", str + shdr[sym.st_shndx].sh_name))
		c = 'D';
	else if (!ft_strcmp(".text", str + shdr[sym.st_shndx].sh_name) ||
		!ft_strncmp(".fini", str + shdr[sym.st_shndx].sh_name, 5) ||
		!ft_strncmp(".init", str + shdr[sym.st_shndx].sh_name, 5))
		c = 'T';
	else
		c = '?';
	if (ELF32_ST_BIND(sym.st_info) == STB_LOCAL && c != '?')
		c += 32;
	return c;
}
