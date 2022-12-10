// MySQLLearn.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <winsock2.h>
#include <iostream> 
#include "mysql.h"
#include <vector>
#pragma comment(lib, "libmysql.lib")
#pragma comment(lib, "wsock32.lib")
using namespace std;
MYSQL conn;
bool QueryDaraBase(void);
bool DeleteQueryBase(void);
bool QueryStoreProcess(void);
int main()
{
	//char sql[1024];
	//int res =1;
	//mysql_init(&conn);
	//MYSQL* temp = mysql_real_connect(&conn, "localhost", "hed", "666", "test", 3306, NULL, CLIENT_FOUND_ROWS);
	//if (temp)
	//{
	//	mysql_query(&conn, "set names gbk");
	//	printf("connect success");
	//	cout << endl;
	//	//sprintf_s(sql, "insert into student values(113,'小红',19);");
	//	res = mysql_query(&conn, "insert into student values(113,'小智',10);");
	//	if (!res)
	//	{
	//		cout << "query success" << endl;
	//	}
	//	else 
	//	{
	//		cout << "query fail" << endl;
	//	}
	//}
	//else {
	//	cout << "connect fail!" << endl;
	//}
	//mysql_close(&conn);
	//QueryDaraBase();
	//DeleteQueryBase();
	QueryStoreProcess();
	vector<DWORD> vecTime;
	for(int i=0;i<10;++i)
	{ 
		vecTime.emplace_back(i);
	}
    return 0;
	//cin >> res;
}

bool QueryDaraBase()
{
	
	int res;
	MYSQL_RES *result = NULL;
	MYSQL_FIELD *field = NULL;
	mysql_init(&conn);
	
	//222555yq为数据库的进入密码，yg_sql为数据库名
	if (mysql_real_connect(&conn, "localhost", "hed", "666", "test", 3306, NULL, CLIENT_FOUND_ROWS))
	{
		
		cout << "connect success!" << endl;
		mysql_query(&conn, "set names gbk");
		res = mysql_query(&conn, "select * from student"); //读取数据库yg_sql的yg_user_images表中图片路径字段下的数据（路径）
																		//判断是否读取成功
		if (res !=0)
			cout << "error" << endl;
		else
			cout << "OK" << endl;

		
		//保存结果    
		result = mysql_store_result(&conn);
		//路径数据的个数
		int rowcount = mysql_num_rows(result);
		cout << rowcount << endl;
		//字段的个数
		int fieldcount = mysql_num_fields(result);
		cout << fieldcount << endl;
		//显示所有字段
		for (int i = 0; i < fieldcount; i++)
		{
			field = mysql_fetch_field_direct(result, i);
			cout << field->name << "\t\t";
		}
		cout << endl;
		//显示各个字段下的所有数据
		MYSQL_ROW row = NULL;
		row = mysql_fetch_row(result);
		while (NULL != row)
		{
			for (int i = 0; i<fieldcount; i++)
			{
				cout << row[i] << "\t\t";
			}
			cout << endl;
			row = mysql_fetch_row(result);
		}
		mysql_close(&conn);
	}
	return true;
}

bool DeleteQueryBase()
{
	mysql_init(&conn);
	MYSQL_RES* result = NULL;
	MYSQL_FIELD* pField = NULL;
	int ret = 1;
	if (mysql_real_connect(&conn, "localhost", "hed", "666", "test", 3306, NULL, CLIENT_FOUND_ROWS))
	{
		mysql_query(&conn, "set names gbk");
		cout << "connect success" << endl;
		ret = mysql_query(&conn, "delete from student where uid=112");
		ret = mysql_query(&conn, "select * from student");
		if (ret==0)
		{
			printf("query success2");
			cout << endl;
		}
		else
		{
			printf("query fail");
			cout << endl;
		}

		result = mysql_store_result(&conn);
		int rowCount = mysql_num_rows(result);    //数据量
		cout << "rowCount:" << rowCount << endl;
		int field = mysql_num_fields(result);     //字段数量
		cout << "fieldCount:" << field << endl;

		for (int i = 0; i < field; ++i)
		{
			 pField = mysql_fetch_field_direct(result, i);
			 cout << pField->name << "\t\t";
		}
		cout << endl;
		MYSQL_ROW Row = NULL;

		for (int j = 0; j < rowCount; ++j)
		{
			Row = mysql_fetch_row(result);
			for (int i = 0; i < field; ++i)
			{
				
				cout << Row[i] << "\t\t";
				
			}
			cout << endl;
		}
		
		mysql_close(&conn);
	}
	return true;
}

bool QueryStoreProcess()
{
	mysql_init(&conn);
	MYSQL_RES* result = NULL;
	MYSQL_FIELD* pField = NULL;
	int ret = 1;
	//通知服务器客户端可以发送多条语句(由分号分隔)。如果该标志为没有被设置，多条语句执行。  CLIENT_MULTI_STATEMENTS 
	if (mysql_real_connect(&conn, "localhost", "hed", "666", "test", 3306, NULL, CLIENT_MULTI_STATEMENTS))
	{
		mysql_query(&conn, "set names gbk");
		cout << "connect success" << endl;

		char query[1024] = { 0 };
		memcpy_s(query, 1024, "call proc_find_name('小智',@ret)",1024);

		ret = mysql_real_query(&conn, query, strlen(query));
		mysql_query(&conn, "select @ret");

		if (ret == 0)
		{
			cout << "query success" << endl;
		}
		else
		{
			cout << "query fail" << endl;
			return false;
		}

		result = mysql_store_result(&conn);

		MYSQL_ROW Row = NULL;
		while ((Row = mysql_fetch_row(result)))
		{
			cout << "result:" << Row[0] << endl;
		}

		mysql_free_result(result);
		mysql_close(&conn);
	}
	return true;
}