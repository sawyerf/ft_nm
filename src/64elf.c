#include "libft.h"
#include "ft_nm.h"

int		get_sym(t_64sym *sym, t_64elf elf)
{
	int			len;

	len = (elf.size - swap64(elf.ehdr.e_shoff, elf.endian)) / sizeof(Elf64_Shdr);
	for (int i = 0; i < len; i++)
	{
		if (swap64(elf.shdr[i].sh_type, elf.endian) == SHT_SYMTAB)
		{
			sym->sym = (Elf64_Sym*)(elf.ptr + swap64(elf.shdr[i].sh_offset, elf.endian));
			sym->size = swap64(elf.shdr[i].sh_size, elf.endian) / sizeof(Elf64_Sym);
			sym->str = elf.ptr + swap64(elf.shdr[swap32(elf.shdr[i].sh_link, elf.endian)].sh_offset, elf.endian);
			return (1);
		}
	}
	return (0);
}

t_symbol	*filter_64sym(t_64elf elf, t_64sym sym)
{
	int			ttype;
	t_symbol	*symbol;

	symbol = ft_memalloc(sizeof(t_symbol) * (sym.size + 1));
	for (int y = 0; y < sym.size; y++)
	{
		ttype = ELF64_ST_TYPE(sym.sym[y].st_info);
		if (ttype == STT_FUNC || ttype == STT_OBJECT || ttype == STT_NOTYPE)
			addsym(symbol, sym.str + swap32(sym.sym[y].st_name, elf.endian),
				symbol64(sym.sym[y], elf.shdr, elf),
				swap64(sym.sym[y].st_value, elf.endian));
	}
	return (symbol);
}

void	print_64sym(t_symbol *symbol, char *file)
{
	if (!symbol[0].name)
	{
		dprintf(2, "ft_nm: %s: aucun symbole\n", file);
		return ;
	}
	for (int y = 0; symbol[y].name; y++)
	{
		if (symbol[y].symbol != 'U' && symbol[y].symbol != 'w' && symbol[y].symbol != 'v')
			printf("%016lx %c %s\n", symbol[y].addr, symbol[y].symbol, symbol[y].name);
		else
			printf("%16c %c %s\n", ' ', symbol[y].symbol, symbol[y].name);
	}
}

void	elf64(char *ptr, size_t size, char *file)
{
	t_64elf		elf;
	t_64sym		sym;
	t_symbol	*symbol;

	elf.endian = ptr[EI_DATA];
	ft_memcpy(&elf.ehdr, ptr, sizeof(Elf64_Ehdr));
	if (swap32(elf.ehdr.e_phoff, elf.endian) > size ||
		swap64(elf.ehdr.e_shoff, elf.endian) + (swap16(elf.ehdr.e_shnum, elf.endian) * sizeof(Elf64_Shdr)) > size)
	{
		dprintf(2, "ft_nm: %s: file truncated\n", file);
		return ;
	}
	ft_memcpy(&elf.phdr, ptr + swap64(elf.ehdr.e_phoff, elf.endian), sizeof(Elf64_Phdr));
	elf.shdr = (Elf64_Shdr*)(ptr + swap64(elf.ehdr.e_shoff, elf.endian));
	elf.ptr = ptr;
	elf.size = size;
	if (!get_sym(&sym, elf))
	{
		dprintf(2, "ft_nm: %s: aucun symbole\n", file);
		return ;
	}
	symbol = filter_64sym(elf, sym);
	print_64sym(symbol, file);
	free(symbol);
}
