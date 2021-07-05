# Discord Rich Presence CLI
Set your Discord Rich Presence from the command line or script!

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
 5. Start timestamp (0 for none)
 6. End timestamp (0 for none)

As soon as the end timestamp is entered, your rich presence is updated,
and the input process begins again.

Leaving a prompt blank will reset the input loop, prompting for Details
again. Leaving the Details prompt blank will clear the presence.

## Compiling

### Linux

1. Clone this repository:

```
git clone https://github.com/Pigpog/discord-rich-presence-cli.git
```

2. Download and extract the latest release of [Discord-RPC](https://github.com/discordapp/discord-rpc/releases)
4. Copy the files from linux-dynamic/lib to /usr/lib, and the files from linux-dynamic/include to /usr/include
5. Run the following commands from this project's root directory:

```
sudo ldconfig
cmake .
make
```

You should now have a binary file named "send-presence". Run it with `./send-presence`, and it should start asking you questions (see Usage).
