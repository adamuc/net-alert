# About net-alert
A client-server application written in C++ made for opening messageboxes on remote computers.
It's mainly designed to be simple and bloat-free. It uses wxWidgets for the GUI and messageboxes.
Port 30400 is used for sending and receiving messages.

# Client usage
Using the client is quite straightforward - you just enter your message, a destination address and click "Send".
A command line version of the client may be released in the future.

![net-alert client GUI](https://i.imgur.com/00TZJat.png)

# Server usage
The server is a process which sits in the background and doesn't need any interaction.  
You can run it from a terminal/console for some extra information.

![net-alert server messagebox](https://i.imgur.com/uRqbBLU.png)

# Binaries
You can download the static 32-bit precompiled binaries for Windows on the releases tab [here](https://github.com/adamuc/net-alert/releases).

# License
net-alert is licensed under the [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl.html).

![GPLv3](https://www.gnu.org/graphics/gplv3-127x51.png)
