#include "libft.h"
#include "ft_nm.h"

uint64_t	swap64(uint64_t nbr, char endian)
{
	int			i;
	uint64_t	ret;
	size_t		size;

	i = 0;
	if (endian != ELFDATA2MSB)
		return (nbr);
	size = sizeof(nbr);
	ret = 0;
	while (size)
	{
		size--;
		((char*)&ret)[i] = ((char*)&nbr)[size];
		i++;
	}
	((char*)&ret)[i] = ((char*)&nbr)[size];
	return (ret);
}

uint32_t	swap32(uint32_t nbr, char endian)
{
	int			i;
	uint32_t	ret;
	size_t		size;

	i = 0;
	size = sizeof(nbr);
	if (endian != ELFDATA2MSB)
		return (nbr);
	ret = 0;
	while (size)
	{
		size--;
		((char*)&ret)[i] = ((char*)&nbr)[size];
		i++;
	}
	return (ret);
}

uint16_t	swap16(uint16_t nbr, char endian)
{
	int			i;
	uint16_t	ret;
	size_t		size;

	i = 0;
	if (endian != ELFDATA2MSB)
		return (nbr);
	size = sizeof(nbr);
	ret = 0;
	while (size)
	{
		size--;
		((char*)&ret)[i] = ((char*)&nbr)[size];
		i++;
	}
	((char*)&ret)[i] = ((char*)&nbr)[size];
	return (ret);
}
