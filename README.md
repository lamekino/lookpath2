LookPath2
---------
This is a re-write of an old C program I wrote in 2023. It goes through each
directory in the user's $PATH and searches for the given pattern. LookPath2 is
inspired by the `look(1)` UNIX command; by default it will search by checking if
the string contains the argument as a substring prefix. Regular expressions are
also supported with the `-E` flag.

It can be pretty useful if you forget part of a command name, or have multiple
versions of the same program installed.

*No LLM generated code was used in the creation of this project.*
