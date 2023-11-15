/**
 * getListLength - determines length of linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t getListLength(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		head = head->next;
		count++;
	}
	return count;
}

/**
 * listToStrings - returns an array of strings from the list nodes' str field
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **listToStrings(list_t *head)
{
	list_t *node = head;
	size_t size = getListLength(head), i, j;
	char **strings;
	char *str;

	if (!head || !size)
		return NULL;

	strings = malloc(sizeof(char *) * (size + 1));
	if (!strings)
		return NULL;

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(sizeof(char) * (_strlen(node->str) + 1));
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strings[j]);
			free(strings);
			return NULL;
		}

		str = _strcpy(str, node->str);
		strings[i] = str;
	}
	strings[i] = NULL;
	return strings;
}

/**
 * printList - prints all elements of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t printList(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(convertNumber(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}
	return count;
}

/**
 * findNodeStartsWith - returns node whose string starts with prefix
 * @head: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: matching node or NULL
 */
list_t *findNodeStartsWith(list_t *head, char *prefix, char c)
{
	char *p = NULL;

	while (head)
	{
		p = startsWith(head->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return head;
		head = head->next;
	}
	return NULL;
}

/**
 * getNodeIndex - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t getNodeIndex(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return index;
		head = head->next;
		index++;
	}
	return -1;
}
