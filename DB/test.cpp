#include "mysqlite.hpp"

int main()
{
	sqlite3 *db = NULL;
	int ret;
	ret = sqlite3_open("mmm.db", &db);
	if (ret != SQLITE_OK)
	{
		perror("sqlite3_open");
		return -1;
	}
	
	create_table(db);

	insert_record(db, "m", "5");

	insert_record(db, "n", "6");

	delete_record(db, "m", "5");

	search_contact(db, "n", "6");

	return 0;
}