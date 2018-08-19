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

int main()
{
	// Checking memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	DIRECTORY_ARRAY_TESTS();
	USER_ARRAY_TESTS();
	SINGLE_TESTS();

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