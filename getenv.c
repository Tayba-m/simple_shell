#include "shell.h"

/**
 * getEnviron - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **getEnviron(Info *info)
{
    if (!info->environ || info->envChanged)
    {
        info->environ = listToStrings(info->env);
        info->envChanged = 0;
    }

    return (info->environ);
}

/**
 * unsetEnv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int unsetEnv(Info *info, char *var)
{
    List *node = info->env;
    size_t i = 0;
    char *p;

    if (!node || !var)
        return (0);

    while (node)
    {
        p = startsWith(node->str, var);
        if (p && *p == '=')
        {
            info->envChanged = deleteNodeAtIndex(&(info->env), i);
            i = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        i++;
    }
    return (info->envChanged);
}

/**
 * setEnv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */
int setEnv(Info *info, char *var, char *value)
{
    char *buf = NULL;
    List *node;
    char *p;

    if (!var || !value)
        return (0);

    buf = malloc(strlen(var) + strlen(value) + 2);
    if (!buf)
        return (1);
    strcpy(buf, var);
    strcat(buf, "=");
    strcat(buf, value);
    node = info->env;
    while (node)
    {
        p = startsWith(node->str, var);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            info->envChanged = 1;
            return (0);
        }
        node = node->next;
    }
    addNodeEnd(&(info->env), buf, 0);
    free(buf);
    info->envChanged = 1;
    return (0);
}
