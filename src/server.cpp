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

#include "sockets.h"

#include <iostream>
#include <wx/msgdlg.h>


int hSocket, accepted_hSocket, c;
struct sockaddr_in server, client;

char message[2048];


int serverFunction()
{
  memset(message, 0, sizeof(message));

  sockInit();
  hSocket = socket(AF_INET, SOCK_STREAM, 0);

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(30400);

  if(bind(hSocket, (struct sockaddr *)&server, sizeof(server)) < 0)
  {
    std::cout << "Bind failed." << std::endl;
    sockQuit();
    sockClose(hSocket);
    return 1;
  }

  listen(hSocket, 3);

  c = sizeof(struct sockaddr_in);
  accepted_hSocket = accept(hSocket, (struct sockaddr *)&client, (socklen_t*)&c);

  if(accepted_hSocket < 0)
  {
    std::cout << "Connection failed.";
    sockQuit();
    sockClose(hSocket);
    sockClose(accepted_hSocket);
    return 2;
  }

  memset(message, 0, sizeof(message));

  if(recv(accepted_hSocket, message, 2048, 0) > 0)
  {
    std::cout << "Received: ";
    std::cout << message << std::endl;
    wxMessageBox(message);

    sockQuit();
    sockClose(hSocket);
    sockClose(accepted_hSocket);
  }

  return 0;
}


int main()
{
  std::cout << "net-alert 1.0\n(C) Adam Mucha 2018\nLicensed under the GNU General Public License v3.0 (GPLv3)\n\nMain repository: https://github.com/adamuc/net-alert\nContact: mail@adammucha.eu\n" << std::endl;

  while(true)
  {
    serverFunction();
  }
}
