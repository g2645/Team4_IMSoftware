#ifndef MYSQLITE_HPP
#define MYSQLITE_HPP

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include "string"

/*���ݿ��ʼ��*/
sqlite3* DbInit()
{
	sqlite3 *db = NULL;
	int ret;
	ret = sqlite3_open("mmm.db", &db);
	if (ret != SQLITE_OK)
	{
		perror("sqlite3_open");
	}

	return db;
}

/*�����û���Ϣ��userinfo*/
void create_table(sqlite3 *db)
{
	char *errmsg = NULL;
	char *sql = NULL;
	int ret;
	sql = "create table if not exists userinfo(name text primary key, password text); ";
	ret = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
	if (ret != SQLITE_OK)
	{
		printf("create table error : %s\n", errmsg);
	}
}

/*���û���Ϣ�������¼*/
void insert_record(sqlite3 *db, char *name, char *password)
{
	char sql[100];
	char *errmsg = NULL;
	sprintf(sql, "insert into userinfo values('%s', '%s'); ", name, password);
	if (SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, &errmsg))
	{
		printf("insert record error : %s\n", errmsg);
	}
}

/*���û���Ϣ��ɾ����¼*/
void delete_record(sqlite3 *db, char *name, char *password)
{
	char sql[100];
	char *errmsg = NULL;
	sprintf(sql, "delete from userinfo where name = '%s'; ", name, password);
	if (SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, &errmsg))
	{
		printf("delete record error : %s\n", errmsg);
	}
}

/*�û���Ϣ����ѯ�û�*/
bool search_contact(sqlite3 *db, char *name, char *password)
{
	char sql[100];
	char *errmsg;
	int nrow, ncolumn;
	char **azresult;
	int i;
	int ret;

	sprintf(sql, "select name from userinfo where name = '%s' and password = '%s';", name, password);
	if (SQLITE_OK != sqlite3_get_table(db, sql, &azresult, &nrow, &ncolumn, &errmsg))
	{
		printf("log in failed : %s\n", errmsg);
		return false;
	}
	else
	{
		return true;
	}
}

/*�û���Ϣ����ѯ��������*/
std::string search_name(sqlite3 *db)
{
	std::string s;
	char *sql;
	char *errmsg;
	int nrow, ncolumn;
	char **azresult;
	int i;
	int ret;
	char a[] = { "log in��" };

	sql = "select name from userinfo;";
	if (SQLITE_OK != sqlite3_get_table(db, sql, &azresult, &nrow, &ncolumn, &errmsg))
	{
		printf("log in failed : %s\n", errmsg);
		exit(0);
	}

	for (int i = ncolumn; i<(nrow + 1)*ncolumn; i++)
	{
		s.append((char*)azresult[i]);
		s.append("#");
		if (!((i + 1) % ncolumn))
			putchar(10);
	}
	return s;
}

/*���������¼��liao*/
void create_table_l(sqlite3 *db)
{
	char *errmsg = NULL;
	char *sql = NULL;
	int ret;
	sql = "create table if not exists liao(fname text, message text,jname text); ";
	ret = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
	if (ret != SQLITE_OK)
	{
		printf("create table error : %s\n", errmsg);
	}
}

/*�����¼����������*/
void insert_record_l(sqlite3 *db, char *fname, char *message,char *jname)
{
	char sql[100];
	char *errmsg = NULL;
	sprintf(sql, "insert into liao values('%s', '%s','%s'); ", fname, message,jname);
	if (SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, &errmsg))
	{
		printf("insert record error : %s\n", errmsg);
	}
}

/*�����¼�����������¼*/
std::string search_message_l(sqlite3 *db,char *fname,char *jname)
{
	char sql[100];
	std::string s;
	char *errmsg;
	int nrow, ncolumn;
	char **azresult;
	int i;
	int ret;
	sprintf(sql, "select message from liao where fname = '%s' and jname = '%s'; ", fname,jname);
	if (SQLITE_OK != sqlite3_get_table(db, sql, &azresult, &nrow, &ncolumn, &errmsg))
	{
		printf("select in failed : %s\n", errmsg);
		exit(0);
	}

	for (int i = ncolumn; i<(nrow + 1)*ncolumn; i++)
	{
		s.append((char*)azresult[i]);
		s.append("#");
		if (!((i + 1) % ncolumn))
			putchar(10);
	}
	return s;
}

#endif //MYSQLITE_HPP