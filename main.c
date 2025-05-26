/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:51:16 by zatalbi           #+#    #+#             */
/*   Updated: 2025/05/26 16:46:26 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	t_tree	*tree;
	char *PWD;
	char	*prompt;
	

	while (1)
	{
		PWD = getenv("PWD");
		prompt = ft_strjoin(PWD, "> ");
		line = readline(prompt);
		if (!line)
			break ;
		add_history(line);
		tree = ft_parser(line, 1337);
		show_the_tree(tree);
		recursion(tree, PWD);
		ft_free_tree(tree);
		free(line);
	}
	rl_clear_history();
	exit(0);
}
