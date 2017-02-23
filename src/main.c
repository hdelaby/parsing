/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 08:56:41 by hdelaby           #+#    #+#             */
/*   Updated: 2017/02/23 15:12:10 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

t_list	*ft_lstpopnode(t_list **lst)
{
	t_list	*tmp;

	tmp = NULL;
	if (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		tmp->next = NULL;
	}
	return (tmp);
}

void	feed_cmdlist(t_cmdlist **cmd, int type)
{
	t_cmdlist *new_cmd;

	new_cmd = malloc(sizeof(t_cmdlist));
	ft_bzero(new_cmd, sizeof(t_cmdlist));
	if (*cmd)
	{
		(*cmd)->type = type;
		(*cmd)->next = new_cmd;
		*cmd = (*cmd)->next;
	}
}

void	parser(t_list *lst)
{
	t_cmdlist	*cmd;
	t_cmdlist	*tmp;
	t_list		*node;

	cmd = malloc(sizeof(t_cmdlist));
	ft_bzero(cmd, sizeof(t_cmdlist));
	tmp = cmd;
	while (lst)
	{
		node = ft_lstpopnode(&lst);
		if (node->content_size == WORD)
			ft_lstaddback(&cmd->args, node);
		else if (node->content_size == OREDIR || node->content_size == IREDIR)
		{
			ft_lstaddback(&cmd->redir, node);
			node = ft_lstpopnode(&lst);
			ft_lstaddback(&cmd->redir, node);
		}
		else
		{
			feed_cmdlist(&cmd, CMD);
			ft_lstaddback(&cmd->args, node);
			feed_cmdlist(&cmd, node->content_size);
		}
	}
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			ft_putendl(">> PIPE");
			ft_putchar('\n');
			tmp = tmp->next;
			continue;
		}
		ft_putendl("ARGS");
		ft_putlst(tmp->args);
		ft_putchar('\n');
		ft_putendl("REDIR");
		ft_putlst(tmp->redir);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

int		check_tokens(t_list *lst)
{
	while (lst)
	{
		if (lst->content_size == PIPE && lst->next == NULL)
			return (1);
		else if ((lst->content_size == OREDIR || lst->content_size == IREDIR)
				&& (!lst->next || lst->next->content_size != WORD))
			return (1);
		lst = lst->next;
	}
	return (0);
}

int		main(void)
{
	t_list	*lst;
	char	*cmd;

	strlen("LOL");
	cmd = ft_strdup("ls >&2- <<- | ls -l src | lol | >> hello");
	lst = lex_cmd(cmd);
	free(cmd);
	if (check_tokens(lst))
		exit(1);
	parser(lst);
}
