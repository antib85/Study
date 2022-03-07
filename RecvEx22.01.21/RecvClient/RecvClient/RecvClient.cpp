// GameClientApp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <conio.h>
#include <functional>
#include <assert.h>

#include <WinSock2.h>
#include <Windows.h> 
#include <WS2tcpip.h> 
#include <thread>
#include <memory>
#include <vector>

#pragma comment (lib, "ws2_32")

std::mutex Lock;

std::thread RecvThread;

bool Check = true;

std::vector<std::string> Recv;

void checkRecv(const char Buffer[])
{
	for (size_t i = 0; i < sizeof(Buffer); ++i)
	{
		if (Buffer[i] == 0)
		{					
			return;
		}

		else if (Buffer[i] == '!')
		{
			std::cout << Recv[0] << std::endl; 
			Recv.clear();
			int a = 0;
		}

		Recv.back() += Buffer[i];	

	}
}


void RecvFunc(SOCKET _SessionSocket)
{
	while (Check)
	{
		char Buffer[1024];

		int Result = recv(_SessionSocket, Buffer, sizeof(Buffer), 0);

		if (SOCKET_ERROR == Result)
		{
			return;
		}

		checkRecv(Buffer);

		if(0 != Buffer[1])
			std::cout << "Recv : " << Buffer << std::endl;
	}
}

int main()
{
	WSADATA wsa;

	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		std::cout << "WSAStartup Error" << std::endl;
	}

	SOCKET SessionSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == SessionSocket)
	{
		return 0;
	}

	std::cout << "IP주소를 입력해주세요" << std::endl;
	std::string Ip;
	std::string Port;
	std::cin >> Ip;

	if ("Q" == Ip
		|| "q" == Ip)
	{
		Ip = "127.0.0.1";
	}
	else if ("w" == Ip
		|| "W" == Ip)
	{
		Ip = "58.150.30.210";
	}

	SOCKADDR_IN Add = { 0, };
	Add.sin_family = AF_INET;
	Add.sin_port = htons(30001);
	if (SOCKET_ERROR == inet_pton(AF_INET, Ip.c_str(), &Add.sin_addr))
	{
		return 0;
	}
	int Len = sizeof(SOCKADDR_IN);

	if (SOCKET_ERROR == connect(SessionSocket, (const sockaddr*)&Add, Len))
	{
		return 0;
	}

	std::cout << "커넥트 성공." << std::endl;

	Recv.push_back(std::string());
	RecvThread = std::thread(RecvFunc, SessionSocket);

	while (true)
	{
		std::string In;

		// Lock.lock();

		std::cin >> In;

		if (In == "q" || In == "Q")
		{
			//TCP면 포핸드 쉐이크를 다 깔끔하게 맞춰줍니다.
			closesocket(SessionSocket);
			Check = false;
			RecvThread.join();
			Sleep(1);
			return 0;
		}

		char Buffer[1024] = { "" };

		Sleep(1);

		memcpy_s(Buffer, sizeof(Buffer), In.c_str(), In.size());

		int Result = send(SessionSocket, Buffer, sizeof(Buffer), 0);
	}

	_getch();
}
