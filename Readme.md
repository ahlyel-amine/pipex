<h1>Project structur</h1>

```
/pipex         (root project folder)
    |
    |____/bin        (the final executable file)
    |
    |___/include     (header files, .h)
    |
    |____/src        (source files, .c)
    |
    |____/obj        (where the generated .o files will be)
    |
    |____/lib        (any library dependences)
    |
    |____Makefile    (make instructions file)
    |
    |____README      (general readme of the project)
    |
    |___/bonus
        |
        |____/bin        (the final executable file)
        |
        |___/include     (header files, .h)
        |
        |____/src        (every source file, .c and .c)
        |
        |____/obj        (where the generated .o files will be)
        |
        |____/lib        (any library dependences)

```
<h1>Usage</h1>

<h3>Mandatory part</h3>

open a terminal window in the project directory
~~~
$> make
~~~
for mandatory part you can execute commands like
~~~
$> bin/pipex "infile" "command1" "command2" "outfile"
~~~
behave exactly like 
~~~
$> < infile command1 | command2 > outfile
~~~
and you can find the output in the outfile exist in the root directory of the project

<h3>bonus part</h3>

open a terminal window in the project directory
~~~
$> make bonus
~~~
for bonus part you can execute commands like
~~~
$> bonus/bin/pipex "infile" "command 1" "command 2" ... "command n" "outfile"
~~~
behave exactly like 
~~~
$> < infile command1 | command2 | ... | "command n" > outfile
~~~
and you can find the output in the outfile exist in the bonus directory

and you can execute commands like :
~~~
$> bonus/bin/pipex "here_doc" LIMITER command1 command2 outfile
~~~
you got a open file 
~~~
$> pipe heredoc>
~~~
^^ enter a text and th limiter
this one behave like 
~~~
$> command1 << LIMITER | command2 >> outfile
~~~
<h3>Cleaning</h3>

to delete object file
~~~
$> make clean
~~~

to delete object files and executable file

~~~
$> make fclean
~~~

<h1>Project</h1>

```
main process
|
|
|                              \/ for each command \/
|_______________________________________________________________________________________________
|\                                                                                              |
| \                                                                                             |
|  \                                                                                            |
|   \                                                                                           |
|    \                                                                                          |
|     \                                                                                         |
|       pipe(fd)                                                                                |
|       |                                                                                       |
|       | pid = fork()                                                                          |
|       |                                                                                       |
|       |___________child process                                                               |
|               |       dup2(fd[1], STDOUT)                                                     |
|               |       close(fd[0])                                                            |
|               |       close(fd[1])                                                            |
|               |______ execve(command path, command, envp) // this function kill process       |
|               |                                                                               |
|       ________|___ parent process                                                             |
|      /           |                                                                            |
|     /            |   dup2(fd[0], STDIN)                                                       |
|    /             |   close(fd[1])                                                             |
|   /              |   close(fd[0])                                                             |
|  /               |___waitpid(pid)                                                             |
| /                                                                                             |
|/______________________________________________________________________________________________|
|
|
|
|___________ parent process == main proccess   |
        |                                      |
        |  dup2(outfile, STDOUT)               |  < for last command
        |__execve(command path, command, envp) |
```

<h1>Final Mark</h1>

Not yet
