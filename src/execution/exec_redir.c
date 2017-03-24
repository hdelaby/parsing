/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:42:08 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/24 15:20:52 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int		ft_isnumber(char *str)
{
	while (*str)
		if (!ft_isdigit(*(str++)))
			return (0);
	return (1);
}

void			get_arg_type(char *arg, struct s_redir *info)
{
	if (info->redir_type == REDIR_AMP && ft_isnumber(arg))
	{
		info->fd_src = ft_atoi(arg);
		info->arg_type = ARG_NUMBER;
	}
	else if (info->redir_type == REDIR_AMP &&
			(ft_strlen(arg) == 1) && (*arg) == '-')
		info->arg_type = ARG_CLOSE;
	else
	{
		info->arg_type = ARG_WORD;
		info->word = arg;
	}
}

void	get_info(struct s_redir *info, char *redir_op, char *arg, size_t type)
{
	if (type == IREDIR)
		info->fd_dst = STDIN_FILENO;
	else
		info->fd_dst = STDOUT_FILENO;
	if (ft_isdigit(*redir_op))
	{
		info->fd_dst = ft_atoi(redir_op);
		while (ft_isdigit(*redir_op))
			redir_op++;
	}
	redir_op += 1;
	if (*redir_op == '&')
		info->redir_type = REDIR_AMP;
	else if (type == IREDIR && *redir_op == '>')
		info->redir_type = REDIR_RDWR;
	else if (*redir_op == '>')
		info->redir_type = REDIR_APD;
	get_arg_type(arg, info);
}

void	do_redir(struct s_redir *info, size_t type)
{
	if (info->arg_type == ARG_CLOSE)
	{
		close(info->fd_dst);
		return ;
	}
	if (info->arg_type == ARG_WORD && type == OREDIR)
		info->fd_src = open(info->word, (info->redir_type == REDIR_APD ?
				WRAPD : WR), 0644);
	else if (info->arg_type == ARG_WORD)
		info->fd_src = open(info->word, (info->redir_type == REDIR_RDWR ?
				RDWR : RD), 0644);
	dup2(info->fd_src, info->fd_dst);
}

void    get_redir(t_list *redir)
{
	struct s_redir	info;

	ft_bzero(&info, sizeof(struct s_redir));
	get_info(&info, redir->content, redir->next->content, redir->content_size);
	do_redir(&info, redir->content_size);
}

void	apply_redir(t_list *lst)
{
	if (lst)
		get_redir(lst);
}
