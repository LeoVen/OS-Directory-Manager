/**
* @file DirectoryManager.c
*
* @author Leonardo Vencovsky (https://github.com/LeoVen)
* @date 17/08/2018
*
* @brief Entry point for project
*
*/

#include "User.h"
#include "UserDynamicArray.h"
#include "Core.h"

int main()
{
	Status st = 0;

	User *user;

	String *name;
	String *full_name;
	String *password;

	st += str_make(&name, "root");
	st += str_make(&full_name, "Overlord");
	st += str_make(&password, "toor");

	if (st != DS_OK)
	{
		printf("\n\nERROR\n\n");
		return -1;
	}

	st = usr_make(&user, &name, &full_name, &password, 0);

	if (st != DS_OK)
		return st;

	usr_display(user);

	usr_delete(&user);

	char c = 0;

	String *test;

	str_init(&test);

	while (c != '\n')
	{
		c = getchar();

		if (c != '\n')
			str_push_char_back(test, c);
	}

	str_display(test);

	str_delete(&test);

	return 0;
}

