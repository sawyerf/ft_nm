#include <sys/mman.h>
#include <fcntl.h>
#include <ar.h>
#include "libft.h"
#include "ft_nm.h"

char	*readf(char *file, struct stat *st)
{
	int		fd;
	char	*ptr;

	if ((fd = open(file, O_RDONLY)) < 0)
		return NULL;
	if (fstat(fd, st) < 0)
		return NULL;
	ptr = mmap(NULL, st->st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	return ptr;
}

int		c32or64(char *ptr)
{
	if (!ft_strncmp(ptr, ARMAG, SARMAG))
		return (ARCH);
	if (ft_strncmp(ptr, ELFMAG, SELFMAG))
		return (NOTELF);
	if (ptr[EI_CLASS] == ELFCLASS32)
		return (ELF32);
	else if (ptr[EI_CLASS] == ELFCLASS64)
		return (ELF64);
	else
		return (INVCL);
}

int main(int argi, char **argv)
{
	char	*ptr;
	struct stat st;
	int		class;

	(void)argi;
	ptr = readf(argv[1], &st);
	class = c32or64(ptr);
	if (class == ELF32)
		elf32(ptr, st);
	else if (class == ELF64)
		elf64(ptr, st);
	else if (class == ARCH)
		arch(ptr, st);
	else
		printf("autre\n");
}
