#include "SQLThread.h"
#include "SQLOperation.h"

SQLThread::SQLThread() :
	SQLOperationTaskQueue(&ConnectionPool.TaskQueue),
	CancelationToken(false),
	WorkingThread(&SQLThread::Main, this)
{
}

SQLThread::~SQLThread()
{
	CancelationToken = true;

	SQLOperationTaskQueue->Cancel();

	WorkingThread.join();
}

void SQLThread::Main()
{
	while (!SQLOperationTaskQueue)
	{
		if (CancelationToken)
		{
			return;
		}
	}

	while (true)
	{
		SQLOperation* operation = nullptr;

		SQLOperationTaskQueue->WaitAndPop(operation);

		while (!operation)
		{
			if (CancelationToken)
			{
				return;
			}
		}

		operation->Call();

		if (CancelationToken)
		{
			return;
		}
	}
}
