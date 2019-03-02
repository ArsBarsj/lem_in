/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_g_spec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuhn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 21:06:55 by artemiy           #+#    #+#             */
/*   Updated: 2019/01/09 20:20:40 by fkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static int	ft_numlen_float(long long int n)
{
	int	len;

	len = 0;
	if (n < 0)
		++len;
	while (n)
	{
		n /= 10;
		++len;
	}
	return (len);
}

char		*ft_strrstrip_zeros(char *str)
{
	int		i;
	char	*res;
	char	*first_zero;

	i = ft_strlen(str) > 0 ? ft_strlen(str) - 1 : 0;
	if (!(first_zero = ft_strchr(str, '0')))
		return (str);
	if (ft_strchr(str, 'e') || ft_strchr(str, 'E'))
		i = ft_strlen(str) - 5;
	while (str + i >= first_zero && (str[i] == '0' || str[i] == '.'))
		i--;
	res = ft_strsub(str, 0, str[i] == '0' ? i : i + 1);
	if (ft_strchr(str, 'e') || ft_strchr(str, 'E'))
	{
		first_zero = res;
		res = ft_strjoin(res, str + ft_strlen(str) - 4);
		free(first_zero);
	}
	free(str);
	return (res);
}

char		*ft_double_to_g(long double num, t_specifier *spec)
{
	char	*fstr;
	char	*str;
	int		exponent;
	int		precition;

	precition = spec->precition > 0 ? spec->precition : 6;
	if (!(fstr = ft_ftoa(num, 18)))
		return (NULL);
	exponent = num == 0.0 ? 0 : ft_get_exponent(fstr);
	free(fstr);
	if (exponent >= precition || exponent < -4)
		fstr = ft_double_to_exp(num, precition - 1, 'e');
	else
		fstr = ft_ftoa(num, precition - ft_numlen_float((long long)num));
	str = ft_strrstrip_zeros(fstr);
	return (str);
}

char		*ft_dispatch_g(t_specifier *spec, va_list *ap)
{
	char	*str;

	if (spec->precition == 0)
		spec->precition = 1;
	if (spec->length == 0)
		str = ft_double_to_g(va_arg(*ap, double), spec);
	else if (spec->length == 3)
		str = ft_double_to_g(va_arg(*ap, double), spec);
	else
		str = ft_double_to_g(va_arg(*ap, long double), spec);
	return (str);
}
