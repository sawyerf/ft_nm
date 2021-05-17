#include <sys/mman.h>
#include <fcntl.h>
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
	if (ft_strncmp(ptr, ELFMAG, SELFMAG))
		return (NOTELF);
	if (ptr[EI_CLASS] == ELFCLASS32)
		return (ELF32);
	else if (ptr[EI_CLASS] == ELFCLASS64)
		return (ELF64);
	else
		return (INVCL);
}

void	elf32(char *ptr, struct stat st)
{
	t_32elf	elf;

	(void)st;
	ft_memcpy(&elf.ehdr, ptr, sizeof(Elf32_Ehdr));
	ft_memcpy(&elf.phdr, ptr + elf.ehdr.e_phoff, sizeof(Elf32_Phdr));
	elf.shdr = (Elf32_Shdr*)(ptr + elf.ehdr.e_shoff);
}

int main(int argi, char **argv)
{
	char	*ptr;
	struct stat st;
	int		class;

	ptr = readf(argv[1], &st);
	class = c32or64(ptr);
	if (class == ELF32)
		(void)argi;
	else if (class == ELF64)
		elf64(ptr, st);
}
