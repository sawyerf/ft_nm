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
	{
		dprintf(2, "ft_nm: %s: Open error\n", file);
		return (NULL);
	}
	if (fstat(fd, st) < 0)
	{
		dprintf(2, "ft_nm: %s: Fstat error\n", file);
		return (NULL);
	}
	if ((st->st_mode & S_IFMT) == S_IFDIR)
	{
		dprintf(2, "ft_nm: Attention : « %s » est un répertoire\n", file);
		return (NULL);
	}
	ptr = mmap(NULL, st->st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);
	return (ptr);
}

int	amagic(char *ptr, size_t size)
{
	if (size > SARMAG && !ft_strncmp(ptr, ARMAG, SARMAG))
		return (ARCH);
	if (size < EI_CLASS)
		return (INVCL);
	if (ft_strncmp(ptr, ELFMAG, SELFMAG))
		return (NOTELF);
	if (ptr[EI_CLASS] == ELFCLASS32)
		return (ELF32);
	else if (ptr[EI_CLASS] == ELFCLASS64)
		return (ELF64);
	else
		return (INVCL);
}

int	main(int argi, char **argv)
{
	char	*ptr;
	struct stat st;
	int		class;

	(void)argi;
	for (int i = 1; argv[i]; i++)
	{
		if (!(ptr = readf(argv[i], &st)))
			continue ;
		//printf("file: %s\n", argv[i]);
		class = amagic(ptr, st.st_size);
		if (class > ISERR && argi > 2)
			printf("\n%s:\n", argv[i]);
		if (class == ELF32)
			elf32(ptr, st.st_size, argv[i]);
		else if (class == ELF64)
			elf64(ptr, st.st_size, argv[i]);
		else if (class == ARCH)
			arch(ptr, st.st_size);
		else if (class == NOTELF)
			dprintf(2, "ft_nm: %s: file format not recognized\n", argv[i]);
	}
}
