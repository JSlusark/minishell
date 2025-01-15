#include "../../../include/minishell.h"

int handle_env(char **ms_env)
{
    int i;

    i = 0;
    while (ms_env[i])
    {
        printf("%s\n", ms_env[i++]);
    }
    return (0);
}