/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 11:40:42 by hdelaby           #+#    #+#             */
/*   Updated: 2017/02/20 17:02:03 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"

# define MAX_TOKEN_LEN 256

typedef struct	s_token
{
	char	str[MAX_TOKEN_LEN];
	int		cmd_i;
	int		str_i;
	int		is_pipe;
	int		is_quoted;
	int		is_oredir;
	int		is_iredir;
}				t_token;

struct			s_parsingtab
{
	char	key;
	void	(*p)(t_token *tok, t_list **tokens_lst);
};

void	end_token(t_token *tok, t_list **tokens_lst);

void	handle_pipe(t_token *tok, t_list **tokens_lst);
void	handle_space(t_token *tok, t_list **tokens_lst);
void	handle_dquote(t_token *tok, t_list **tokens_lst);
void	handle_squote(t_token *tok, t_list **tokens_lst);
void	handle_backsh(t_token *tok, t_list **tokens_lst);
void	handle_iredir(t_token *tok, t_list **tokens_lst);
void	handle_oredir(t_token *tok, t_list **tokens_lst);
void	handle_other(t_token *tok, t_list **tokens_lst, char key);

#endif
