/**
 * @file OS-Directory-Manager.c
 *
 * @author Leonardo Vencovsky       (https://github.com/LeoVen)
 * @author Eduardo Vencovsky        (https://github.com/eduvencovsky)
 * @author Guilherme Pinazza        (https://github.com/pinazza)
 * @author Erick Domingos Modenez
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
#include "FileHandler.h"

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

	//global_id++;

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

	// Loading
	///////////////////////////////////////////////////////////////////////////
	st = f_load_usr(global_user_list);

	if (st != DS_OK)
	{
		print_status_repr(st);
		udar_display_inline(global_user_list);
		_getch();
	}

	st = f_load_dir(global_dir_list, global_user_list);

	if (st != DS_OK)
	{
		print_status_repr(st);
		ddar_display_inline(global_dir_list);
		_getch();
	}
	///////////////////////////////////////////////////////////////////////////

	// change global_id according to user global list size
	size_t i;
	for (i = 0; i < global_user_list->size; i++)
	{
		if (global_user_list->buffer[i]->id > global_id)
			global_id = global_user_list->buffer[i]->id;
	}
	// Next
	global_id++;

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

	// User input, command 1 and parameter
	String *input, *cmd1, *cmd2, *str_copy;

	// Temporary variables (create/delete User/Directory)
	User *user;
	Directory *directory;

	size_t index;

	st += str_init(&input);
	st += str_init(&cmd1);
	st += str_init(&cmd2);

	if (st != DS_OK)
		return st;

	// This flag is used to prevent the root user from making directories inside
	// other user's home
	bool root_flag;

	while (ok)
	{
		// Login as root first or as any loaded user
		while (!logged_in)
		{
			logged_in = shandler_login(global_dir_list, global_user_list, &curr_user, &curr_dir);
		}

		st = shandler_make_prompt(curr_user, curr_dir, line);

		if (st != DS_OK)
			return st;

		// Set flag if root
		root_flag = curr_user->root;

		printf("%s ", line->buffer);

		st = shandler_getline(input);
		
		if (st != DS_OK)
			return st;

		// Parsing input
		st = shandler_parse_input(input, cmd1, cmd2);

		if (st != DS_OK)
			return st;
		
		// Execute command ////////////////////////////////////////////////////
		// System-related functions ///////////////////////////////////////////
		if (str_eqstr(cmd1, "poweroff"))
		{
			// exit (only root is allowed)
			if (str_equals(curr_user->name, root_n))
				ok = false;
			else
			{
				printf("Insufficient privileges\n");
			}
		}
		else if (str_eqstr(cmd1, "logout"))
		{
			logged_in = false;
		}
		else if (str_eqstr(cmd1, "date"))
		{
			String *date;

			st = shandler_current_date(&date);

			if (st != DS_OK)
				return st;

			printf("%s\n", date->buffer);

			str_delete(&date);
		}
		else if (str_eqstr(cmd1, "time"))
		{
			String *time;

			st = shandler_current_hour(&time);

			if (st != DS_OK)
				return st;

			printf("%s\n", time->buffer);

			str_delete(&time);
		}
		// User-related functions /////////////////////////////////////////////
		else if (str_eqstr(cmd1, "adduser"))
		{
			if (curr_user->root)
			{
				if (cmd2->len == 0)
				{
					printf("Invalid user name\n");
				}
				else if (udar_contains(global_user_list, cmd2))
				{
					printf("User already exists\n");
				}
				else if (ddar_contains(root_dir->children, cmd2))
				{
					// Because there is a directory with the same name as the user
					printf("Could not add new user\n");
				}
				else
				{
					st = usr_input(&user, cmd2, &global_id);

					if (st != DS_OK)
						return st;
					
					// Make user
					st = udar_insert_back(global_user_list, user);

					if (st != DS_OK)
						return st;

					// Copy of user name
					st = str_init(&str_copy);

					if (st != DS_OK)
						return st;

					st = str_append(str_copy, user->name);

					if (st != DS_OK)
						return st;

					// Also make home directory
					st = dir_make(&directory, root_dir, user, str_copy);

					if (st != DS_OK)
						return st;

					// Insert directory to global list
					st = ddar_insert_back(global_dir_list, directory);

					if (st != DS_OK)
						return st;

					// Insert directory to root children
					st = ddar_insert_back(root_dir->children, directory);

					if (st != DS_OK)
						return st;

					user = NULL;
					directory = NULL;
					str_copy = NULL;
				}
			}
			else
			{
				printf("Insufficient privileges\n");
			}
		}
		else if (str_eqstr(cmd1, "deluser"))
		{
			if (curr_user->root)
			{
				if (cmd2->len == 0)
				{
					printf("Invalid user name\n");
				}
				else if (str_equals(root_n, cmd2))
				{
					printf("Can't delete root\n");
				}
				else
				{
					st = udar_find(global_user_list, cmd2, &index);

					if (st != DS_OK)
					{
						if (st != DS_ERR_NOT_FOUND)
							return st;

						printf("User not found\n");
					}
					else
					{
						st = udar_remove_at(global_user_list, index, &user);

						if (st != DS_OK)
							return st;

						// Delete every directory of deleted owner first
						// First delete from root child list
						st = ddar_find(root_dir->children, user->name, &index);

						if (st != DS_OK)
							return st;

						// Unlink directory reference
						// It will later be deleted in the for loop
						st = ddar_remove_at(root_dir->children, index, &directory);

						if (st != DS_OK)
							return st;

						for (index = 0; index < global_dir_list->size; index++)
						{
							if (str_equals(global_dir_list->buffer[index]->owner->name, user->name))
							{
								st = ddar_remove_at(global_dir_list, index, &directory);

								if (st != DS_OK)
									return st;

								st = dir_delete(&directory);

								if (st != DS_OK)
									return st;
							}
						}

						st = usr_delete(&user);

						if (st != DS_OK)
							return st;
					}
				}
			}
			else
			{
				printf("Insufficient privileges\n");
			}
		}
		else if (str_eqstr(cmd1, "lock"))
		{
			if (curr_user->root)
			{
				if (cmd2->len == 0)
				{
					printf("Invalid user name\n");
				}
				else if (str_equals(root_n, cmd2))
				{
					printf("Can't lock root\n");
				}
				else
				{
					st = udar_find(global_user_list, cmd2, &index);

					if (st != DS_OK)
					{
						if (st != DS_ERR_NOT_FOUND)
							return st;

						printf("User not found\n");
					}
					else
					{
						global_user_list->buffer[index]->locked = true;
					}
				}
			}
			else
			{
				printf("Insufficient privileges\n");
			}
		}
		else if (str_eqstr(cmd1, "unlock"))
		{
			if (curr_user->root)
			{
				if (cmd2->len == 0)
				{
					printf("Invalid user name\n");
				}
				else
				{
					st = udar_find(global_user_list, cmd2, &index);

					if (st != DS_OK)
					{
						if (st != DS_ERR_NOT_FOUND)
							return st;

						printf("User not found\n");
					}
					else
					{
						global_user_list->buffer[index]->locked = false;
					}
				}
			}
			else
			{
				printf("Insufficient privileges\n");
			}
		}
		else if (str_eqstr(cmd1, "id"))
		{
			st = udar_find(global_user_list, cmd2, &index);

			if (st != DS_OK)
			{
				if (st != DS_ERR_NOT_FOUND)
					return st;

				printf("User not found\n");
			}

			if (curr_user->root)
				usr_display(global_user_list->buffer[index]);
			else
				usr_display_noroot(global_user_list->buffer[index]);
		}
		else if (str_eqstr(cmd1, "listuser"))
		{
			if (curr_user->root)
			{
				udar_display_inline(global_user_list);
				printf("\n");
			}
			else
				printf("Insufficient privileges\n");
		}
		// Directory-related functions ////////////////////////////////////////
		else if (str_eqstr(cmd1, "mkdir"))
		{
			if (cmd2->len == 0)
			{
				printf("Invalid directory name\n");
			}
			else if (ddar_contains(curr_dir->children, cmd2))
			{
				printf("Directory already exists\n");
			}
			else if (str_eqstr(cmd2, "/"))
			{
				printf("Invalid directory name\n");
			}
			else if (root_flag && !str_equals(curr_dir->owner->name, root_n))
			{
				printf("Operation not allowed\n");
			}
			else
			{
				// Add new directory to global list and to the current directory list
				st = dir_input(global_dir_list, &directory, curr_dir, cmd2, curr_user);

				if (st != DS_OK)
					return st;
			}
		}
		else if (str_eqstr(cmd1, "rmdir"))
		{
			if (cmd2->len == 0)
			{
				printf("Invalid directory name\n");
			}
			else if (!ddar_contains(curr_dir->children, cmd2))
			{
				printf("Directory not found\n");
			}
			else
			{
				// Find directory position from current directory list
				st = ddar_find(curr_dir->children, cmd2, &index);

				if (st != DS_OK)
					return st;
				
				// Directory can't be empty
				if (curr_dir->children->buffer[index]->children->size != 0)
				{
					printf("Directory is not empty\n");
				}
				else
				{
					// Remove from current directory list
					st = ddar_remove_at(curr_dir->children, index, &directory);

					if (st != DS_OK)
						return st;

					// Find from global directory list
					st = ddar_find(global_dir_list, cmd2, &index);

					if (st != DS_OK)
						return st;

					// Remove from global list
					st = ddar_remove_at(global_dir_list, index, &directory);

					if (st != DS_OK)
						return st;

					// Delete
					st = dir_delete(&directory);

					if (st != DS_OK)
						return st;
				}
			}
		}
		else if (str_eqstr(cmd1, "cd"))
		{
			if (cmd2->len == 0)
			{
				if (curr_user->root)
				{
					// Root goes all the way up to /
					while (curr_dir->parent != NULL)
					{
						curr_dir = curr_dir->parent;
					}
				}
				else
				{
					// Common users go all the way up to /home
					while (!str_equals(curr_dir->name, curr_user->name))
					{
						curr_dir = curr_dir->parent;
					}
				}
			}
			else
			{
				if (str_eqstr(cmd2, ".."))
				{
					// Go to parent
					if (curr_user->root)
					{
						if (curr_dir->parent != NULL)
							curr_dir = curr_dir->parent;
					}
					else
					{
						// Common users can't go past their home directory
						if (!str_equals(curr_dir->name, curr_user->name))
						{
							curr_dir = curr_dir->parent;
						}
					}
				}
				else
				{
					// Find directory position from current directory list
					st = ddar_find(curr_dir->children, cmd2, &index);

					if (st != DS_OK)
					{
						if (st != DS_ERR_NOT_FOUND)
							return st;

						printf("Directory not found\n");
					}
					else
						curr_dir = curr_dir->children->buffer[index];
				}
			}
		}
		else if (str_eqstr(cmd1, "pwd"))
		{
			String *print;

			st = str_init(&print);

			if (st != DS_OK)
				return st;

			Directory *dir = curr_dir;

			if (str_equals(curr_user->name, root_n))
			{
				// If root go all the way up to /
				while (dir->parent != NULL)
				{
					st += str_prepend(print, dir->name);
					if (!str_eqstr(dir->name, "/"))
						st += str_push_char_front(print, '/');

					if (st != DS_OK)
						return st;

					dir = dir->parent;

				}

				if (print->len == 0)
				{
					printf("\t/\n");
				}
				else
				{
					printf("\t%s\n", print->buffer);
				}

			}
			else
			{
				// If root go all the way up to /
				while (!str_equals(curr_user->name, dir->name))
				{
					st += str_prepend(print, dir->name);
					if (!str_eqstr(dir->name, "/"))
						st += str_push_char_front(print, '/');

					if (st != DS_OK)
						return st;

					dir = dir->parent;
				}

				st += str_push_char_front(print, 'e');
				st += str_push_char_front(print, 'm');
				st += str_push_char_front(print, 'o');
				st += str_push_char_front(print, 'h');
				st += str_push_char_front(print, '/');

				if (print->len == 0)
				{
					printf("\t/home\n");
				}
				else
				{
					printf("\t%s\n", print->buffer);
				}
			}

			str_delete(&print);
		}
		else if (str_eqstr(cmd1, "ls"))
		{
			if (str_eqstr(cmd2, "-l"))
			{
				st = ddar_display_inline(curr_dir->children);
			}
			else
			{
				for (index = 0; index < curr_dir->children->size; index++)
				{
					printf("%s\t", curr_dir->children->buffer[index]->name->buffer);
				}
				printf("\n");
			}

			if (st != DS_OK)
				return st;
		}
		// Miscellaneous //////////////////////////////////////////////////////
		else if (str_eqstr(cmd1, "help"))
		{
			help();
		}
		else if (str_eqstr(cmd1, "whoami"))
		{
			printf("%s\n", curr_user->name->buffer);
		}
		else if (str_eqstr(cmd1, "clear"))
		{
			CLEAR_SCREEN;
		}
		else if (str_eqstr(cmd1, "echo"))
		{
			printf("%s\n", cmd2->buffer);
		}
		else if (str_eqstr(cmd1, "copyright"))
		{
			copyright();
		}
		else
		{
			printf("Command not found\n");
		}

		// Reset
		st = 0;
		st += str_erase(&line);
		st += str_erase(&input);
		st += str_erase(&cmd1);
		st += str_erase(&cmd2);

		if (st != DS_OK)
			return st;
	}

	// Saving
	///////////////////////////////////////////////////////////////////////////
	f_save_dir(global_dir_list);
	f_save_usr(global_user_list);
	///////////////////////////////////////////////////////////////////////////

	str_delete(&line);
	str_delete(&input);
	str_delete(&cmd1);
	str_delete(&cmd2);

	st += ddar_delete(&global_dir_list);
	st += udar_delete(&global_user_list);

	if (st != DS_OK)
		return st;

	final_shutdown();

	printf("\n\n");
	return 0;
}
