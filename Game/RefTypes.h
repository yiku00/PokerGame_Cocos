/********************************************************************
	filename: 	RefTypes.h
	
	purpose:	
*********************************************************************/
#pragma once

struct ServerInfo
{
	string id;
	string name;
	string addr;
	string port;
	string vers;
	string md5;
	int status;
	string info;
};

typedef vector<ServerInfo> ServerList;