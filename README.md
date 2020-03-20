# Discord Rich Presence CLI
Set your Discord Rich Presence from the command line!

_Adapted from the send-presence program found in https://github.com/discordapp/discord-rpc/_

## Description
This program can be used to set your Discord Rich Presence by inputting
each Rich Presence attribute into stdin. It can be used as a simple, 
lightweight, cross-platform and cross-language shim between any program and 
Discord's Rich Presence API.

This repository was made specifically for use in vlc-discord-rpc, so if 
you are using this for your own purposes I would suggest forking. Things 
will change without notice on this repository.

## Usage
NOTE: This documentation assumes that you have a basic understanding of
how Discord Rich Presence works.

The program will prompt you through each of the attributes of a Rich 
Presence. Here is the order in which the data should be entered:

 0. APPLICATION ID (ONLY ONCE)
 1. Details
 2. State
 3. Large Image Key
 4. Small Image Key

If any of these attributes are missing, it will immediately clear the 
rich presence and restart its input loop, going back to prompting for 
Details.

As soon as the Small Image Key is entered, the rich presence data is 
sent to Discord to update the presence, and the input process begins 
again.

## Compiling
### Linux
1. Download the latest release of [Discord-RPC](https://github.com/discordapp/discord-rpc/releases)
2. Extract the zip file
3. Copy the files from linux-dynamic/lib to /usr/lib, and the files from linux-dynamic/include to /usr/include
4. Run the following commands from this project's root directory:
```
sudo ldconfig
cmake .
make
```
You should now have a binary file named "send-presence". Run it with `./send-presence`, and it should start asking you questions (see Usage).
