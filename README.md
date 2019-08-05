Test C/C++ For NetApp.

Created with open source version of QtCreator.
CentOS 7 (64bit) with KDE installed. Selected Dev tools on install of OS

Ugraded the following: 

#sudo yum upgrade make (to version 3,82)

#sudo yum upgrade gdb 

#sudo yum upgrade g++ (to version 4.8.5)

#sudo yum upgrade gcc (to version 4.8.5)

Using Boost:

  boost-1.53.0-27.el7.x86_64
  
  boost-devel-1.53.0-27.el7.x86_64

Installed via this command:

#sudo yum install boost boost-devel



The code is obviously a bit simple. Most of my C++ experience is on Windows, not Linux. The spec did not say anything
about logging so I just used std::cout.

Working in Linx after working in Windows so long is a bit like figuring out how to drive on the right side of the road 
when I first got to the US, after spending so long driving on the left. 

Cars work the same, but everything is in a different place. Just as it took some time developing the muscle memory 
for driving in the US, it may take some time to develop the muscle memory for POSIX programing.

Have also manged to get a basic makefile working, and have it building with no warnings or errors 
(at least on my box).
