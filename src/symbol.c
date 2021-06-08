#include "libft.h"
#include "ft_nm.h"

char	symbol64b(Elf64_Sym sym, Elf64_Shdr *shdr, t_64elf elf)
{
	Elf64_Word		sh_type;
	Elf64_Xword		sh_flag;

	if (sym.st_shndx == SHN_UNDEF)
		return ('U');
	else if (sym.st_shndx == SHN_ABS)
		return ('A');
	else if (sym.st_shndx == SHN_COMMON)
		return ('C');
	sh_type = swap32(shdr[swap16(sym.st_shndx, elf.endian)].sh_type, elf.endian);
	if (sh_type == SHT_NOBITS)
		return ('B');
	sh_flag = swap64(shdr[swap16(sym.st_shndx, elf.endian)].sh_flags, elf.endian);
	if ((sh_type == SHT_PROGBITS && sh_flag == (SHF_ALLOC | SHF_MERGE))
		|| (sh_type == SHT_PROGBITS && sh_flag == (SHF_ALLOC)))
		return ('R');
	else if ((sh_type == SHT_PROGBITS && sh_flag == (SHF_ALLOC | SHF_WRITE))
		|| (sh_type == SHT_DYNAMIC))
		return ('D');
	else if ((sh_type == SHT_PROGBITS) || (sh_type == SHT_INIT_ARRAY)
		|| (sh_type == SHT_FINI_ARRAY))
		return ('T');
	else
		return ('?');
}

char	symbol64(Elf64_Sym sym, Elf64_Shdr *shdr, t_64elf elf)
{
	char			c;
	unsigned char	st_bind;
	unsigned char	st_type;

	st_bind = ELF64_ST_BIND(sym.st_info);
	st_type = ELF64_ST_TYPE(sym.st_info);
	if (st_bind == STB_GNU_UNIQUE)
		c = 'u';
	else if (st_bind == STB_WEAK && sym.st_shndx == SHN_UNDEF)
		c = 'w';
	else if (st_bind == STB_WEAK)
		c = 'W';
	else if (st_bind == STB_WEAK && st_type == STT_OBJECT)
	{
		c = 'V';
		if (sym.st_shndx == SHN_UNDEF)
			c = 'v';
	}
	else
		c = symbol64b(sym, shdr, elf);
	if (st_bind == STB_LOCAL && c != '?')
		c += 32;
	return (c);
}

char	symbol32b(Elf32_Sym sym, Elf32_Shdr *shdr, t_32elf elf)
{
	Elf32_Word		sh_type;
	Elf32_Word		sh_flag;

	if (sym.st_shndx == SHN_UNDEF)
		return ('U');
	else if (sym.st_shndx == SHN_ABS)
		return ('A');
	else if (sym.st_shndx == SHN_COMMON)
		return ('C');
	sh_type = swap32(shdr[swap16(sym.st_shndx, elf.endian)].sh_type,  elf.endian);
	if (sh_type == SHT_NOBITS)
		return ('B');
	sh_flag = swap32(shdr[swap16(sym.st_shndx, elf.endian)].sh_flags, elf.endian);
	if ((sh_type == SHT_PROGBITS && sh_flag == (SHF_ALLOC | SHF_MERGE))
		|| (sh_type == SHT_PROGBITS && sh_flag == (SHF_ALLOC)))
		return ('R');
	else if ((sh_type == SHT_PROGBITS && sh_flag == (SHF_ALLOC | SHF_WRITE))
		|| (sh_type == SHT_DYNAMIC))
		return ('D');
	else if ((sh_type == SHT_PROGBITS) || (sh_type == SHT_INIT_ARRAY)
		|| (sh_type == SHT_FINI_ARRAY))
		return ('T');
	else
		return ('?');
}

char	symbol32(Elf32_Sym sym, Elf32_Shdr *shdr, t_32elf elf)
{
	char			c;
	unsigned char	st_bind;
	unsigned char	st_type;

	st_bind = ELF32_ST_BIND(sym.st_info);
	st_type = ELF32_ST_TYPE(sym.st_info);
	if (st_bind == STB_GNU_UNIQUE)
		c = 'u';
	else if (st_bind == STB_WEAK && st_type == STT_OBJECT)
	{
		c = 'V';
		if (sym.st_shndx == SHN_UNDEF)
			c = 'v';
	}
	else if (st_bind == STB_WEAK && sym.st_shndx == SHN_UNDEF)
		c = 'w';
	else if (st_bind == STB_WEAK)
		c = 'W';
	else
		c = symbol32b(sym, shdr, elf);
	if (st_bind == STB_LOCAL && c != '?')
		c += 32;
	return (c);
}
