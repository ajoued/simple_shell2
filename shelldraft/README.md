**0x16 C-Simple Shell**
made by Ajoued Senoussi and Abdulmalik Aremu

**0 - Code passes Betty checks**

**1 - UNIX command line interpreter**

    - Display prompt.
      - Prompt displays repeated every time a coomand is carried out.
      	- If executable not found, print an error message.
	  - Handles errors.
	    - Handles "end of file" condition (Ctrl+D).

**2 - Simple shell 0.1 +**

    - Manages user interface with arguments.

**3 - Simple shell 0.2 +**

    - Handles PATH.
      - If command does not exist do not call fork.

**4 - Simple shell 0.3 +**

    - Execute the exit built-in, that exits the shell.
      - Arguments to built-in exit not handled.

**5 - Simple shell 0.4 +**

    - Apply the env built-in, prints the current environment.