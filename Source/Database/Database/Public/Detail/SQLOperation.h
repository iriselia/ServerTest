#pragma once
#include "Private/Detail/SQLOpertion/SQLOperationParamsArchive.h"
#include "Private/Detail/SQLOpertion/SQLOperationResultSet.h"

class SQLConnection;


enum class SqlOperationFlag
{
	Sync,
	Async,
	Both,
	Neither
};

enum class SQLOperationResult
{
	Success,
	Failed,
	None,
	Count
};

class SQLOperation : public SQLOperationParamsArchive, public SQLOperationResultSet
{

private:

	// General
	SQLConnection* Connection;
	MYSQL_STMT* Statement;
	SqlOperationFlag OperationFlag;

	DISALLOW_COPY(SQLOperation);

public:

	SQLOperation(SQLConnection* conn);
	~SQLOperation();

	void Clear()
	{
		SQLOperationParamsArchive::ClearParams();
		SQLOperationResultSet::ClearResultSet();
		Statement = nullptr;
		OperationFlag = SqlOperationFlag::Neither;
		//ParamCount = 0;
		//ParamSetBitMask = 0x00000000;
		//ParamData = nullptr;
		//Storage = StatementStorage::None;
		//RowCount = 0;
		//FieldCount = 0;
		//CurrentRowCursor = 0;
		//SQLOperationResult = SQLOperationResult::None;
	}

	// init params
	void SetConnection(SQLConnection* Connection);
	void SetStatement(MYSQL_STMT* Statement);
	void SetStatement(char* StatementString);
	void SetOperationFlag(SqlOperationFlag flag);
	void Execute();
	void Call();
	bool IsDone()
	{
		if (SQLOperationResult == SQLOperationResult::Success)
		{
			return true;
		}

		return false;
	}


private:

	static uint32 SizeForType(MYSQL_FIELD* field);

	bool FetchNextRow();

};