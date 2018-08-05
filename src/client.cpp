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

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "client.h"


int hSocket;
struct sockaddr_in server;

char ip[15];
char data[2048];


IMPLEMENT_APP(nacApp)

bool nacApp::OnInit()
{
  nacFrame *frame = new nacFrame(_T("net-alert client"), wxPoint(0, 0), wxSize(280, 100));

  frame->Show(true);
  SetTopWindow(frame);

  return true;
}

BEGIN_EVENT_TABLE(nacFrame, wxFrame)
  EVT_BUTTON(BUTTON_sendMsg, nacFrame::OnSend)
  EVT_BUTTON(BUTTON_about, nacFrame::OnAbout)
END_EVENT_TABLE()

nacFrame::nacFrame(const wxString &title, const wxPoint &pos, const wxSize &size) : wxFrame((wxFrame*) NULL, -1, title, pos, size, wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
  ipLabel = new wxStaticText(this, LABEL_ip, _T("Target IP:") ,wxPoint(10, 12), wxSize(60, 20), wxALIGN_LEFT);
  msgLabel = new wxStaticText(this, LABEL_msg, _T("Message:") ,wxPoint(10, 42), wxSize(60, 20), wxALIGN_LEFT);

  ipField = new wxTextCtrl(this, TEXT_ip, _T(""), wxPoint(70, 10), wxSize(120, 20), 0);
  msgField = new wxTextCtrl(this, TEXT_msg, _T(""), wxPoint(70, 40), wxSize(120, 20), 0);

  sendMsg = new wxButton(this, BUTTON_sendMsg, _T("Send"), wxPoint(210, 10), wxSize(50, 25), 0);
  about = new wxButton(this, BUTTON_about, _T("About"), wxPoint(210, 35), wxSize(50, 25), 0);
}

void nacFrame::OnSend(wxCommandEvent& event)
{
  if(!ipField->GetValue() || !msgField->GetValue()) return;

  memset(data, 0, sizeof(data));

  strcpy(ip, ipField->GetValue().c_str());
  strcpy(data, msgField->GetValue().c_str());

  sockInit();
  hSocket = socket(AF_INET, SOCK_STREAM, 0);

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(ip);
  server.sin_port = htons(30400);

  if(connect(hSocket, (struct sockaddr *)&server, sizeof(server)) < 0)
  {
    wxMessageBox("Connection error");
    sockQuit();
    sockClose(hSocket);
    return;
  }

  if(send(hSocket, data, msgField->GetValue().length(), 0) < 0)
  {
    wxMessageBox("Data send failed!");
    sockQuit();
    sockClose(hSocket);
    return;
  }

  wxMessageBox("Message sent!");

  sockQuit();
  sockClose(hSocket);
}

wxString aboutInfo = "aba";

void nacFrame::OnAbout(wxCommandEvent& event)
{
  wxMessageBox("net-alert 1.0\n(C) Adam Mucha 2018\nLicensed under the GNU General Public License v3.0 (GPLv3)\n\nMain repository: https://github.com/adamuc/net-alert\nContact: mail@adammucha.eu", "About net-alert", wxICON_NONE);
}
