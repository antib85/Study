#include "ThreadHandlerJoinResultMessage.h"
#include "../../Global/ClientGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "../../UnrealClient.h"
#include "../../Global/ClientBlueprintFunctionLibrary.h"

// DB�� �����ϴ���
// �����ϴ���
// ���������� ��� ��Ŷ�� ������ �ϱ���
// ���δ� �̾ȿ��� �������� �ϰ�
// ����� �ܺη� ��������� �ȵ˴ϴ�.

// ��� �̷��� �ϰ������ �����ϸ� ū�ϳ��ϴ�.
// �ܿ�� ���� �ƴ϶� �ڵ带 §����� �ǵ��� �ľ��ض�.
// ���� ��������� ���ϴ� �̴ϴ�.
ThreadHandlerJoinResultMessage::ThreadHandlerJoinResultMessage(std::shared_ptr<JoinResultMessage> _JoinResultMessage)
	: JoinResultMessage_(_JoinResultMessage)
{
	// UGameplayStatics::
}

void ThreadHandlerJoinResultMessage::Init(UClientGameInstance* _Inst, UWorld* _World)
{
	Inst_ = _Inst;
	World_ = _World;
}


void ThreadHandlerJoinResultMessage::Start()
{
	if (EGameServerCode::OK == JoinResultMessage_->Code)
	{
		UE_LOG(ClientLog, Log, TEXT("%S(%u) > Successed  to sign up."));
		return;
	}

	else if(EGameServerCode::JoinError == JoinResultMessage_->Code)
	{
		UE_LOG(ClientLog, Log, TEXT("%S(%u) > Failed to sign up."));
		return;
	}

	// �α��� ui
}

