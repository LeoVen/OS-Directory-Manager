/**
 * @file OS-Directory-Manager.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @author Eduardo Vencovsky  (https://github.com/eduvencovsky)
 * @author Guilherme Pinazza  (https://github.com/pinazza)
 *
 * @date 17/08/2018
 *
 * @brief Entry point for project
 *
 */

#include "User.h"
#include "UserDynamicArray.h"
#include "Core.h"

int USER_ARRAY_TESTS(void);

int main()
{
	// Checking memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

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

	st = usr_make(&user, name, full_name, password, 0);

	if (st != DS_OK)
		return st;

	usr_display(user);

	usr_delete(&user);

	printf("\n ---------- ---------- TEST ---------- ---------- \n\n");

	print_status_repr(USER_ARRAY_TESTS());

	return 0;
}

int USER_ARRAY_TESTS(void)
{
	Status st = 0;
	size_t i;

	char *n[12] = { "Alan", "John", "John", "Albert", "Daenerys", "George",
			"Leonhard", "Isaac", "Anakin", "Carl", "Arthur", "Edgar"};
	String *names[12];

	char *fn[12] = { "Alan Turing", "John Snow", "John von Neumann",
			"Albert Einstein", "Daenerys Targaryen", "George Lucas",
			"Leonhard Euler", "Isaac Newton", "Anakin Skywalker",
			"Carl Friedrich Gauss", "Sir Arthur Conan Doyle",
			"Edgar Allan Poe"};
	String *full_names[12];

	char *p[12] = {"alan@computers", "IKnowNothing", "architecturewins",
			"fatpeoplehavemoreenergy", "burningeverything", "darthvaderwins",
			"namemisspelledeverytime", "gravity123", "jointhed4rkside",
			"normaldistribution", "letsinvestigate", "haventreadyet"};
	String *passwords[12];

	for (i = 0; i < 12; i++)
	{
		st += str_make(&(names[i]), n[i]);
		st += str_make(&(full_names[i]), fn[i]);
		st += str_make(&(passwords[i]), p[i]);
	}

	if (st != DS_OK)
		return st;

	UserDynamicArray *users;
	st = dar_init(&users);

	if (st != DS_OK)
		return st;

	User *user;

	for (i = 0; i < 12; i++)
	{
		st = usr_make(&user, names[i], full_names[i], passwords[i], i);

		if (st != DS_OK)
			return st;

		st = dar_insert_back(users, user);

		if (st != DS_OK)
			return st;

		user = NULL;
	}

	dar_display(users);

	dar_delete(&users);

	return 0;
}

/**
 *
 * Very important!
 *
	while (c != '\n')
	{
	c = getchar();

	if (c != '\n')
		str_push_char_back(name, c);
	}
 */