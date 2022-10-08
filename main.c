#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	mode_detection(char **argv);
void	get_payload(void);
char	**check_all(char **argv);
char 	*change_dll_name(char *dllname);
void	check_dirs(void);

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("ERROR: No arguments given...\n");
		return(0);
	}
	if (argc > 5)
	{
		printf("ERROR: Too many arguments...\n");
		return(0);
	}
	if (argv[1][0] != '-')
	{
		printf("ERROR: Invalid option...\n");
		return(0);
	}
	mode_detection(argv);
}

void	mode_detection(char **argv)
{
	char	*orig;
	char	**save;
	char	buf[10000];

	if(!strcmp(argv[1], "--get-payload") || !strcmp(argv[1], "-gp"))
		get_payload();
	else
	{
		save = check_all(argv);
		check_dirs();
		orig = save[0];
		save[0] = change_dll_name(save[0]);
		snprintf(buf, sizeof(buf), "cp %s generated/%s", orig, save[0]);
		system(buf);
		snprintf(buf, sizeof(buf), "cd generated && python3 ../scripts/script.py %s > ../defs/geng.def", save[0]);
		system(buf);
		snprintf(buf, sizeof(buf), "i686-w64-mingw32-gcc -shared -o generated/%s %s defs/geng.def -s", orig, save[1]);
		system(buf);
		printf("DLLs generated succesfully, check generated dir ;)\n");
		return ;
	}
}

void	get_payload(void)
{
	//char *tofile = "void payload(void)\n	{\n		//Write here your Payload...\n		}\n\n\n\nBOOL WINAPI\nDllMain (HANDLE hDll, DWORD dwReason, LPVOID lpReserved)\n{\n		switch (dwReason)\n{\n		case DLL_PROCESS_ATTACH:\n		payload();\n		break;\n	}\n		return TRUE;\n}";
	system("echo \"void payload(void)\n{\n	//Write here your Payload...\n}\n\n\n\nBOOL WINAPI\nDllMain (HANDLE hDll, DWORD dwReason, LPVOID lpReserved)\n{\n	switch (dwReason)\n	{\n		case DLL_PROCESS_ATTACH:\n			payload();\n			break;\n	}\n	return TRUE;\n}\" > payload.c");
}

char	**check_all(char **argv)
{
	int		i;
	int		specified[2];
	int		exist[2];
	char	**save;
	int		error;

	specified[0] = 0;
	specified[1] = 0;
	exist[0] = 0;
	exist[1] = 0;
	error = 0;
	save = malloc(2 * sizeof(char *));
	for (i = 1; i < 5; i += 2)
	{
		if (argv[i] && !strcmp(argv[i], "-d"))
		{
			if (argv[i+1] && access(argv[i+1], F_OK))
			{
				printf("ERROR: DLL file does not exits...\n");
				exist[0]++;
			}
			else
				save[0] = argv[i+1];
			specified[0]++;
		}
		else if (argv[i] && !strcmp(argv[i], "-p"))
		{
			if (argv[i+1] && access(argv[i+1], F_OK))
			{
				printf("ERROR: Payload file does not exits...\n");
				exist[1]++;
			}
			else
				save[1] = argv[i+1];
			specified[1]++;
		}
		else if (argv[i])
		{
			printf("ERROR: Invalid argument: %s...\n", argv[i]);
			error++;
		}
	}
	if (specified[0] != 1 && !exist[0])
		printf("ERROR: DLL file not specified...\n");
	if (specified[1] != 1 && !exist[1])
		printf("ERROR: Payload file not specified...\n");
	if (error || specified[0] != 1 || specified[1] != 1 || exist[0] || exist[1])
	{
		free(save);
		exit(1);
	}
	return(save);
}

char *change_dll_name(char *dllname)
{
	int		len;
	char	*new;

	len = 0;
	len = strlen(dllname);
	new = malloc((len + 7) * sizeof(char));
	strncpy(new, dllname, len - 4);
	strcat(new, "_orig.dll");
	new[len + 5] = 0;
	return(new);
}

void	check_dirs(void)
{
	//Checks defs/ dir
	if (!access("defs/", F_OK))
	{
		if (access("defs/", R_OK) && access("defs/", W_OK))
		{
			printf("Dont have permission to r/w onto defs/ folder...");
			exit(1);
		}

	}
	else
		system("mkdir defs/");

	//Checks generated/ dir
	if (!access("generated/", F_OK))
	{
		if (access("generated/", R_OK) && access("generated/", W_OK))
		{
			printf("Dont have permission to r/w onto generated/ folder...");
			exit(1);
		}

	}
	else
		system("mkdir generated/");
}
