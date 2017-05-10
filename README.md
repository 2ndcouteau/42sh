# 42sh
This is the one. The best shell ever ! Yes, after BASH or ZSH of course ;-

This project is a good reproduction of a shell. We made it from scratch.

The main improvements in comparison with my 21sh are:
- Jobs control
- Subshell \`\`
- Globbing Completion
- Alias
- Bang History ! management
- Dynamical completion
- and history completion.
- Pimp prompt

**This is a group project.**

#### Builtins :

	jobs:
		list current jobs.
	fg:
    		relaunch the last job stoped.
	bg:
    		put job in background.
	env:
		env [-i][ENV_VAR_NAME=][ENV_VALUE][CMD]
	setenv:
		setenv [ENV_NAME_VAR] [ENV_VALUE]
	unsetenv:
		unsetenv [NAME_VAR]
  	alias:
	  	alias [ALIAS]="ARGS"
  	unalias:
  		unalias [ALIAS]
	exit:
		exit [VALUE]
	history:
		history [VALUE] -- Value print n_VALUE last command in history
    		we also manage the bang system. **"!"**
	cd:
		cd [-LP] [PATH]
			PATH:		absolute path:	/path
									~
					relative path:	./path
									~/path
					direct path:	($PWD)path
									'-'
			OPTIONS :	Options can be print everywhere in the command.
					For disable them you can use "--"
	echo:
		echo [-Een] [--version] [--help] [ARG]
			You can print characters with them OCTAL or HEXA values with -e option 
			Cf "man echo"

#### Pipe: '|'
	CMD | CMD
		You can it to use all of available pipe else shell return error. Test: "CMD | CMD | CMD | CMD ..." 
		There is no limit of buffer usage; Test : ls -Rla | cat -e

#### Separator: ;
	You can write mutiple command and separate them with ';' 
	CMD ; CMD

#### Redirections: < > << >> :
		You can redirect output execution to a file or file to a binary.
		Heredoc: <<
			Multiple enter for Heredoc are valid but just the last one will be used 
			Waiting Current Keyword is print in prompt 

#### Groups : []{}()
		Those parts will be delete before execution 
		Waiting close character is print in prompt 
		To much open character make a warning 

#### Globbing: \*

	You can use \* sign for call all occurences who match with.
	This could be a path, a binary, a file ...

#### Back quotes: \`\`

	Create a subshell and return his results

#### Quotes: "" ''
		For "" and '', it's the current usage 

#### Variables: $VARIABLE
		Call $ENV_NAME_VAR with '$' for replace it by his ENV_VALUE 

#### BackSlash: \
		Use it for echap a character
		if \ is the last one of a command, the shell return the line and let you continue write your command 

#### Operator: && ||
		AND operator &&: If the first command return SUCCESS then the second command is execute else not.  
		OR operator ||:	 If the first command return ERROR then the second command is execute else not.  

#### Agregator File Descriptor: [number]>&[number] , 2>&1 ...
		Simple agreg_fd.
			[number] are strictly necessary.
		Just the first one valid agreg_fd will be use.

### TERMCAPS:

	left arrow	: Move to one left character
	right arrow 	: Move to one right character
	up arrow	: Make an history completion with previous line history
	down arrow	: Make and history completion with next line history

	enter		: Valid command
	delete		: Delete one character on the right of cursor 
	suppr		: Delete one character on the left of cursor

	CTRL +:
		x	: Cut the line after the cursor
		k	: Cut the line after the cursor
		u	: Cut all the line
		w	: Paste the last cut
		e	: Go to the end of the command
		a	: Go to the begin of the command

		d	: Exit the shell
		l	: Clear the window

		s	: Suspend the current command
		q	: Start the command previously suspend 
		c	: Stop the current command
		z	: Suspend current process

	CTRL + MAJ + \	: Quit

	ALT +:
		left arrow	: Move to one left word
		right arrow 	: Move to one right word
		up arrow	: Move to one line up
		down arrow	: Move to one line down

	BL : Bell signal when Termcaps are unvailable.

	You can resize the window reasonably. :D
	If Termcap seems broken, use CTRL + l for clean the bugs 

#### $SHLVL:
	Incremente SHLVL env variable for each new shell inception. 

#### Finest Error Management:
	For the majority of error, they have precise error return. 

#### No leaks

#### Debug mode:

	you can precise the tty of another shell for print debug output in.
	./42sh debug=ttyname

### Grade: 110/100
