# AST definition and rules -- draft

## Node definitions

### Pipe
- Left!: redirection / command / pipe (pipe is left based, to accomodate DFS algo)
- Right!: redirection / command

### Redirection
- Value!: type
- Left!: command
- Right!: file / here document

### Command
- Value!: command -> string
- Right: argument / variable / assignemnt

### Argument
- Value!: arguments -> string array

### Environment variable
- Value!: variable -> string

### Variable assignment
- Value!: assignment -> string
- Right: redirection / command
