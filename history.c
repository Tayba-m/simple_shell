#include "shell.h"

/**
 * getHistoryFile - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */
char *getHistoryFile(Info *info)
{
    char *buf, *dir;

    dir = getenv(info, "HOME=");
    if (!dir)
        return NULL;
    buf = malloc(sizeof(char) * (strlen(dir) + strlen(HIST_FILE) + 2));
    if (!buf)
        return NULL;
    buf[0] = '\0';
    strcpy(buf, dir);
    strcat(buf, "/");
    strcat(buf, HIST_FILE);
    return buf;
}

/**
 * writeHistory - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int writeHistory(Info *info)
{
    ssize_t fd;
    char *filename = getHistoryFile(info);
    ListNode *node = NULL;

    if (!filename)
        return -1;

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);
    if (fd == -1)
        return -1;
    for (node = info->history; node; node = node->next)
    {
        putsToFileDescriptor(node->str, fd);
        putCharToFileDescriptor('\n', fd);
    }
    putCharToFileDescriptor(BUF_FLUSH, fd);
    close(fd);
    return 1;
}

/**
 * readHistory - reads history from file
 * @info: the parameter struct
 *
 * Return: histCount on success, 0 otherwise
 */
int readHistory(Info *info)
{
    int i, last = 0, lineCount = 0;
    ssize_t fd, rdLen, fileSize = 0;
    struct stat st;
    char *buf = NULL, *filename = getHistoryFile(info);

    if (!filename)
        return 0;

    fd = open(filename, O_RDONLY);
    free(filename);
    if (fd == -1)
        return 0;
    if (!fstat(fd, &st))
        fileSize = st.st_size;
    if (fileSize < 2)
        return 0;
    buf = malloc(sizeof(char) * (fileSize + 1));
    if (!buf)
        return 0;
    rdLen = read(fd, buf, fileSize);
    buf[fileSize] = '\0';
    if (rdLen <= 0)
        return (free(buf), 0);
    close(fd);
    for (i = 0; i < fileSize; i++)
    {
        if (buf[i] == '\n')
        {
            buf[i] = '\0';
            buildHistoryList(info, buf + last, lineCount++);
            last = i + 1;
        }
    }
    if (last != i)
        buildHistoryList(info, buf + last, lineCount++);
    free(buf);
    info->histCount = lineCount;
    while (info->histCount-- >= HIST_MAX)
        deleteNodeAtIndex(&(info->history), 0);
    renumberHistory(info);
    return info->histCount;
}

/**
 * buildHistoryList - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @lineCount: the history line count, histCount
 *
 * Return: Always 0
 */
int buildHistoryList(Info *info, char *buf, int lineCount)
{
    ListNode *node = NULL;

    if (info->history)
        node = info->history;
    addNodeEnd(&node, buf, lineCount);

    if (!info->history)
        info->history = node;
    return 0;
}

/**
 * renumberHistory - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histCount
 */
int renumberHistory(Info *info)
{
    ListNode *node = info->history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }
    return (info->histCount = i);
}
