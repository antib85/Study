// Homework220107.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> CutIp(const std::string& _IpText, char _CutChar)
{
	// .12233.2222.333

	std::vector<std::string> Ips;
	Ips.push_back(std::string());
	for (size_t i = 0; i < _IpText.size(); i++)
	{
		if (_IpText[i] == _CutChar)
		{
			Ips.push_back(std::string());
			continue;
		}

		Ips.back() += _IpText[i];
	}

	return Ips;
}

bool IsNumberStr(const std::string& _Number)
{
	for (size_t i = 0; i < _Number.size(); i++)
	{
		if (0 == isdigit(_Number[i]))
		{
			return false;
		}
	}

	return true;
}

bool CheckIp(const std::string& _IpText)
{
	std::vector<std::string> VectorIp = CutIp(_IpText, '.');

	if (4 != VectorIp.size())
	{
		return false;
	}

	// 숫자인지 아닌지 구분하면 끝난다.
	for (size_t i = 0; i < VectorIp.size(); i++)
	{
		if (VectorIp[i] == "")
		{
			return false;
		}
	}

	for (size_t i = 0; i < VectorIp.size(); i++)
	{
		if (false == IsNumberStr(VectorIp[i]))
		{
			return false;
		}

		int Value = std::stoi(VectorIp[i]);
		if (0 > Value)
		{
			return false;
		}

		if (Value > 256)
		{
			return false;
		}
	}

	int a = 0;

	// 내가 생각하는 완벽한 조건을 통과했을때만 여기로 오게 만든다.
	return true;
}

bool CheckPortNumber(const std::string& _IpText)
{
	return std::string::npos != _IpText.find(':');
}

int CheckPoint(const std::string& _IpText)
{
	int Count = 0;

	for (int i = 0; i < _IpText.size(); i++)
	{
		if (_IpText[i] == '.')
		{
			++Count;
		}
	}

	return Count;
}

int main()
{
	std::string ResultIp = "";
	std::string ResultPort = "";
	std::string Ip;
	int Port = -1;
	while (ResultIp == "")
	{
		std::cout << "IP주소를 입력해주세요" << std::endl;
		std::cin >> Ip;

		// 동시에 2가지를 처리하려고 하지마세요.
		if (3 != CheckPoint(Ip))
		{
			continue;
		}

		// 포트가 있는지 없는지 찾아봅니다.
		if (true == CheckPortNumber(Ip))
		{
			// 포트랑 ip를 분리해야한다.

			std::vector<std::string> IPAndPort = CutIp(Ip, ':');

			ResultIp = IPAndPort[0];
			ResultPort = IPAndPort[1];

		}
		else
		{
			if (true == CheckIp(Ip))
			{
				ResultIp = Ip;
				break;
			}
		}
	}

	while (ResultPort == "")
	{

	}

	int a = 0;
}
