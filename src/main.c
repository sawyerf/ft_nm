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
	print_hex((unsigned char*)&elf, sizeof(elf));
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

int main(int argi, char **argv)
{
	int fd;
	struct stat st;
	t_elf		elf;
	Elf64_Shdr	shdr;
	(void)argi;

	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return 1;
	if (fstat(fd, &st) < 0)
		return 1;
	char	 all[st.st_size + 1];
	printf("size: %ld\n", st.st_size);
	read(fd, &elf, sizeof(t_elf));
	print_elf(elf.ehdr);
	print_pelf(elf.phdr);
	read(fd, all + sizeof(elf), st.st_size - sizeof(elf));
	// for (long unsigned int i = elf.ehdr.e_shoff; i < elf.ehdr.e_shoff + sizeof(shdr) * 11; i += sizeof(shdr))
	int y = 0;
	for (long int i = elf.ehdr.e_shoff; i < st.st_size; i += sizeof(shdr))
	{
		y += 1;
		memcpy(&shdr, all + i, sizeof(shdr));
		printf("======== Shdr =======\n");
		
		//print_hex((unsigned char *)&all[i], sizeof(shdr));
		printf("======== name =======\n");
		print_hex((unsigned char *)all + shdr.sh_offset, shdr.sh_size);
		printf("yyyyyyyyyy  : %d\n",    y);
		printf("addrrrrrrr  : 0x%lx\n", i);
		printf("sh_name     : 0x%d\n",	shdr.sh_name);
		printf("sh_type     : %d\n",    shdr.sh_type);
		printf("sh_flags    : %ld\n",   shdr.sh_flags);
		printf("sh_addr     : 0x%ld\n", shdr.sh_addr);
		printf("sh_offset   : 0x%ld\n", shdr.sh_offset);
		printf("sh_size     : %ld\n",   shdr.sh_size);
		printf("sh_link     : 0x%d\n",  shdr.sh_link);
		printf("sh_info     : 0x%d\n",  shdr.sh_info);
		printf("sh_addralign: 0x%ld\n", shdr.sh_addralign);
		printf("sh_entsize  : 0x%ld\n", shdr.sh_entsize);
	}
}
	// print_hex((unsigned char *)all, st.st_size);

