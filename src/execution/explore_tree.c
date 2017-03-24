/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 14:45:32 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/24 16:46:10 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "signal_handling.h"

void	execute(t_ast *tree, t_sh *sh)
{
	signal(SIGINT, &parent_sigint_handler);
	if (!tree)
		return ;
	if (tree->type == SEQ_NODE)
	{
		pipe_node(tree->left, sh);
		execute(tree->right, sh);
	}
	else
		pipe_node(tree, sh);
}
