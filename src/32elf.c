#include "libft.h"
#include "ft_nm.h"

int	get_32sym(t_32sym *sym, t_32elf elf)
{
	int			len;

	len = (elf.size - swap32(elf.ehdr.e_shoff, elf.endian))
		/ sizeof(Elf32_Shdr);
	for (int i = 0; i < len; i++)
	{
		if (swap32(elf.shdr[i].sh_type, elf.endian) == SHT_SYMTAB)
		{
			sym->sym = (Elf32_Sym*)(elf.ptr
				+ swap32(elf.shdr[i].sh_offset, elf.endian));
			sym->size = swap32(elf.shdr[i].sh_size, elf.endian)
				/ sizeof(Elf32_Sym);
			sym->str = elf.ptr + swap32(elf.shdr[swap32(elf.shdr[i].sh_link,
				elf.endian)].sh_offset, elf.endian);
			return (1);
		}
	}
	return (0);
}

t_symbol	*filter_32sym(t_32elf elf, t_32sym sym)
{
	int			ttype;
	t_symbol	*symbol;

	symbol = ft_memalloc(sizeof(t_symbol) * (sym.size + 1));
	for (int y = 0; y < sym.size; y++)
	{
		ttype = ELF32_ST_TYPE(sym.sym[y].st_info);
		if (ttype == STT_FUNC || ttype == STT_OBJECT || ttype == STT_NOTYPE)
			addsym(symbol,
				sym.str + swap32(sym.sym[y].st_name, elf.endian),
				symbol32(sym.sym[y], elf.shdr, elf),
				swap32(sym.sym[y].st_value, elf.endian));
	}
	return (symbol);
}

void	print_32sym(t_symbol *symbol, char *file)
{
	if (!symbol[0].name)
	{
		dprintf(2, "ft_nm: %s: no symbols\n", file);
		return ;
	}
	for (int y = 0; symbol[y].name; y++)
	{
		if (symbol[y].symbol != 'U' && symbol[y].symbol != 'w' && symbol[y].symbol != 'v')
			printf("%08lx %c %s\n", symbol[y].addr, symbol[y].symbol, symbol[y].name);
		else
			printf("%8c %c %s\n", ' ', symbol[y].symbol, symbol[y].name);
	}
}

void	elf32(char *ptr, size_t size, char *file)
{
	t_32elf		elf;
	t_32sym		sym;
	t_symbol	*symbol;

	elf.endian = ptr[EI_DATA];
	ft_memcpy(&elf.ehdr, ptr, sizeof(Elf32_Ehdr));
	if (swap32(elf.ehdr.e_shoff, elf.endian)
		+ (swap16(elf.ehdr.e_shnum, elf.endian) * sizeof(Elf32_Shdr)) > size)
	{
		dprintf(2, "ft_nm: %s: file truncated\n", file);
		return ;
	}
	elf.shdr = (Elf32_Shdr*)(ptr + swap32(elf.ehdr.e_shoff, elf.endian));
	elf.ptr = ptr;
	elf.size = size;
	if (!get_32sym(&sym, elf))
	{
		dprintf(2, "ft_nm: %s: no symbols\n", file);
		return ;
	}
	symbol = filter_32sym(elf, sym);
	print_32sym(symbol, file);
	free(symbol);
}
