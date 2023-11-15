#include "shell.h"

/**
 * clearInfo - initializes Info struct
 * @info: struct address
 */
void clearInfo(Info *info)
{
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

/**
 * setInfo - initializes Info struct
 * @info: struct address
 * @av: argument vector
 */
void setInfo(Info *info, char **av)
{
    int i = 0;

    info->fname = av[0];
    if (info->arg)
    {
        info->argv = strtow(info->arg, " \t");
        if (!info->argv)
        {
            info->argv = malloc(sizeof(char *) * 2);
            if (info->argv)
            {
                info->argv[0] = strdup(info->arg);
                info->argv[1] = NULL;
            }
        }
        for (i = 0; info->argv && info->argv[i]; i++)
            ;
        info->argc = i;

        replaceAlias(info);
        replaceVars(info);
    }
}

/**
 * freeInfo - frees Info struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void freeInfo(Info *info, int all)
{
    ffree(info->argv);
    info->argv = NULL;
    info->path = NULL;
    if (all)
    {
        if (!info->cmdBuf)
            free(info->arg);
        if (info->env)
            freeList(&(info->env));
        if (info->history)
            freeList(&(info->history));
        if (info->alias)
            freeList(&(info->alias));
        ffree(info->environ);
        info->environ = NULL;
        bfree((void **)info->cmdBuf);
        if (info->readFd > 2)
            close(info->readFd);
        putchar(BUF_FLUSH);
    }
}
