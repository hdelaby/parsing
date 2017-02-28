/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 08:58:46 by hdelaby           #+#    #+#             */
/*   Updated: 2017/02/28 13:39:32 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parsing_error(char *str)
{
	ft_putstr_fd("Parsing error at ", 2);
	ft_putendl_fd(str, 2);
}

void	eat(t_list **tok, int type)
{
	if ((*tok)->content_size == (size_t)type)
		*tok = (*tok)->next;
	else
		parsing_error((char *)(*tok)->content);
}

void	linebreak(t_list **tok)
{
	while ((*tok)->content_size == EOL)
		eat(tok, EOL);
}

void	args(t_list **tok)
{
	if ((*tok)->content_size == WORD)
		eat(tok, WORD);
}

void	redir(t_list **tok)
{
	eat(tok, IREDIR);
	eat(tok, WORD);
}

void	simple_cmd(t_list **tok)
{
	if ((*tok)->content_size == IREDIR)
		redir(tok);
	else
		args(tok);
	while ((*tok)->content_size == IREDIR || (*tok)->content_size == WORD)
		simple_cmd(tok);
}

void	job(t_list **tok)
{
	simple_cmd(tok);
	while ((*tok)->content_size == PIPE)
	{
		eat(tok, PIPE);
		linebreak(tok);
		job(tok);
	}
}

void	separator(t_list **tok)
{
	if ((*tok)->content_size == SEMICO)
		eat(tok, SEMICO);
	else
		linebreak(tok);
}

void	cmd(t_list **tok)
{
	if ((*tok)->content_size == SEMICO || (*tok)->content_size == EOL)
	{
		separator(tok);
		return ;
	}
	else
	{
		job(tok);
		separator(tok);
	}
}

int		parser(t_list *tok)
{
	job(&tok);
	if (tok && tok->content_size != END)
		parsing_error(tok->content);
	return (1);
}
