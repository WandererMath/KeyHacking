# KeyHacking
Help you Hack out passwords and sensitive information!


DISCLAIMER:

FOR ACADEMIC PURPOSE ONLY.

Key presses are recorded on windows target machine and sent to the hacker. 

"Me" runs on the server (hacker's computer, with Linux operating system). A public IP is needed. If you don't have, deploy it on a vps. 

You'll need a cross-compiler to compile Victim.cpp (It contains some C codes for Unix) to .exe file for Windows target machine. Typically the Windows tool Cygwin helps. Change the preprocessing command "#define S_IP" in Victim.cpp to your own IP address (the computer with which to receive key press logs). 

