#include <stdio.h>
#include <elf.h>

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
	(void)all;
	printf("======== ST =======\n");
	printf("st_name : 0x%d\n",  sym.st_name);
	if (sym.st_name < 100000)
		printf("nameee  : %s\n",    sstr + sym.st_name);
	printf("st_info : %d\n", ELF64_ST_TYPE(sym.st_info));
	printf("st_other: %c\n",    sym.st_other);
	// printf("st_shndx: %s\n",    all + sym.st_shndx);
	printf("st_shndx: %d\n",    sym.st_shndx);
	printf("st_value: 0x%ld\n", sym.st_value);
	// printf("st_value: %s\n", all + sym.st_value + sym.st_shndx);
	printf("st_size : 0x%ld\n", sym.st_size);
}

