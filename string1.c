/**
 * stringCopy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *stringCopy(char *dest, const char *src)
{
	int i = 0;

	if (dest == src || src == NULL)
		return dest;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return dest;
}

/**
 * stringDuplicate - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *stringDuplicate(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return NULL;
	while (str[length])
		length++;
	ret = malloc((length + 1) * sizeof(char));
	if (!ret)
		return NULL;
	for (int i = 0; i <= length; i++)
		ret[i] = str[i];
	return ret;
}

/**
 * printString - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void printString(const char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * writeCharacter - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int writeCharacter(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return 1;
}
