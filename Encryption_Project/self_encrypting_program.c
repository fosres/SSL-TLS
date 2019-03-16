#if 0
(C) Copyright 2018-INFINITY Tanveer Salim
This program will automatically have built in W^X writing permissions.
This program comes with absolutely NO WARRANTY and provided as is.

Not only does a program like this perfrom its duty it also, protects

it from being statically and/or dynamically analyzed by unwelcome people.

The writer of this software honors the principle of Free and Open Source

Software as advocated by Richard Matthew Stallman. Still, there are times

when measures must be taken to prevent the software from being pirated,

or to prevent people with malicious intentions from seeing the software.

For instance, you are designing a computer program for an academic

assignment and you are FORBIDDEN from sharing your code with classmates.

So this type of program can not only do what the program is supposed to

do, but also encrypts its own source code file after code generation of

the program completes. After the executable code is run, the executable

will only decrypt the source code file IF AND ONLY IF the computer has

the same git identity tag as the original author of the program. But

once the executable finishes decrypting the source code file, it will

automatically delete itself. You can either have the source code file

as readable xor (the xor is not a typo!)  have the executable exist in 

your machine only since you are not the author of the program! The executable 

reproduces a copy of the source code by using quine programming features. Again, 
	   
once the copy file of the source code file is made, it automatically deletes itself.

Only if you are the true author of the program, where the program verifies your

git identity tag is identical to that of the authors, will the program allow

both the source and binaries to exist in any location throughout the author's

machine.


The program stores the hash salt of the author's git identity tag in a global 

static char array. It checks if the hash salt the git identity tag the machine 

returns is identical to the one in the global static char array.


#endif
