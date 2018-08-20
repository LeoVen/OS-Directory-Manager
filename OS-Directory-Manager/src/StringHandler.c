/**
 * @file StringHandler.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @author Eduardo Vencovsky  (https://github.com/eduvencovsky)
 * @author Guilherme Pinazza  (https://github.com/pinazza)
 *
 * @date 18/08/2018
 *
 * @brief Source file for Handling Strings
 *
 */

#include "StringHandler.h"


Status shandler_getline(String *string)
{
	char c = ' ';

	Status st;

	while (c != '\n')
	{
		c = getchar();

		if (c != '\n')
		{
			st = str_push_char_back(string, c);

			if (st != DS_OK)
				return st;
		}
	}

	return DS_OK;
}

Status shandler_current_time(String **curr_time)
{
	time_t now;
	time(&now);

	struct tm ct;
	localtime_s(&ct, &now);

	char *str = malloc(sizeof(char) * 20);

	strftime(str, 20, "%x %X", &ct);

	Status st = str_make(curr_time, str);

	if (st != DS_OK)
		return st;

	free(str);

	return DS_OK;
}

Status shandler_current_date(String **curr_date)
{
	time_t now;
	time(&now);

	struct tm ct;
	localtime_s(&ct, &now);

	char *str = malloc(sizeof(char) * 20);

	strftime(str, 20, "%x", &ct);

	Status st = str_make(curr_date, str);

	if (st != DS_OK)
		return st;

	free(str);

	return DS_OK;
}

Status shandler_current_hour(String **curr_hour)
{
	time_t now;
	time(&now);

	struct tm ct;
	localtime_s(&ct, &now);

	char *str = malloc(sizeof(char) * 20);

	strftime(str, 20, "%X", &ct);

	Status st = str_make(curr_hour, str);

	if (st != DS_OK)
		return st;

	free(str);

	return DS_OK;
}

bool shandler_login(UserDynamicArray *users, User **curr_user)
{
	CLEAR_SCREEN;

	String *name, *password;

	Status st = 0;

	st += str_init(&name);
	st += str_init(&password);

	if (st != DS_OK)
		goto error;

	char c;

	printf("+--------------------------------------------------------------------------------+\n");
	printf("|                                                                                |\n");
	printf("|                                Directory Manager                               |\n");
	printf("|                                                                                |\n");
	printf("+--------------------------------------------------------------------------------+\n");
	printf("\n");
	printf("\tUser name : ");
	st += shandler_getline(name);
	printf("\n");
	printf("\tPassword  : ");
	st += shandler_getline(password);
	printf("\n");

	if (st != DS_OK)
		goto error;

	size_t i;
	st = udar_find(users, name, &i);

	if (st != DS_OK)
	{
		if (st != DS_ERR_NOT_FOUND)
			goto error;

		printf("Invalid user or password...");

		c = getchar();

		str_delete(&name);
		str_delete(&password);

		return false;
	}

	if (users->buffer[i]->locked)
	{
		printf("User locked...");

		c = getchar();

		str_delete(&name);
		str_delete(&password);

		return false;
	}

	if (str_equals(users->buffer[i]->password, password))
	{
		*curr_user = users->buffer[i];

		str_delete(&name);
		str_delete(&password);

		return true;
	}
	else
	{
		str_delete(&name);
		str_delete(&password);

		printf("Invalid user or password...");

		c = getchar();

		return false;
	}

error:
	print_status_repr(st);

	str_delete(&name);
	str_delete(&password);

	return false;
}

Status shandler_make_prompt(User *curr_user, Directory *curr_dir, String *result)
{
	if (curr_user == NULL || curr_dir == NULL || result == NULL)
		return DS_ERR_NULL_POINTER;

	String *m_name, *c_dir, *root_dir_name;

	Status st = str_make(&m_name, MACHINE_NAME);

	if (st != DS_OK)
		return st;

	st = str_init(&c_dir);

	if (st != DS_OK)
		return st;

	st += str_append(result, curr_user->name);

	st += str_push_char_back(result, '@');
	
	st += str_append(result, m_name);

	st += str_push_char_back(result, ':');

	if (st != DS_OK)
		return st;

	// Find root path

	Directory *scan = curr_dir;

	// Don't append if current dir is / (root)
	st = str_make(&root_dir_name, "/");

	if (st != DS_OK)
		return st;

	// While scan hasn't reached root folder
	while (scan != NULL)
	{
		if (!str_equals(scan->name, root_dir_name))
			st += str_append(c_dir, scan->name);

		st += str_push_char_front(c_dir, '/');

		if (st != DS_OK)
			return st;

		scan = scan->parent;
	}

	st = str_append(result, c_dir);

	if (st != DS_OK)
		return st;

	char c = (curr_user->root) ? '#' : '$';

	st = str_push_char_back(result, c);

	if (st != DS_OK)
		return st;

	str_delete(&root_dir_name);
	str_delete(&m_name);
	str_delete(&c_dir);

	return DS_OK;
}

Status shandler_parse_input(String *input, String *cmd1, String *cmd2)
{
	char c = 'A';
	Status st;
	bool param = false;

	size_t i;
	for (i = 0; i < input->len; i++)
	{
		c = input->buffer[i];

		if (c == ' ' && !param)
		{
			param = true;

			continue;
		}

		if (!param)
		{
			if (c != ' ' || c != '\n')
				st = str_push_char_back(cmd1, c);
		}
		else
		{
			if (c != '\n')
				st = str_push_char_back(cmd2, c);
		}

		if (st != DS_OK)
			return st;
	}

	return DS_OK;
}