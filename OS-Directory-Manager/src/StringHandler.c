/**
 * @file StringHandler.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @author Eduardo Vencovsky  (https://github.com/eduvencovsky)
 * @author Guilherme Pinazza  (https://github.com/pinazza)
 *
 * @date 18/08/2018
 *
 * @brief Source file for String Hanlders
 *
 */

#include "StringHandler.h"

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

bool shandler_login(UserDynamicArray *users)
{
	String *name, *password;

	Status st = 0;

	st += str_init(&name);
	st += str_init(&password);

	if (st != DS_OK)
		goto error;

	printf("\nUser name : ");
	st += shandler_getline(name);

	printf("Password  : ");
	st += shandler_getline(password);

	if (st != DS_OK)
		goto error;

	size_t i;
	st = udar_find(users, name, &i);

	if (st != DS_OK)
	{
		if (st != DS_ERR_NOT_FOUND)
			goto error;

		printf("\nUser not found!");

		str_delete(&name);
		str_delete(&password);

		return false;
	}

	if (str_equals(users->buffer[i]->password, password))
	{
		str_delete(&name);
		str_delete(&password);

		return true;
	}
	else
	{
		str_delete(&name);
		str_delete(&password);

		printf("\nInvalid password");

		return false;
	}

error:
	print_status_repr(st);

	str_delete(&name);
	str_delete(&password);

	return false;
}