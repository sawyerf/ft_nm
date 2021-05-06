//#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>

int main(int argi, char **argv)
{
	int fd;
	struct stat buf;
	Elf64_Ehdr elf;
	(void)argi;

	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return 1;
	if (fstat(fd, &buf) < 0)
		return 1;
	read(fd, &elf, sizeof(elf));
	printf("%s\n", elf.e_ident);
	printf("%d\n", elf.e_ident[EI_CLASS]);
	if (elf.e_ident[EI_CLASS] == ELFCLASS32)
  		printf("32bit\n");
	if (elf.e_ident[EI_CLASS] == ELFCLASS64)
  		printf("64bit\n");
	printf("%d\n", elf.e_type);
	printf("%d\n", elf.e_machine);
	printf("%d\n", elf.e_version);
}
