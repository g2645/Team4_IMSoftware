#ifndef MYSQLITE_HPP
#define MYSQLITE_HPP

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

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

void search_contact(sqlite3 *db, char *name, char *password)
{
	char sql[100];
	char *errmsg;
	int nrow, ncolumn;
	char **azresult;
	int i;
	int ret;
	char a[] = { "log in¡­" };

	sprintf(sql, "select name from userinfo where name = '%s' and password = '%s';", name, password);
	if (SQLITE_OK != sqlite3_get_table(db, sql, &azresult, &nrow, &ncolumn, &errmsg))
	{
		printf("log in failed : %s\n", errmsg);
		exit(0);
	}

	for (int i = 0; i < ncolumn; i++)
	{
		printf("%s", azresult[i]);
	}
	putchar(10);

	for (int i = ncolumn; i<(nrow + 1)*ncolumn; i++)
	{
		printf("%s\t", azresult[i]);
		if (!((i + 1) % ncolumn))
			putchar(10);
	}
}

#endif //MYSQLITE_HPP