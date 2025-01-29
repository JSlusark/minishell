#include "../../../include/minishell.h"

int handle_env(t_node_list *node)
{
	int i;

	i = 0;
	while (node->msh->ms_env[i])
	{
		printf("%s\n", node->msh->ms_env[i++]);
	}
	return (0);
}
