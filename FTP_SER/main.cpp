#include"server.h"
#include"my_sql.h"
int main()
{
	Mysql sql;
	sql.check_file();
	Server ser;
	ser.server_start(sql);
	return 0;

}
