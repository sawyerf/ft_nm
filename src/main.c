//#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>
#include "libft.h"

char            symbol(Elf64_Sym sym, Elf64_Shdr *shdr)
{
  char  c;

  if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
    c = 'u';
  else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK)
    {
      c = 'W';
      if (sym.st_shndx == SHN_UNDEF)
        c = 'w';
    }
  else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK && ELF64_ST_TYPE(sym.st_info) == STT_OBJECT)
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
  else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS
       && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    c = 'B';
  else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
       && shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
    c = 'R';
  else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
       && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    c = 'D';
  else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
       && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
    c = 'T';
  else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
    c = 'D';
  else
    c = '?';
  if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && c != '?')
    c += 32;
  return c;
}

void	print_elf(Elf64_Ehdr elf)
{
	if (elf.e_ident[EI_CLASS] == ELFCLASS32)
		printf("32bit\n");
	if (elf.e_ident[EI_CLASS] == ELFCLASS64)
		printf("64bit\n");
	printf("======== Ehdr =======\n");
	printf("e_indent : %s\n", elf.e_ident);
	printf("e_indent4: %d\n", elf.e_ident[EI_CLASS]);
	printf("e_phnum  : %d\n", elf.e_phnum);
	printf("e_type   : %d\n", elf.e_type);
	printf("e_machine: %d\n", elf.e_machine);
	printf("e_version: %d\n", elf.e_version);
	printf("e_entry  : 0x%lx\n", elf.e_entry);
	printf("e_phoff  : 0x%ld\n", elf.e_phoff);
	printf("e_shoff  : 0x%ld\n", elf.e_shoff);
	printf("e_phnum  : %d\n", elf.e_phnum);
	printf("e_shstrndx: %d\n", elf.e_shstrndx);
}

void	print_pelf(Elf64_Phdr pelf)
{
	printf("======== Phdr =======\n");
	printf("p_type  : %d\n", pelf.p_type);
	printf("p_flags : %d\n", pelf.p_flags);
	printf("p_offset: %ld\n",  pelf.p_offset);
	printf("p_vaddr : 0x%lx\n", pelf.p_vaddr);
	printf("p_paddr : 0x%lx\n", pelf.p_paddr);
	printf("p_filesz: 0x%lx\n", pelf.p_filesz);
	printf("p_memsz : 0x%lx\n", pelf.p_memsz);
	printf("p_align : %ld\n", pelf.p_align);
}

typedef struct	s_elf
{
	Elf64_Ehdr ehdr;
	Elf64_Phdr phdr;

}				t_elf;

void	print_oself(char *str, Elf64_Shdr shdr)
{
	printf("======== Shdr =======\n");
	printf("name        : %s\n",    str + shdr.sh_name);
	printf("sh_type     : %d\n",    shdr.sh_type);
	printf("sh_name     : 0x%d\n",	shdr.sh_name);
	printf("sh_type     : %d\n",    shdr.sh_type);
	printf("sh_flags    : %ld\n",   shdr.sh_flags);
	printf("sh_addr     : 0x%ld\n", shdr.sh_addr);
	printf("sh_offset   : 0x%ld\n", shdr.sh_offset);
	printf("sh_size     : %ld\n",   shdr.sh_size / sizeof(Elf64_Sym));
	printf("sh_link     : 0x%d\n",  shdr.sh_link);
	printf("sh_info     : 0x%d\n",  shdr.sh_info);
	printf("sh_addralign: 0x%ld\n", shdr.sh_addralign);
	printf("sh_entsize  : 0x%ld\n", shdr.sh_entsize);
}

void	print_sym(char *all, char *sstr, Elf64_Sym sym)
{
	printf("======== ST =======\n");
	printf("nameee  : %s\n",    sstr + sym.st_name);
	printf("st_name : 0x%d\n",  sym.st_name);
	printf("st_info : %d\n", ELF64_ST_TYPE(sym.st_info));
	printf("st_other: %c\n",    sym.st_other);
	printf("st_shndx: %s\n",    all + sym.st_shndx);
	printf("st_shndx: %d\n",    sym.st_shndx);
	printf("st_value: 0x%ld\n", sym.st_value);
	printf("st_value: %s\n", all + sym.st_value + sym.st_shndx);
	printf("st_size : 0x%ld\n", sym.st_size);
}

void	print_self(char *all, t_elf elf, Elf64_Shdr *shdr, int len)
{
	char		*str;
	char		*sstr;
	Elf64_Sym	*sym;
	int			len_sym;

	str = all + shdr[elf.ehdr.e_shstrndx].sh_offset;
	(void)str;
	sstr = all + shdr[elf.ehdr.e_shstrndx - 1].sh_offset;
	for (int i = 0; i < len; i++)
	{
		if (shdr[i].sh_type == 2)
		{
			// print_oself(str, shdr[i]);
			sym = (Elf64_Sym*)(all + shdr[i].sh_offset);
			len_sym = shdr[i].sh_size / sizeof(Elf64_Sym);
		}
	}
	int ttype;
	for (int y = 0; y < len_sym; y++)
	{
		ttype = ELF64_ST_TYPE(sym[y].st_info);
		if (ttype != 4 && ttype != 3)
		{
			if (sym[y].st_value)
				printf("%.16lx %c %s\n", sym[y].st_value, symbol(sym[y], shdr), sstr + sym[y].st_name);
			else
				printf("%16c %c %s\n", ' ', symbol(sym[y], shdr), sstr + sym[y].st_name);
		}
		// else
		// 		printf("%16d %c %s\n", ttype, symbol(sym[y], shdr), sstr + sym[y].st_name);
	}
}

int main(int argi, char **argv)
{
	int fd;
	struct stat st;
	t_elf		elf;
	(void)argi;

	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return 1;
	if (fstat(fd, &st) < 0)
		return 1;
	char	 all[st.st_size + 1];
	// printf("size: %ld\n", st.st_size);
	read(fd, &elf, sizeof(t_elf));
	// print_elf(elf.ehdr);
	// print_pelf(elf.phdr);
	read(fd, all + sizeof(elf), st.st_size - sizeof(elf));
	print_self(all, elf, (Elf64_Shdr*)(all + elf.ehdr.e_shoff), (st.st_size - elf.ehdr.e_shoff) / sizeof(Elf64_Shdr));
}
