*This project has been created as part of the 42 curriculum by kechan.*

## Description
Get Next Line (GNL) is a C project aiming to create a functional copy of C's fgets.

The basic rundown of GNL / fgets is that these functions return a line (which is defined as a string of text that ends with \n, \0 or the end of the file),
when given the file descriptor (essentially, a number assigned to each file, the stdin, stdout and stderr which allows the OS to access and modify files).

In this rendition of GNL, a static variable (a variable which stores its contents through the entire runtime of the program rather than only while the function
is called) is used to store each iteration of the read() (from the fnctl library) function as a string. That variable is then processed using ft_strchr() (a 42-equivalent of the default C-library strchr),
to find \n or \0 to identify a line. The string is then separated using functions extract_line() and extract_remnant(), which separates the string into the
line (the part of the string before and including the ending \n or \0), which is to be returned, and the remnant (the part of the string after the ending \n or \0),
which is stored for the next call.

## Instructions
To use this function, first complile it, ensuring that the header is also included where the program is compiled:

`cc [-D BUFFER_SIZE=x] get_next_line.c get_next_line_utils.c`

The -D option is available to set the size of the buffer (how much of the file will be read at once).
Variable x is the size of the buffer. If the -D flag is not used, the default buffer size will be set to 10.

The prototype of the function is as follows:

`char	*get_next_line(int fd);`

It is up to the user's discretion to free the memory allocated to each line.

### Return Value
The return value of the function shall be the read line as a char*, or (null), representing an error.

## Resources

#### preexisting functions / methods
https://www.w3schools.com/c/c_files_read.php

https://stackoverflow.com/questions/3501338/c-read-file-line-by-line

https://www.geeksforgeeks.org/c/read-a-file-line-by-line-in-c/

https://stackoverflow.com/questions/6220093/difference-between-read-and-fgets-in-c

https://stackoverflow.com/questions/37843193/reading-new-line-in-c

https://stackoverflow.com/questions/19555434/how-to-extract-a-substring-from-a-string-in-c

https://stackoverflow.com/questions/39217872/implementing-gets-in-c

https://c-for-dummies.com/blog/?p=3379

#### macros
https://www.geeksforgeeks.org/c/macros-and-its-types-in-c-cpp/

#### file descriptors
https://dev.to/aerrfig/get-next-line-a-42-project-to-learn-how-to-deal-with-file-descriptors-and-io-of-system-3652

https://en.wikipedia.org/wiki/File_descriptor

#### manual pages
https://man7.org/linux/man-pages/man2/open.2.html

https://man7.org/linux/man-pages/man2/read.2.html

https://man7.org/linux/man-pages/man3/fgets.3.html

https://linux.die.net/man/3/getline

https://man7.org/linux/man-pages/man3/fgets.3p.html

#### guides from other 42 students
https://koisuru-computer.hateblo.jp/entry/9937063

https://42-cursus.gitbook.io/guide/1-rank-01/get_next_line/building-the-thing

https://zenn.dev/grigri_grin/articles/bf45a9fa50f25f#fn-35fc-1

https://medium.com/@beatrizbazaglia/get-next-line-3872eb3189e6

#### debugging
https://www.koikikukan.com/archives/2017/02/03-005555.php

https://sourceware.org/gdb/current/onlinedocs/gdb.html/Breakpoints.html

https://cs3157.github.io/www/2022-9/guides/valgrind.html

https://gcc.gnu.org/onlinedocs/cpp/Diagnostics.html

https://visualgdb.com/gdbreference/commands/display

https://stackoverflow.com/questions/668962/what-is-the-difference-between-gcc-ggdb-and-gcc-g

https://www.reddit.com/r/C_Programming/comments/1etgqmv/how_do_i_fix_this_memory_leak/


#### constants
https://stackoverflow.com/questions/19715850/eof-symbolic-constant


#### memory
https://stackoverflow.com/questions/28945283/possible-to-both-return-and-free-a-dynamically-allocated-array-in-c

**AI was not used throughout this project.**

## Algorithm
The algorithm for this function is as follows:

1. The function is called.

2. The buffer is set.

3. If the memory allocation for the buffer succeeded, and there are unread lines, read lines equal to the buffer.

4. If the return value of read is not -1, then concatenate the result to the previous result (if there is no previous result, do nothing).

5. Repeat 3 & 4 until the end of file is reached, or an error occurs.

6. Pass the line or failed result, NULL into extract_line(), which will extract the line from the read string, or return NULL if failed.
Pass this result back to get_next_line().

7. Pass the line or NULL to extract_remnant(), which will extract the remnant from the read string, or return NULL if failed.
Pass this result back to get_next_line().

8. The result of extract_line() is set as the return value of get_next_line(). The remnant is stored in variable "storage".

6. Return line if succeeded / return NULL if failed.