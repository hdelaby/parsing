/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 08:56:41 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/01 13:38:45 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* t_list	*ft_lstpopnode(t_list **lst) */
/* { */
/* 	t_list	*tmp; */

/* 	tmp = NULL; */
/* 	if (*lst) */
/* 	{ */
/* 		tmp = *lst; */
/* 		*lst = (*lst)->next; */
/* 		tmp->next = NULL; */
/* 	} */
/* 	return (tmp); */
/* } */

/* void	feed_cmdlist(t_cmdlist **cmd, int type) */
/* { */
/* 	t_cmdlist *new_cmd; */

/* 	new_cmd = malloc(sizeof(t_cmdlist)); */
/* 	ft_bzero(new_cmd, sizeof(t_cmdlist)); */
/* 	if (*cmd) */
/* 	{ */
/* 		(*cmd)->type = type; */
/* 		(*cmd)->next = new_cmd; */
/* 		*cmd = (*cmd)->next; */
/* 	} */
/* } */

/* void	parser(t_list *lst) */
/* { */
/* 	t_cmdlist	*cmd; */
/* 	t_cmdlist	*tmp; */
/* 	t_list		*node; */

/* 	cmd = malloc(sizeof(t_cmdlist)); */
/* 	ft_bzero(cmd, sizeof(t_cmdlist)); */
/* 	tmp = cmd; */
/* 	while (lst) */
/* 	{ */
/* 		node = ft_lstpopnode(&lst); */
/* 		if (node->content_size == WORD) */
/* 			ft_lstaddback(&cmd->args, node); */
/* 		else if (node->content_size == OREDIR || node->content_size == IREDIR) */
/* 		{ */
/* 			ft_lstaddback(&cmd->redir, node); */
/* 			node = ft_lstpopnode(&lst); */
/* 			ft_lstaddback(&cmd->redir, node); */
/* 		} */
/* 		else */
/* 		{ */
/* 			feed_cmdlist(&cmd, CMD); */
/* 			ft_lstaddback(&cmd->args, node); */
/* 			feed_cmdlist(&cmd, node->content_size); */
/* 		} */
/* 	} */
/* } */

/* int		check_tokens(t_list *lst) */
/* { */
/* 	while (lst) */
/* 	{ */
/* 		if (lst->content_size == PIPE && lst->next == NULL) */
/* 			return (1); */
/* 		else if ((lst->content_size == OREDIR || lst->content_size == IREDIR) */
/* 				&& (!lst->next || lst->next->content_size != WORD)) */
/* 			return (1); */
/* 		lst = lst->next; */
/* 	} */
/* 	return (0); */
/* } */

int		main(void)
{
	t_list	*lst;
	char	*cmd;

	cmd = ft_strdup("ls -l |\n");
	lst = lex_cmd(cmd);
	free(cmd);
	parser(lst);
}
