Project #3: Kernel Mailbox
July 29, 2013
Jarrad Battaglia
Jared Roberts

Modified files:
https://github.com/maddchickenz/kernel/compare/P3

Compilation and Testing:
Project was written and compiled on TUX. Apply the supplied patch to the Linux source code to test. Various test cases are included as well.

Difficulties:
The project was pretty straight forward. Once we understood that the kernel was shared by all processes (particularly variables used in the kernel), development continued on at a good pace. The material was understood, and most bugs were just minor typos.

Also had drastic problems with myreceive earlier we could send and receive but once we implemented checking, the pids from the mailbox and onces being sent in would not comparison check correctly against each other even though they were the same pid.  Also you can see this demonstration in the video from the 23 second mark onward where the screen would freeze when in this (because it would be stuck in our loop).  But could not get it to work correctly, but mysend does work, and the code in myreceive works except for the pid checking.
