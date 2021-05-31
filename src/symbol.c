#include "libft.h"
#include "ft_nm.h"

char	symbol64(char *str, Elf64_Sym sym, Elf64_Shdr *shdr)
{
	char			c;
	Elf64_Word		sh_type;
	Elf64_Xword		sh_flag;
	unsigned char	st_bind;
	unsigned char	st_type;
	int		bind;
	
	(void)str;
	sh_type = shdr[sym.st_shndx].sh_type;
	sh_flag = shdr[sym.st_shndx].sh_flags;
	st_bind = ELF64_ST_BIND(sym.st_info);
	st_type = ELF64_ST_TYPE(sym.st_info);
	if (st_bind == STB_GNU_UNIQUE)
		c = 'u';
	else if (st_bind == STB_WEAK)
	{
		c = 'W';
		if (sym.st_shndx == SHN_UNDEF)
			c = 'w';
	}
	else if (st_bind == STB_WEAK &&
			st_type == STT_OBJECT)
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
	else if (sh_type == SHT_NOBITS)
		c = 'B';
	else if (sh_type == SHT_PROGBITS && sh_flag == (SHF_ALLOC | SHF_MERGE))
		c = 'R';
	else if (sh_type == SHT_PROGBITS && sh_flag == (SHF_ALLOC))
		c = 'R';
	else if (sh_type == SHT_PROGBITS && sh_flag == (SHF_ALLOC | SHF_WRITE))
		c = 'D';
	else if (sh_type == SHT_PROGBITS)
		c = 'T';
	else if (sh_type == SHT_INIT_ARRAY)
		c = 'T';
	else if (sh_type == SHT_FINI_ARRAY)
		c = 'T';
	else if (sh_type == SHT_DYNAMIC)
		c = 'D';
	else
		c = '?';
	if (st_bind == STB_LOCAL && c != '?')
		c += 32;
	return c;
}

char	symbol32(char *str, Elf32_Sym sym, Elf32_Shdr *shdr)
{
	char	c;
	Elf32_Word		sh_type;
	Elf32_Word		sh_flag;
	unsigned char	st_bind;
	unsigned char	st_type;
	
	(void)str;
	sh_type = shdr[sym.st_shndx].sh_type;
	st_bind = ELF32_ST_BIND(sym.st_info);
	st_type = ELF32_ST_TYPE(sym.st_info);
	sh_flag = shdr[sym.st_shndx].sh_flags;
	if (st_bind == STB_GNU_UNIQUE)
		c = 'u';
	else if (st_bind == STB_WEAK &&
			st_type == STT_OBJECT)
	{
		c = 'V';
		if (sym.st_shndx == SHN_UNDEF)
			c = 'v';
	}
	else if (st_bind == STB_WEAK)
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
	else if (sh_type == SHT_NOBITS)
		c = 'B';
	else if (sh_type == SHT_PROGBITS && sh_flag == (SHF_ALLOC | SHF_MERGE))
		c = 'R';
	else if (sh_type == SHT_PROGBITS && sh_flag == (SHF_ALLOC))
		c = 'R';
	else if (sh_type == SHT_PROGBITS && sh_flag == (SHF_ALLOC | SHF_WRITE))
		c = 'D';
	else if (sh_type == SHT_PROGBITS)
		c = 'T';
	else if (sh_type == SHT_INIT_ARRAY)
		c = 'T';
	else if (sh_type == SHT_FINI_ARRAY)
		c = 'T';
	else if (sh_type == SHT_DYNAMIC)
		c = 'D';
	else
		c = '?';
	if (st_bind == STB_LOCAL && c != '?')
		c += 32;
	return c;
}
