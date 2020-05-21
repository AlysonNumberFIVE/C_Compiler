/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angonyam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 15:54:01 by angonyam          #+#    #+#             */
/*   Updated: 2017/12/19 17:15:06 by angonyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "ft_read/line.h"
#include "shell.h"

char				*exit_trap(char *str, t_exp **head, char **env)
{
	if (ft_strstr(str, "exit"))
		ft_exit(str, env, *head);
	if (ft_strstr(str, "${"))
		str = handling_exports(str, head);
	if (ft_strstr(str, "exit"))
		ft_exit(str, env, *head);
	return (str);
}

char				*input(char **env, t_exp **head)
{
	char			*str;
	char			*temp;
	int				val;

	ft_printf("LOL$HELL:#>");
	str = setting_up(env);
	if (str == NULL)
		return (input(env, head));
	str = exit_trap(str, head, env);
	temp = ft_strtrim(str);
	free(str);
	if (ft_strchr(temp, '(') || ft_strchr(temp, ')'))
	{
		env = subshell_checker(temp, env, &val);
		return (input(env, head));
	}
	if (ft_strlen(temp) <= 1)
	{
		free(temp);
		return (input(env, head));
	}
	return (temp);
}

char				**lolshell(char *str, char **env, t_exp **head, int *r)
{
	if ((export_check(str) == 1 && ft_strchr(str, '='))
		|| ft_strstr(str, "export"))
	{
		str = handling_setenv_string(str);
		env = export(str, env, head, r);
	}
	return (env);
}

void				ft_42sh(char **env, t_exp *head)
{
	int				r;
	char			*str;
	int				val;

	while (42)
	{
		val = 0;
		r = 0;
		str = input(env, &head);
		env = lolshell(str, env, &head, &r);
		if (ft_strchr(str, ';'))
			env = altogether(str, env, &val, &r);
		else if (ft_strstr(str, ">"))
			env = run_redirection(str, env, &val, &r);
		else if (ft_strncmp(str, "echo", 4) == 0)
			aly_echo(str, env, &r);
		else if (ft_strchr(str, '|') && !ft_strstr(str, "||"))
			piping(str, env, &val, &r);
		else if (ft_strstr(str, "&&") || ft_strstr(str, "||"))
			env = andor_management(str, env, &r);
		if (r == 0)
			env = run(str, env, &val);
		free(str);
	}
}
