## Implementing the uniq command
Implement the commonly used command line program in Linux called “uniq” but will be doing this myself in xv6 to get an idea of how command line programs are written. uniq is a Unix utility which, when fed a text file, outputs the file with adjacent identical lines collapsed to one. If a filename is provided on the command line (i.e., uniq FILE) then uniq should open it, read, filter out, print without repeated lines in this file, and then close it. If no filename is provided, uniq reads from standard input.

For the examples I will be running the uniq command on the README.md file included in xv6. Before I begin coding I'll delete all the text in README.md file and paste the following lines of text in its place. This is the file and subsequent text you will be running the uniq program on.

### Text to copy and paste into xv6 README.md file:
No. 1<br>
No. 2<br>
No. 2<br>
No. 2<br>
No. 3<br>
No. 4<br>
No. 5<br>
No. 6<br>
No. 6<br>
No. 2<br>
no. 2

Here’s an example of the basic usage of uniq:
 
$ cat README.md

No. 1<br>
No. 2<br>
No. 2<br>
No. 2<br>
No. 3<br>
No. 4<br>
No. 5<br>
No. 6<br>
No. 6<br>
No. 2<br>
no. 2

$ uniq README.md

No. 1<br>
No. 2<br>
No. 3<br>
No. 4<br>
No. 5<br>
No. 6<br>
No. 2<br>
no. 2

I should also be able to invoke it without a file, and have it read from standard input. For example, I can use a pipe to direct the output of another xv6 command into uniq:

$ cat README.md | uniq

No. 1<br>
No. 2<br>
No. 3<br>
No. 4<br>
No. 5<br>
No. 6<br>
No. 2<br>
no. 2