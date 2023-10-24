/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:21:05 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/24 14:00:55 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_lounch(void)
{
	char	*prompt;

	while (!info->exit_f)
	{
		prompt = ft_readline();
		if (!prompt)
			continue ;
		tokenizer(prompt);
		if (!ft_strncmp(prompt, "wq", SIZE_MAX))
			info->exit_f = 1;
/* 		if (!ft_strncmp(prompt, "env", SIZE_MAX))
		{
			int i = 0;
			while (info->envp[i])
			{
				printf ("%s\n", info->envp[i]);
				i++;
			}
		}
		if (!ft_strncmp(prompt, "env_list", SIZE_MAX))
		{
			t_list *ptr = info->envp_lst;
			while (ptr != NULL)
			{
				printf ("key: %s , value: %s\n", ptr->key, ptr->value);
				ptr = ptr->next;
			}
		} */
		expansion();
		/* t_token *ptr = info->token_lst;
		while (ptr != NULL)
		{
			printf ("token: %d , value: %s , len: %d\n", ptr->key, ptr->value, ptr->len);
			ptr = ptr->next;
		} */
		grouping();
		info->token_lst = NULL;
		free(prompt);
	}
	clear_history();
}
