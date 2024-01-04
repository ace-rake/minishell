# Execute sequence
 
### Purpose
> Trying to figure out in what pattern/sequence the syntax tree should be executed

### Notes
> look into recursive
> depth first search <-- prob this
> breath first search

### Logic start
> always start at the top (duh)
> all nodes have a input and output, the standard for these will just be the stdin and stdout
> these in and output can be changed based on previous nodes (e.g. pipe or redirection)
> 
#### *cases*

> pipe
> > creates a pipe()
> > sets the output of its left node to be that of the pipe()
> > sets the input of its right node to be that of the pipe()

> *>*
> > truncate to 0/create the file to its right
> > there cant already be a file of that name without writing permissions
> > sets the output of its left node to the fd of the file to its right node

> *>>*
> > same as *>* only no need to truncate first, but have to write at the end

> *<*
> > sets the input of its left node to be the fd of the file to its right
> > file has to exist and be readable

> *<<*
> > heredoc stuff
> command
> > will execute the command to the left
> > will use the node to the right as its arguments should it exist
> > > should these arguments exist then they overrule any input fd that was given prior to the execution of this command

> argument
> > these are needed for everything else to work

### Fd priority 
> fd priority will be as following
> 1. Any arguments given to the command will be used as input
> 2. Any previous redirection either by redirection or piping for either input or output
> 3. Default to stdin and stdout

