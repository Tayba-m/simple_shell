/**
 * stringLength - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */
int stringLength(const char *str)
{
	int length = 0;

	if (!str)
		return 0;

	while (*str++)
		length++;
	return length;
}

/**
 * stringCompare - performs lexicographic comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative if str1 < str2, positive if str1 > str2, zero if str1 == str2
 */
int stringCompare(const char *str1, const char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return 0;
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * startsWith - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
const char *startsWith(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
			return NULL;
	}
	return haystack;
}

/**
 * stringConcatenate - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *stringConcatenate(char *dest, const char *src)
{
	char *result = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return result;
}
