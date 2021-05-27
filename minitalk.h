/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara </var/mail/snara>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 21:49:52 by snara             #+#    #+#             */
/*   Updated: 2021/05/28 02:57:51 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# define END 0

int	ft_puts(char *s, int fd);
int	ft_putnbr_fd(int n, int fd);
int	ft_atoi_p(char *s, int *n);

#endif
