/**
 * isCommand - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int isCommand(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return 0;

	if (st.st_mode & S_IFREG)
	{
		return 1;
	}
	return 0;
}

/**
 * duplicateCharacters - duplicates characters
 * @pathString: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicateCharacters(char *pathString, int start, int stop)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathString[i] != ':')
			buffer[k++] = pathString[i];
	buffer[k] = '\0';
	return buffer;
}

/**
 * findPath - finds this command in the PATH string
 * @info: the info struct
 * @pathString: the PATH string
 * @command: the command to find
