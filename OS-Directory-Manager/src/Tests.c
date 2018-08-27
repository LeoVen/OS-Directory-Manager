/**
 * @file Tests.c
 *
 * @author Leonardo Vencovsky       (https://github.com/LeoVen)
 * @author Eduardo Vencovsky        (https://github.com/eduvencovsky)
 * @author Guilherme Pinazza        (https://github.com/pinazza)
 * @author Erick Domingos Modenez
 *
 * @date 18/08/2018
 *
 * @brief Tests
 *
 */

#include "User.h"
#include "UserDynamicArray.h"
#include "Directory.h"
#include "DirectoryDynamicArray.h"
#include "Core.h"

int SINGLE_TESTS(void)
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

	st = usr_make(&user, name, full_name, password, 0);

	if (st != DS_OK)
		return st;

	usr_display(user);

	Directory *dir;

	String *dir_name;

	st = str_make(&dir_name, "/");

	if (st != DS_OK)
		return st;

	st = dir_make(&dir, NULL, user, dir_name);

	if (st != DS_OK)
		return st;

	dir_display(dir);

	dir_delete(&dir);
	usr_delete(&user);
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
			"namemisspelledev", "gravity123", "jointhed4rkside",
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
	st = udar_init(&users);

	if (st != DS_OK)
		return st;

	User *user;

	for (i = 0; i < 12; i++)
	{
		st = usr_make(&user, names[i], full_names[i], passwords[i], i);

		if (st != DS_OK)
			return st;

		st = udar_insert_back(users, user);

		if (st != DS_OK)
			return st;

		user = NULL;
	}

	udar_display(users);

	udar_remove_at(users, 3, &user);

	usr_delete(&user);

	udar_remove_at(users, 3, &user);

	usr_delete(&user);

	udar_display_inline(users);

	udar_delete(&users);

	return 0;
}

int DIRECTORY_ARRAY_TESTS(void)
{
	Status st = 0;
	size_t i;

	char *n[12] = { "Alan", "John", "John", "Albert", "Daenerys", "George",
		"Leonhard", "Isaac", "Anakin", "Carl", "Arthur", "Edgar" };
	String *names[12];

	char *fn[12] = { "Alan Turing", "John Snow", "John von Neumann",
		"Albert Einstein", "Daenerys Targaryen", "George Lucas",
		"Leonhard Euler", "Isaac Newton", "Anakin Skywalker",
		"Carl Friedrich Gauss", "Sir Arthur Conan Doyle",
		"Edgar Allan Poe" };
	String *full_names[12];

	char *p[12] = { "alan@computers", "IKnowNothing", "architecturewins",
		"fatpeoplehavemoreenergy", "burningeverything", "darthvaderwins",
		"namemisspelledev", "gravity123", "jointhed4rkside",
		"normaldistribution", "letsinvestigate", "haventreadyet" };
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
	st = udar_init(&users);

	if (st != DS_OK)
		return st;

	User *user;

	for (i = 0; i < 12; i++)
	{
		st = usr_make(&user, names[i], full_names[i], passwords[i], i);

		if (st != DS_OK)
			return st;

		st = udar_insert_back(users, user);

		if (st != DS_OK)
			return st;

		user = NULL;
	}

	// Now with 12 users, make 12 directories

	char *d[12] = {"bin", "ect", "dev", "boot", "home", "opt", "srv", "tmp", "proc", "mnt", "lib", "sbin"};

	String *dir_names[12];

	for (i = 0; i < 12; i++)
	{
		st = str_make(&(dir_names[i]), d[i]);

		if (st != DS_OK)
			return st;
	}

	DirectoryDynamicArray *directories;

	st = ddar_init(&directories);

	if (st != DS_OK)
		return st;

	// Root
	String *root_d, *root_n, *root_fn, *root_pswd;

	st += str_make(&root_d, "/");          // Rot directory name
	st += str_make(&root_n, "root");       // Root name
	st += str_make(&root_fn, "Root Toor"); // Root full name
	st += str_make(&root_pswd, "toor");    // Root password

	if (st != DS_OK)
		return st;

	Directory *dir, *root;

	// Making root
	st = usr_make(&user, root_n, root_fn, root_pswd, 0);

	if (st != DS_OK)
		return st;

	// Making root dir
	st = dir_make(&dir, NULL, user, root_d);

	if (st != DS_OK)
		return st;

	// Inserting root in user list
	st = udar_insert_back(users, user);

	if (st != DS_OK)
		return st;

	// Inserting root dir in dir list
	st = ddar_insert_back(directories, dir);

	root = dir; // Just to keep a reference in the for loop

	dir = NULL;

	// i = 1 to skip first user (root)
	for (i = 0; i < 12; i++)
	{
		st = dir_make(&dir, root, users->buffer[i], dir_names[i]);

		if (st != DS_OK)
			return st;

		st = ddar_insert_back(directories, dir);

		if (st != DS_OK)
			return st;

		dir = NULL;
	}

	udar_display(users);
	ddar_display(directories);

	udar_delete(&users);
	ddar_delete(&directories);

	return 0;
}