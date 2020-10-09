
#include "parser.h"

long long		ft_atol_exit(const char *str)
{
	int				i;
	int				sign;
	double			number;
	long long		out;

	out = 0;
	i = 0;
	sign = 1;
	number = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] <= '9' && str[i] >= '0')
		number = number * 10 + (str[i++] - '0');
	if (number > 9223372036854775807)
		return (256);
	out = (long long)(number);
	if (sign == 1)
		out %= 256;
	else
		out = -(out % 256) + 256;
	return (out);
}

void		exit_cmd(char **str)
{
	int				i;
	int				minus;
	unsigned short	code;

	minus = 0;
	i = 0;
	while (str[i] != NULL)
		i++;
	if (i == 1)
		exit(1);
	if (i != 2)
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 1);
	else
	{
		i = -1;
		if (str[1][0] =='-')
		{
			minus = 1;
			i++;
		}
		while (str[1][++i] != '\0')
			if (!ft_isdigit(str[1][i]))
			{
				i = 0;
				break;
			}
		if (i == 0)
		{
			ft_putstr_fd("exit\nminishell: exit: ", 1);
			ft_putstr_fd(str[1], 1);
			ft_putstr_fd(": numeric argument required\n", 1);
			exit (255);
		}
		else
		{
			if ((code = (unsigned short)ft_atol_exit(str[1])) == 256)
			{
				ft_putstr_fd("exit\nminishell: exit: ", 1);
				ft_putstr_fd(str[1], 1);
				ft_putstr_fd(": numeric argument required\n", 1);
				exit (255);
			}
			else
				exit (code);
		}
	}
}
