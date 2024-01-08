## Installation
There are many options for installing xv6 and running and compiling your own programs in it. It is recommended that you follow the method prescribed in the guide.

However, depending upon the OS and personal preference, students can explore other options if they want. In this guide, we would be installing the xv6 using Docker. Some other options are using a VirtualBox and even WSL (windows sub system for linux)
for Windows Users.

### Step 1:
Download docker desktop from the official website and install on your system. It is available for Windows, Linux and Mac (mac users need to select the specific install pertaining to chip). After downloading the setup, please install it on your system. It is
a straightforward process and you do not have to use any custom setting options (use the standard setting). After successfully installing, run Docker Desktop

### Step 2:
Run this command in PowerShell or bash to pull the ubuntu image with xv6:

docker pull grantbot/xv6

### Step 3:
To run the docker image and get going with xv6 run this command:

docker run -it grantbot/xv6

### Step 4:
Now inside the shell in the ubuntu image run

cd /home/a/xv6-public/
<br>to enter the root folder of the xv6

### Step 5:
make (for building the OS)
<br>make qemu-nox (for running the xv6 OS)

Terminate xv6: pressing control + A at the same time => release => quickly =>press x.

Delete xv6 executable: make clean

*NOTE:* Every time you make change to xv6 code, you need to run "make" (compile xv6) => "make qemu-nox" (launch xv6) => run your program (such as hello) => "make clean" (clean up your executable xv6). Repeat this process when necessary.