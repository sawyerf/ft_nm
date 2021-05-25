#include "libft.h"
#include "ft_nm.h"

void	get_sym(t_64sym *sym, t_64elf elf)
{
	int			len;

	sym->str = elf.ptr + elf.shdr[elf.ehdr.e_shstrndx - 1].sh_offset;
	len = (elf.size - elf.ehdr.e_shoff) / sizeof(Elf64_Shdr);
	for (int i = 0; i < len; i++)
	{
		if (elf.shdr[i].sh_type == SHT_SYMTAB)
		{
			sym->sym = (Elf64_Sym*)(elf.ptr + elf.shdr[i].sh_offset);
			sym->size = elf.shdr[i].sh_size / sizeof(Elf64_Sym);
			return ;
		}
	}
}

void	print_64osym(t_symbol symbol)
{
	if (symbol.symbol != 'U' && symbol.symbol != 'w' && symbol.symbol != 'v')
		printf("%016lx %c %s\n", symbol.addr, symbol.symbol, symbol.name);
	else
		printf("%16c %c %s\n", ' ', symbol.symbol, symbol.name);
}

void	print_64sym(t_64elf elf, t_64sym sym)
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
	if (!symbol[0].name)
		return ;
	for (int y = 0; symbol[y].name; y++)
		print_64osym(symbol[y]);
}

void	elf64(char *ptr, size_t size)
{
	t_64elf	elf;
	t_64sym	sym;

	ft_memcpy(&elf.ehdr, ptr, sizeof(Elf64_Ehdr));
	if (!elf.ehdr.e_phoff)
		ft_memcpy(&elf.phdr, ptr + elf.ehdr.e_phoff, sizeof(Elf64_Phdr));
	elf.shdr = (Elf64_Shdr*)(ptr + elf.ehdr.e_shoff);
	elf.ptr = ptr;
	elf.size = size;
	get_sym(&sym, elf);
	print_64sym(elf, sym);
}
