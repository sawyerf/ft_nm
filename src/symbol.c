#include "libft.h"
#include "ft_nm.h"

char	symbol64(char *str, Elf64_Sym sym, Elf64_Shdr *shdr)
{
	char	c;
	
	(void)str;
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
	else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS)
		c = 'B';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_MERGE))
		c = 'R';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC)) //.rodata*
		c = 'R';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE)) //.data*
		c = 'D';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS) //.text
		c = 'T';
	else if (shdr[sym.st_shndx].sh_type == SHT_INIT_ARRAY) //.init_array
		c = 'T';
	else if (shdr[sym.st_shndx].sh_type == SHT_FINI_ARRAY) //.fini_array
		c = 'T';
	else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC) //.dynamic
		c = 'D';
	else
		c = '?';
	if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && c != '?')
		c += 32;
	return c;
}

char	symbol32(char *str, Elf32_Sym sym, Elf32_Shdr *shdr)
{
	char	c;
	
	(void)str;
	if (ELF32_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
		c = 'u';
	else if (ELF32_ST_BIND(sym.st_info) == STB_WEAK &&
			ELF32_ST_TYPE(sym.st_info) == STT_OBJECT)
	{
		c = 'V';
		if (sym.st_shndx == SHN_UNDEF)
			c = 'v';
	}
	else if (ELF32_ST_BIND(sym.st_info) == STB_WEAK)
	{
		c = 'W';
		if (sym.st_shndx == SHN_UNDEF)
			c = 'w';
	}
	else if (sym.st_shndx == SHN_UNDEF)
		c = 'U';
	else if (sym.st_shndx == SHN_ABS)
		c = 'A';
	else if (sym.st_shndx == SHN_COMMON)
		c = 'C';
	else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS)
		c = 'B';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_MERGE))
		c = 'R';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC))
		c = 'R';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'D';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS)
		c = 'T';
	else if (shdr[sym.st_shndx].sh_type == SHT_INIT_ARRAY)
		c = 'T';
	else if (shdr[sym.st_shndx].sh_type == SHT_FINI_ARRAY)
		c = 'T';
	else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
		c = 'D';
	else
		c = '?';
	if (ELF32_ST_BIND(sym.st_info) == STB_LOCAL && c != '?')
		c += 32;
	return c;
}
