#include "libft.h"
#include "ft_nm.h"

int		get_sym(t_64sym *sym, t_64elf elf)
{
	int			len;

	len = (elf.size - elf.ehdr.e_shoff) / sizeof(Elf64_Shdr);
	for (int i = 0; i < len; i++)
	{
		if (elf.shdr[i].sh_type == SHT_SYMTAB)
		{
			sym->sym = (Elf64_Sym*)(elf.ptr + elf.shdr[i].sh_offset);
			sym->size = elf.shdr[i].sh_size / sizeof(Elf64_Sym);
			sym->str = elf.ptr + elf.shdr[elf.shdr[i].sh_link].sh_offset;
			return (1);
		}
	}
	return (0);
}

t_symbol	*filter_64sym(t_64elf elf, t_64sym sym)
{
	char		*str;
	int			ttype;
	t_symbol	*symbol;

	str = elf.ptr + elf.shdr[elf.ehdr.e_shstrndx].sh_offset;
	symbol = ft_memalloc(sizeof(t_symbol) * (sym.size + 1));
	for (int y = 0; y < sym.size; y++)
	{
		ttype = ELF64_ST_TYPE(sym.sym[y].st_info);
		if (ttype == STT_FUNC || ttype == STT_OBJECT || ttype == STT_NOTYPE)
			addsym(symbol, sym.str + sym.sym[y].st_name, symbol64(str, sym.sym[y], elf.shdr), sym.sym[y].st_value);
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

	ft_memcpy(&elf.ehdr, ptr, sizeof(Elf64_Ehdr));
	ft_memcpy(&elf.phdr, ptr + elf.ehdr.e_phoff, sizeof(Elf64_Phdr));
	elf.shdr = (Elf64_Shdr*)(ptr + elf.ehdr.e_shoff);
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
