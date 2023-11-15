#include "shell.h"

/**
 * myStrncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the amount of characters to be copied
 * Return: the concatenated string
 */
char *myStrncpy(char *dest, const char *src, size_t n)
{
    size_t i;
    char *s = dest;

    for (i = 0; i < n - 1 && src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }

    if (i < n)
    {
        for (; i < n; i++)
        {
            dest[i] = '\0';
        }
    }

    return s;
}

/**
 * myStrncat - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: the amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *myStrncat(char *dest, const char *src, size_t n)
{
    size_t i, j;
    char *s = dest;

    for (i = 0; dest[i] != '\0'; i++)
    {
        ;
    }

    for (j = 0; src[j] != '\0' && j < n; j++)
    {
        dest[i + j] = src[j];
    }

    if (j < n)
    {
        dest[i + j] = '\0';
    }

    return s;
}

/**
 * myStrchr - locates a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 * Return: (s) a pointer to the memory area s
 */
char *myStrchr(const char *s, int c)
{
    while (*s != '\0')
    {
        if (*s == c)
        {
            return (char *)s;
        }
        s++;
    }

    if (c == '\0')
    {
        return (char *)s;
    }

    return NULL;
}
