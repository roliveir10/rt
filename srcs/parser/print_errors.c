/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 01:11:14 by oboutrol          #+#    #+#             */
/*   Updated: 2019/06/26 07:16:41 by oboutrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		print_warning(char *str)
{
	ft_putstr_fd("rt: Warning: ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
}

void		print_na_recon(char *str, char *type)
{
	ft_putstr_fd("rt: Warning: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("' is not reconized for `", 2);
	ft_putstr_fd(type, 2);
	ft_putstr_fd("': Dropping\n", 2);
}
