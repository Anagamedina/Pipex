
PATH=
/opt/homebrew/bin
:/opt/homebrew/sbin
:/usr/local/bin
:/System/Cryptexes/App/usr/bin
:/usr/bin:/bin:/usr/sbin:/sbin
:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin
:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin
:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin
:/opt/X11/bin
:/Applications/iTerm.app/Contents/Resources/utilities
:/Users/catalinaburgos/Library/Application Support/JetBrains/Toolbox/scripts
:/Users/catalinaburgos/Library/Python/3.9/bin



TESTING CASES PIPEX:
- que pasa si no existe los archivos de ntrada y salida i

original:
``` c
< infile_bash grep texto | wc -w > outfile_bash
```

my_pipex:

``` bash
./pipex infile "grep texto" "wc -w" outfile
```

``` bash 
< infile grep texto | wc -w > outfile_bash
diff outfile outfile_bash
```

``` bash
❯ ./pipex inexistente "ls -l" "wc -l" outfile_modify
Error: Cannot open INPUT file: No such file or directory

❯ ./pipex infile "ls -l" "wc -l" outfile_modify
Error: Cannot open OUTPUT file: Permission denied
```

``` bash
❯ ./pipex infile "./script.sh" "wc -l" outfile
Error: Command not found: No such file or directory
```

``` bash
~/CLionProjects/Pipex$ < infile ./script.sh | wc -l > outfile
bash: ./script.sh: Permission denied
```

PERMISOS:

User: rwx -> 421
Group: rwx -> 421
Others: rwx -> 421

0644
User: rwx -> 420
Group: rwx -> 421
Others: rwx -> 421



 ``` bash
 if (access(new->cmd_args[0], F_OK) == -1)
	{
		perror("Error: Command not found F_OK ");
//		free_split_result(new->cmd_args);
		free(new);
		return (NULL);
	}
	if (access(new->cmd_args[0], X_OK) == -1)
	{
		perror("Error: Permission denied  X_OK");
//		free_split_result(new->cmd_args);
		free(new);
		return (NULL);
	}
```


