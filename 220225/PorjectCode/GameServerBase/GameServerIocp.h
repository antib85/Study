#pragma once
#include <WinSock2.h>
#include <thread>
#include <vector>
#include <mutex>
#include <functional>
#include "GameServerObjectBase.h"
#include "GameServerThread.h"

// �뵵 : 
// �з� : 
// ÷�� : 


class GameServerIocpWorker 
{
public:
	friend class GameServerIocp;

private:
	HANDLE IocpHandle;
	DWORD NumberOfBytesTransferred;
	ULONG_PTR CompletionKey;
	LPOVERLAPPED lpOverlapped;
	DWORD Time;
	size_t Index;

public:
	template<typename ConvertType>
	ConvertType GetConvertCompletionKey()
	{
		return reinterpret_cast<ConvertType>(CompletionKey);
	}

	ULONG_PTR GetCompletionKey()
	{
		return CompletionKey;
	}

	DWORD GetNumberOfBytes()
	{
		return NumberOfBytesTransferred;
	}

	LPOVERLAPPED GetOverlappedPtr()
	{
		return lpOverlapped;
	}


public:
	size_t GetIndex() 
	{
		return Index;
	}

public:
	GameServerIocpWorker(HANDLE _IocpHandle, size_t _Index, DWORD _time);

public:
	BOOL Wait();
};

// �̳༮�� �����嵵 ����ų� ���ų�.
class GameServerIocp : public GameServerObjectBase
{
private: // Member Var
	HANDLE Iocp_;
	std::mutex iocpLock;
	std::vector<std::shared_ptr<GameServerThread>> threadList_;
	std::vector<std::shared_ptr<GameServerIocpWorker>> threadWorkerList_;

public:
	size_t GetThreadCount() 
	{
		return threadList_.size();
	}
	

public: // Default
	// -1�� �׳� �⺻ �ý��� �ھ�� * 2 ��ŭ ������.

	GameServerIocp();

	GameServerIocp(std::function<void(std::shared_ptr<GameServerIocpWorker>)> _Func, int threadCount);
	GameServerIocp(std::function<void(std::shared_ptr<GameServerIocpWorker>)> _Func, DWORD _Time, int threadCount);
	~GameServerIocp();

	GameServerIocp(const GameServerIocp& _Other) = delete;
	GameServerIocp(GameServerIocp&& _Other) noexcept;

protected:
	GameServerIocp& operator=(const GameServerIocp& _Other) = delete;
	GameServerIocp& operator=(GameServerIocp&& _Other) = delete;

public:
	void Initialize(std::function<void(std::shared_ptr<GameServerIocpWorker>)> _Func, DWORD _Time, int threadCount);

public: // Member Function
	void AddThread(std::function<void(std::shared_ptr<GameServerIocpWorker>)> _Func, DWORD _Time);
	void Post(DWORD _byteSize, ULONG_PTR _Data);
	bool Bind(HANDLE _Handle, ULONG_PTR _CompletionKey) const;
};
