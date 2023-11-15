/**
 * myMemset - fills memory with a constant byte
 * @str: the pointer to the memory area
 * @ch: the byte to fill *str with
 * @size: the number of bytes to be filled
 *
 * Return: a pointer to the memory area str
 */
char *myMemset(char *str, char ch, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
		str[i] = ch;
	return str;
}

/**
 * freeStringArray - frees an array of strings
 * @strArray: the array of strings to be freed
 */
void freeStringArray(char **strArray)
{
	char **ptr = strArray;

	if (!strArray)
		return;
	while (*strArray)
		free(*strArray++);
	free(ptr);
}

/**
 * myRealloc - reallocates a block of memory
 * @ptr: pointer to the previous allocated block
 * @oldSize: byte size of the previous block
 * @newSize: byte size of the new block
 *
 * Return: pointer to the reallocated block
 */
void *
