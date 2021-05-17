#include "libft.h"
#include "ft_nm.h"

void	get_sym(t_64sym *sym, t_64elf elf)
{
	int			len;

	sym->str = elf.ptr + elf.shdr[elf.ehdr.e_shstrndx - 1].sh_offset;
	len = (elf.size - elf.ehdr.e_shoff) / sizeof(Elf64_Shdr);
	for (int i = 0; i < len; i++)
	{
		if (elf.shdr[i].sh_type == 2)
		{
			sym->sym = (Elf64_Sym*)(elf.ptr + elf.shdr[i].sh_offset);
			sym->size = elf.shdr[i].sh_size / sizeof(Elf64_Sym);
		}
	}
}

void	print_self(t_64elf elf, t_64sym sym)
{
	char		*str;
	int			ttype;

	str = elf.ptr + elf.shdr[elf.ehdr.e_shstrndx].sh_offset;
	for (int y = 0; y < sym.size; y++)
	{
		ttype = ELF64_ST_TYPE(sym.sym[y].st_info);
		if (ttype != 4 && ttype != 3)
		{
			if (sym.sym[y].st_value)
				printf("%.16lx %c %s\n", sym.sym[y].st_value, symbol(str, sym.sym[y], elf.shdr), sym.str + sym.sym[y].st_name);
			else
				printf("%16c %c %s\n", ' ', symbol(str, sym.sym[y], elf.shdr), sym.str + sym.sym[y].st_name);
		}
	}
}

void	elf64(char *ptr, struct stat st)
{
	t_64elf	elf;
	t_64sym	sym;

	ft_memcpy(&elf.ehdr, ptr, sizeof(Elf64_Ehdr));
	ft_memcpy(&elf.phdr, ptr + elf.ehdr.e_phoff, sizeof(Elf64_Phdr));
	elf.shdr = (Elf64_Shdr*)(ptr + elf.ehdr.e_shoff);
	elf.ptr = ptr;
	elf.size = st.st_size;
	get_sym(&sym, elf);
	print_self(elf, sym);
}

