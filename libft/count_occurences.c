int		count_occurences(char *str, char c)
{
	int 	nb_occ;

	nb_occ = 0;
	while (*str)
	{
		if (*str == c)
			nb_occ++;
		str++;
	}
	return (nb_occ);
}
