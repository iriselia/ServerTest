#include "Public/Detail/SQLDatabase.h"
#include "Public/Detail/SQLOperation.h"

#if PLATFORM_WINDOWS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif


BEFORE_MAIN()
{
	GCore.Init();
}

int main()
{
	//GConsole.Print("abcd");

	{
		GConfig.Load("DatabaseTest.ini");
		bool Res;
		SQLConnectionPoolInfo dbInfo;
		Res |= GConfig.GetString("DatabaseTest.LoginDatabase.Hostname", dbInfo.Hostname);
		Res |= GConfig.GetString("DatabaseTest.LoginDatabase.Username", dbInfo.Username);
		Res |= GConfig.GetString("DatabaseTest.LoginDatabase.Password", dbInfo.Password);
		Res |= GConfig.GetString("DatabaseTest.LoginDatabase.Schema", dbInfo.Schema);
		Res |= GConfig.GetUInt("DatabaseTest.LoginDatabase.Port", dbInfo.Port);
		Res |= GConfig.GetUInt("DatabaseTest.LoginDatabase.ConnectionCount", dbInfo.ConnectionCount);

		enum Schemas
		{
			ServerTest
		};

		GDatabase.AddSchema(ServerTest, dbInfo);
		GDatabase.InitConnection();
		SQLOperation operation(GDatabase.GetFreeConnectionByType(ServerTest));
		operation.SetStatement("DROP TABLE IF EXISTS debug_example");
		//operation.SetStatement("CREATE TABLE debug_example (id int not null, my_name varchar(50), PRIMARY KEY(id))");
		//operation.SetStatement("SELECT `sex`, `age`, `name` FROM `user` WHERE `id` = ?");
		operation.SetParamInt32(0, 1);
		for (int i = 0; i < 1000; i++)
		{
			operation.Call();
		}
		//GDatabase.AddTask(&operation);

		while (!operation.Completed())
		{
			int i = 0;
		}


		/*
		Database.Schemas[enum::LoginDatabase];
		SQLOperation op(LoginConnectionPool);
		op.SetPreparedStatement(enum::GET_CHARACTERS);
		op.SetParam(0, xxx);
		GDatabase.AsyncQuery(op);
		//Database.Connect();
		SQLConnection dbConn(dbInfo);
		char* sql = "SELECT `sex`, `age`, `name` FROM `user` WHERE `id` = ?";

		SQLOperation op(&dbConn);
		std::string test = "abc";// "tempString1tempString2tempString3tempString4tempString5tempString6";
		op.SetStatement(sql);
		op.MoveParamString(0, std::move(test));
		op.SetParamInt32(0, 1);
		memset(&test, 0, sizeof(std::string));

		//dbConn.AddTask(&op);
		//SQLThread worker(&dbConn);

		while (!op.IsDone());

		while (op.GetNextRowOfResultSet())
		{
			int32 a = op.GetResultInt32(0);
			int32 b = op.GetResultInt32(1);
			std::string c = op.GetResultString(2);
			std::cout << "Sex: " << a << ", Age: " << b << ", Name: " << c << std::endl;
		}
		*/

	}
#if PLATFORM_WINDOWS
	_CrtDumpMemoryLeaks();
#endif
}