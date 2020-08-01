/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_str_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 23:02:19 by mjuli             #+#    #+#             */
/*   Updated: 2020/07/28 18:58:18 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	process_null(t_arg_info *arg, char **s)
{
	if (arg->precision != -1 && arg->precision < 5)
		*s = "";
	else
		*s = "(null)";
}

static void	print_padding(t_arg_info *arg, int len)
{
	while (arg->width-- > len)
		arg->result += write(1, " ", 1);
}

void		process_string(t_arg_info *arg)
{
	char	*s;
	int		d;
	int		i;

	s = va_arg(arg->ap, char*);
	if (s == NULL)
		process_null(arg, &s);
	d = ft_strlen(s);
	if (arg->precision < 0)
		arg->precision = 0x7fffffff;
	else if (arg->precision >= 0 && d > arg->precision)
		d = arg->precision;
	if (!check_flag(arg, FLAG_DASH))
		print_padding(arg, d);
	i = d;
	while (*s && i-- > 0)
		arg->result += write(1, s++, 1);
	if (check_flag(arg, FLAG_DASH))
		print_padding(arg, d);
}

void		process_char(t_arg_info *arg)
{
	char	c;

	c = va_arg(arg->ap, int);
	if (!check_flag(arg, FLAG_DASH))
		print_padding(arg, 1);
	arg->result += write(1, &c, 1);
	if (check_flag(arg, FLAG_DASH))
		print_padding(arg, 1);
}
