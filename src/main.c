//#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>
#include "libft.h"


void	print_elf(Elf64_Ehdr elf)
{
	if (elf.e_ident[EI_CLASS] == ELFCLASS32)
  		printf("32bit\n");
	if (elf.e_ident[EI_CLASS] == ELFCLASS64)
  		printf("64bit\n");
	// print_hex((unsigned char*)&elf, sizeof(elf));
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

void	print_self(char *all, t_elf elf, Elf64_Shdr *shdr, int len)
{
	char *str;
	char *sstr;
	Elf64_Sym *sym;

	str = all + shdr[elf.ehdr.e_shstrndx].sh_offset;
	(void)str;
	sstr = all + shdr[elf.ehdr.e_shstrndx - 1].sh_offset;
	// print_hex((unsigned char *)sstr, 300);
	for (int i = 0; i < len; i++)
	{
		// print_hex((unsigned char *)all + shdr[i].sh_offset, shdr[i].sh_size);
		// printf("yyyyyyyyyy  : %d\n",    i);
		// printf("======== Shdr =======\n");
		// printf("name        : %s\n",    str + shdr[i].sh_name);
		// printf("sh_type     : %d\n",    shdr[i].sh_type);
		// printf("sh_addr     : 0x%ld\n", shdr[i].sh_addr);
		// printf("sh_offset   : 0x%ld\n", shdr[i].sh_offset);
		if (shdr[i].sh_type == 2)
		{
			// printf("======== Shdr =======\n");
			// printf("name        : %s\n",    str + shdr[i].sh_name);
			// printf("sh_type     : %d\n",    shdr[i].sh_type);
			// printf("sh_name     : 0x%d\n",	shdr[i].sh_name);
			// printf("sh_type     : %d\n",    shdr[i].sh_type);
			// printf("sh_flags    : %ld\n",   shdr[i].sh_flags);
			// printf("sh_addr     : 0x%ld\n", shdr[i].sh_addr);
			// printf("sh_offset   : 0x%ld\n", shdr[i].sh_offset);
			// printf("sh_size     : %ld\n",   shdr[i].sh_size);
			// printf("sh_link     : 0x%d\n",  shdr[i].sh_link);
			// printf("sh_info     : 0x%d\n",  shdr[i].sh_info);
			// printf("sh_addralign: 0x%ld\n", shdr[i].sh_addralign);
			// printf("sh_entsize  : 0x%ld\n", shdr[i].sh_entsize);
			sym = (Elf64_Sym*)(all + shdr[i].sh_offset);
		}
	}
	int ttype;
	for (int y = 0; y < 213; y++)
	{
		char type[20][20] = {
			"NOTYPE",
			"OBJECT",
			"FUNC",
			"SECTION",
			"FILE",
			"COMMON",
			"TLS",
			"NUM",
			"LOOS",
			"GNU_IFUNC",
			"HIOS",
			"LOPROC",
			"HIPROC"
		};
		char bind[20][20];
		ft_strcpy(bind[STB_LOCAL],      "LOCAL");
		ft_strcpy(bind[STB_GLOBAL],     "GLOBAL");
		ft_strcpy(bind[STB_WEAK],       "WEAK");
		ft_strcpy(bind[STB_NUM],        "NUM");
		ft_strcpy(bind[STB_LOOS],       "LOOS");
		ft_strcpy(bind[STB_GNU_UNIQUE], "GNU_UNIQUE");
		ft_strcpy(bind[STB_HIOS],       "HIOS");
		ft_strcpy(bind[STB_LOPROC],     "LOPROC");
		ft_strcpy(bind[STB_HIPROC],     "HIPROC");

		(void)sym;
		ttype = ELF64_ST_TYPE(sym[y].st_info);
		if (ttype != 0 && ttype != 4 && ttype != 3)
		{
			printf("%.16lx %-10s %-10s %s\n", sym[y].st_value, bind[ELF64_ST_BIND(sym[y].st_info)], type[ELF64_ST_TYPE(sym[y].st_info)], sstr + sym[y].st_name);
			//printf("======== ST =======\n");
			// printf("nameee  : %s\n",    sstr + sym[y].st_name);
			// printf("st_name : 0x%d\n",  sym[y].st_name);
			// printf("st_info : %d %d\n",    y, ELF64_ST_TYPE(sym[y].st_info));
			// printf("st_info : %s\n",    bind[ELF64_ST_BIND(sym[y].st_info)]);
			// printf("st_other: %c\n",    sym[y].st_other);
			// printf("st_shndx: %s\n",    all + sym[y].st_shndx);
			// printf("st_value: 0x%ld\n", sym[y].st_value);
			// printf("st_size : 0x%ld\n", sym[y].st_size);
		}
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
	printf("size: %ld\n", st.st_size);
	read(fd, &elf, sizeof(t_elf));
	// print_elf(elf.ehdr);
	// print_pelf(elf.phdr);
	read(fd, all + sizeof(elf), st.st_size - sizeof(elf));
	print_self(all, elf, (Elf64_Shdr*)(all + elf.ehdr.e_shoff), (st.st_size - elf.ehdr.e_shoff) / sizeof(Elf64_Shdr));
}
