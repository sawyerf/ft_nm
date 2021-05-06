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
	printf("e_indent : %s\n", elf.e_ident);
	printf("e_indent4: %d\n", elf.e_ident[EI_CLASS]);
	printf("e_phnum  : %d\n", elf.e_phnum);
	printf("e_type   : %d\n", elf.e_type);
	printf("e_machine: %d\n", elf.e_machine);
	printf("e_version: %d\n", elf.e_version);
	printf("e_entry  : %lx\n", elf.e_entry);
	printf("e_phoff  : %lx\n", elf.e_phoff);
	printf("e_shoff  : %lx\n", elf.e_shoff);
	printf("e_phnum  : %x\n", elf.e_phnum);
}

int main(int argi, char **argv)
{
	int fd;
	struct stat st;
	Elf64_Ehdr elf;
	char	 all[999999];
	(void)argi;

	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return 1;
	if (fstat(fd, &st) < 0)
		return 1;
	read(fd, &elf, sizeof(elf));
	print_elf(elf);
	read(fd, all + sizeof(elf), st.st_size - sizeof(elf));
	// print_hex((unsigned char *)&all[elf.e_phoff + elf.e_phentsize * elf.e_phnum], st.st_size - elf.e_phoff - elf.e_phentsize * elf.e_phnum);
	print_hex((unsigned char *)&all[elf.e_phoff], st.st_size - elf.e_phoff);
}
