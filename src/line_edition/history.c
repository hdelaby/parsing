/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 15:12:46 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/28 11:17:59 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

/*
** This lot of functions handles the history functionaly of our line edition.
** We first retrieve the history defined in HISTORY_PATH, and store its content
** in a doubly-linked lists. This allows easy navigation whenever we want to
** retrieve the content.
** The functions are self_explanatory and quite simple otherwise.
*/

static void	feed_line(t_line *line, char *entry)
{
	cursor_to_home(line);
	tputs(tgetstr("cd", NULL), 0, &tc_putc);
	ft_bzero(line->cmd, MAX_CMD_LEN);
	ft_strcpy(line->cmd, entry);
	line->cursor = ft_strlen(entry);
	line->length = line->cursor;
}

void		new_hist_entry(t_line *line, t_dlist **hist)
{
	if (!line->hist || (line->hist && !line->hist_depth))
		return ;
	line->hist_depth--;
	*hist = (*hist)->prev;
	feed_line(line, (*hist)->content);
	ft_putstr_fd(line->cmd, 0);
	if (!line->hist_depth)
		ft_dlstremovenode(hist);
}

void		old_hist_entry(t_line *line, t_dlist **hist)
{
	t_dlist *new_node;

	if (!line->hist || (line->hist && line->hist_depth == line->hist_size))
		return ;
	if (!line->hist_depth)
	{
		new_node = ft_dlstnew(line->cmd, ft_strlen(line->cmd) + 1);
		if (new_node)
			new_node->content_size = SPE_CMD_LEN;
		ft_dlstadd(hist, new_node);
	}
	*hist = (*hist)->next;
	line->hist_depth++;
	feed_line(line, (*hist)->content);
	ft_putstr_fd(line->cmd, 0);
}
