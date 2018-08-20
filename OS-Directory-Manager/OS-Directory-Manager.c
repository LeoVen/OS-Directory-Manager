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
#include "Directory.h"
#include "DirectoryDynamicArray.h"
#include "Core.h"
#include "StringHandler.h"

int main()
{
	// Checking memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Global user id /////////////////////////////////////////////////////////
	size_t global_id = 0;

	///////////////////////////////////////////////////////////////////////////
	// Init arrays
	// Initializing main arrays that will hold all directory and user structure
	///////////////////////////////////////////////////////////////////////////
	DirectoryDynamicArray *global_dir_list;
	UserDynamicArray *global_user_list;

	Status st = 0;
	st += ddar_init(&global_dir_list);
	st += udar_init(&global_user_list);

	if (st != DS_OK)
		return st;
	// End of init arrays /////////////////////////////////////////////////////

	// Make root directory ////////////////////////////////////////////////////

	User *root_usr;
	Directory *root_dir;
	String *root_d, *root_n, *root_fn, *root_pswd;

	// These strings are deleted only after the user/directory list is deleted
	st += str_make(&root_d, "/");           // Rot directory name
	st += str_make(&root_n, "root");        // Root name
	st += str_make(&root_fn, "Super User"); // Root full name
	st += str_make(&root_pswd, "toor");     // Root password

	if (st != DS_OK)
		return st;

	// Making root
	st = usr_make(&root_usr, root_n, root_fn, root_pswd, global_id);

	if (st != DS_OK)
		return st;

	root_usr->root = true;

	global_id++;

	st = dir_make(&root_dir, NULL, root_usr, root_d);

	if (st != DS_OK)
		return st;

	// Adding root user and directory to their respective list

	st = udar_insert_back(global_user_list, root_usr);

	if (st != DS_OK)
		return st;

	st = ddar_insert_back(global_dir_list, root_dir);

	if (st != DS_OK)
		return st;

	// End of make root directory /////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	// Add load function
	// Where users and directories are loaded to the lists
	// global_id must be incremented as users are added
	///////////////////////////////////////////////////////////////////////////

	// Current directory
	Directory *curr_dir = root_dir;

	// Current user
	User *curr_user = root_usr;

	// Prompt string
	String *line;

	st = str_init(&line);

	if (st != DS_OK)
		return st;

	bool ok = true;
	bool logged_in = false;

	// User input
	String *input;

	st = str_init(&input);

	if (st != DS_OK)
		return st;

	while (ok)
	{
		// Login as root first or as any loaded user
		while (!logged_in)
		{
			logged_in = shandler_login(global_user_list, &curr_user);
		}

		st = shandler_make_prompt(curr_user, curr_dir, line);

		if (st != DS_OK)
			return st;

		printf("\n%s ", line->buffer);

		st = shandler_getline(input);
		
		if (st != DS_OK)
			return st;

		// TODO
		// Need to parse input first //////////////////////////////////////////
		
		// Execute command ////////////////////////////////////////////////////

		if (str_iscmd(input, "poweroff"))
		{
			// exit (only root is allowed)
			if (str_equals(curr_user->name, root_n))
				ok = false;
			else
			{
				printf("Insufficient privileges\n");
			}
		}
		else if (str_iscmd(input, "whoami"))
		{
			printf("%s", curr_user->name->buffer);
		}
		else if (str_iscmd(input, "clear"))
		{
			CLEAR_SCREEN;
		}
		else if (str_iscmd(input, "date"))
		{
			String *date;

			st = shandler_current_date(&date);

			if (st != DS_OK)
				return st;

			printf("%s", date->buffer);

			str_delete(&date);
		}
		else if (str_iscmd(input, "time"))
		{
			String *time;

			st = shandler_current_hour(&time);

			if (st != DS_OK)
				return st;

			printf("%s", time->buffer);

			str_delete(&time);
		}



		// Reset input
		st = str_erase(&input);

		if (st != DS_OK)
			return st;
	}

	///////////////////////////////////////////////////////////////////////////
	// Add save function
	///////////////////////////////////////////////////////////////////////////

	str_delete(&line);
	str_delete(&input);

	st += ddar_delete(&global_dir_list);
	st += udar_delete(&global_user_list);

	if (st != DS_OK)
		return st;

	final_shutdown();

	printf("\n\n");
	return 0;
}
