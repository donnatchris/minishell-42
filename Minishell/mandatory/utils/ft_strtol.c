#include "../include/minishell.h"

static int	initial_check(const char *s, int *neg, int *base)
{
	int	i;

	i = 0;
    while (ft_strchr(WHITESPACES, ((int)s[i])) != NULL)
        i++;
    if (s[i] == '-' || s[i] == '+')
    {
        if (s[i] == '-')
            *neg = 1;
        i++;
    }
	if ((*base == 0 || *base == 16) && s[i] == '0'
		&& (s[i + 1] == 'x' || s[i + 1] == 'X'))
	{
		i += 2;
		*base = 16;
	}
	else if (*base == 0 && s[i] == '0')
		*base = 8;
	else if (*base == 0)
		*base = 10;
	return (i);
}

static void	setup_cut(int neg, int base, long *cutoff, int *cutlim)
{
	if (neg)
		*cutoff = LONG_MIN;
	else
		*cutoff = LONG_MAX;
	*cutlim = (int)(*cutoff % (long)base);
	*cutoff /= (long)base;
	if (neg)
	{
		if (*cutlim > 0)
		{
			*cutlim -= base;
			*cutoff += 1;
		}
		*cutlim = -(*cutlim);
	}
}

static long	setup_acc(long acc, long cutoff, int c, int vars[4])
{
	long	res;

	res = acc;
	if (vars[0])
	{
		if (acc < cutoff || (acc == cutoff && c > vars[3]))
		{
			res = LONG_MIN;
			errno = ERANGE;
		}
		else
			res = (acc * vars[1]) - c;
	}
	else
	{
		if (acc > cutoff || (acc == cutoff && c > vars[3]))
		{
			res = LONG_MAX;
			errno = ERANGE;
		}
		else
			res = (acc * vars[1]) + c;
	}
	return (res);
}

static long	setup_result(const char *s, char **end, long cutoff, int vars[4])
{
	long	acc;
	int		c;

	acc = 0;
	while (s[vars[2]] && (acc != LONG_MIN && acc != LONG_MAX))
	{
		c = s[vars[2]];
		if (ft_isdigit(c))
			c -= '0';
		else if (ft_isalpha(c))
		{
			if (c > 64 && c < 91)
				c -= 'A' - 10;
			else if (c > 96 && c < 123)
				c -= 'a' - 10;
		}
		else
			break ;
		if (c >= vars[1])
			break ;
		acc = setup_acc(acc, cutoff, c, vars);
		vars[2]++;
	}
	*end = (char *)(&s[vars[2]]);
	return (acc);
}

long    ft_strtol(const char *nptr, char **endptr, int base)
{
	long	res;
	long	cutoff;
	int		intarray[4];

	res = 0;
    intarray[0] = 0;
	intarray[1] = base;
	intarray[2] = initial_check(nptr, &(intarray[0]), &(intarray[1]));
	setup_cut(intarray[0], base, &cutoff, &(intarray[3]));
	res = setup_result(nptr, endptr, cutoff, intarray);
	return (res);
}
