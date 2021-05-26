#include "libft.h"
#include "ft_nm.h"

void	get_32sym(t_32sym *sym, t_32elf elf)
{
	int			len;

	len = (elf.size - elf.ehdr.e_shoff) / sizeof(Elf32_Shdr);
	for (int i = 0; i < len; i++)
	{
		if (elf.shdr[i].sh_type == SHT_SYMTAB)
		{
			sym->sym = (Elf32_Sym*)(elf.ptr + elf.shdr[i].sh_offset);
			sym->size = elf.shdr[i].sh_size / sizeof(Elf32_Sym);
			sym->str = elf.ptr + elf.shdr[elf.shdr[i].sh_link].sh_offset;
			return ;
		}
	}
}

void	print_32osym(t_symbol symbol)
{
	if (symbol.symbol != 'U' && symbol.symbol != 'w' && symbol.symbol != 'v')
		printf("%08lx %c %s\n", symbol.addr, symbol.symbol, symbol.name);
	else
		printf("%8c %c %s\n", ' ', symbol.symbol, symbol.name);
}

void	print_32sym(t_32elf elf, t_32sym sym)
{
	char		*str;
	int			ttype;
	t_symbol	*symbol;

	symbol = ft_memalloc(sizeof(t_symbol) * (sym.size + 1));
	str = elf.ptr + elf.shdr[elf.ehdr.e_shstrndx].sh_offset;
	for (int y = 0; y < sym.size; y++)
	{
		ttype = ELF32_ST_TYPE(sym.sym[y].st_info);
		if (ttype == STT_FUNC || ttype == STT_OBJECT || ttype == STT_NOTYPE)
			addsym(symbol, sym.str + sym.sym[y].st_name, symbol32(str, sym.sym[y], elf.shdr), sym.sym[y].st_value);
	}
	if (!symbol[0].name)
		return ;
	for (int y = 0; symbol[y].name; y++)
		print_32osym(symbol[y]);
}

void	elf32(char *ptr, size_t size)
{
	t_32elf	elf;
	t_32sym	sym;

	ft_memcpy(&elf.ehdr, ptr, sizeof(Elf32_Ehdr));
	ft_printf("%b\n", elf.ehdr.e_phoff);
	printf("%ld\n", size);
 	ft_memcpy(&elf.phdr, ptr + elf.ehdr.e_phoff, sizeof(Elf32_Phdr));
	elf.shdr = (Elf32_Shdr*)(ptr + elf.ehdr.e_shoff);
	elf.ptr = ptr;
	elf.size = size;
	get_32sym(&sym, elf);
	print_32sym(elf, sym);
}
