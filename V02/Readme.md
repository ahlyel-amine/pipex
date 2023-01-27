main process
|
|
|                              \/ for each command \/
|_______________________________________________________________________________________________
|                                                                                               |
|_______pipe(fd)                                                                                |
|       |                                                                                       |
|       | pid = fork()                                                                          |
|       |                                                                                       |
|       |___________child process                                                               |
|       |       	|	dup2(fd[1], STDOUT)                                                     |
|       |       	|	close(fd[0])                                                            |
|       |       	|	close(fd[1])                                                            |
|       |       	|__	execve(command path, command, envp) // this function kill process       |
|       |                                                                                       |
|       |___________ parent process                                                             |
|       |           |                                                                           |
|       |           |   dup2(fd[0], STDIN)                                                      |
|       |           |   close(fd[1])                                                            |
|       |           |   close(fd[0])                                                            |
|       |           |___waitpid(pid)                                                            |
|       |                                                                                       |
|_______|_______________________________________________________________________________________|
        |
        |
        |
        |___________ parent process                    |
                |                                      |
                |  dup2(outfile, STDOUT)               | 	< for last command
                |__execve(command path, command, envp) |
