#include "libft.h"
#include "ft_nm.h"

void	get_32sym(t_32sym *sym, t_32elf elf)
{
	int			len;

	sym->str = elf.ptr + elf.shdr[elf.ehdr.e_shstrndx - 1].sh_offset;
	len = (elf.size - elf.ehdr.e_shoff) / sizeof(Elf32_Shdr);
	for (int i = 0; i < len; i++)
	{
		if (elf.shdr[i].sh_type == 2)
		{
			sym->sym = (Elf32_Sym*)(elf.ptr + elf.shdr[i].sh_offset);
			sym->size = elf.shdr[i].sh_size / sizeof(Elf32_Sym);
		}
	}
}

void	print_32sym(t_32elf elf, t_32sym sym)
{
	char		*str;
	int			ttype;

	str = elf.ptr + elf.shdr[elf.ehdr.e_shstrndx].sh_offset;
	(void)str;
	for (int y = 0; y < sym.size; y++)
	{
		ttype = ELF32_ST_TYPE(sym.sym[y].st_info);
		if (ttype != 4 && ttype != 3)
		{
			if (sym.sym[y].st_value)
				printf("%.16x %s\n", sym.sym[y].st_value, sym.str + sym.sym[y].st_name);
			else
				printf("%16c %s\n", ' ', sym.str + sym.sym[y].st_name);
		}
	}
}

void	elf32(char *ptr, size_t size)
{
	t_32elf	elf;
	t_32sym	sym;

	ft_memcpy(&elf.ehdr, ptr, sizeof(Elf32_Ehdr));
	ft_memcpy(&elf.phdr, ptr + elf.ehdr.e_phoff, sizeof(Elf32_Phdr));
	elf.shdr = (Elf32_Shdr*)(ptr + elf.ehdr.e_shoff);
	elf.ptr = ptr;
	elf.size = size;
	get_32sym(&sym, elf);
	print_32sym(elf, sym);
}
