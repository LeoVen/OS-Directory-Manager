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