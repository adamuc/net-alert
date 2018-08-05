/*
Copyright (C) 2018  Adam Mucha

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef _WIN32
  #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0501 /* Windows XP */
  #endif
  #include <winsock2.h>
  #include <ws2tcpip.h>
#else
  /* POSIX-style sockets */
  #include <sys/socket.h>
  #include <arpa/inet.h>
  #include <netdb.h>
  #include <unistd.h>
#endif

#ifndef _WIN32
  typedef int SOCKET;
#endif

int sockInit(void)
{
  #ifdef _WIN32
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(1, 1), &wsa_data);
  #else
    return 0;
  #endif
}

int sockQuit(void)
{
  #ifdef _WIN32
    return WSACleanup();
  #else
    return 0;
  #endif
}

int sockClose(SOCKET sock)
{
  int status = 0;

  #ifdef _WIN32
    status = shutdown(sock, SD_BOTH);
    if(status == 0)
    {
      status = closesocket(sock);
    }
  #else
    status = shutdown(sock, SHUT_RDWR);
    if(status == 0)
    {
      status = close(sock);
    }
  #endif

  return status;
}