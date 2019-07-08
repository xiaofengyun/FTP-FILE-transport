#include"my_sql.h"
#include<sys/stat.h>
#include<mysql/mysql.h>
Mysql::Mysql()
{
	mpcon =mysql_init((MYSQL *)0);

	if(!mysql_real_connect(mpcon,"127.0.0.1","root","123456",NULL,3306,NULL,0))
	{
		cerr<<"sql connect errno:"<<errno<<endl;
		return ;
	}
	//cout<<mpcon<<endl;
	
	if(mysql_select_db(mpcon,"my"))
	{
		cerr<<"select fail:errno:"<<errno<<endl;

	}
	else
	{
		printf("connect to mysql success...\n");

	}

	char cmd[100]="select file_name from ftpdata;";
	if(mysql_real_query(mpcon,cmd,strlen(cmd)))
	{
		cout<<"query fail"<<endl;
		return ;
	}

	mp_res =mysql_store_result(mpcon);
	mp_row =mysql_fetch_row(mp_res);
	//check_file();

}

void Mysql::check_file()
{
	printf("start check...\n");
	const char *strpath="/home/maomao/school/recv/";
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if((dp = opendir(strpath))==NULL)
	{
		printf("cannot open server file...\n");
		return ;
		//continue; ;
	}
	else
	{
		printf("open it success\n");
	}
	while((entry =readdir(dp))!=NULL)
	{
	//	cout<<entry->d_name<<endl;
		if(strcmp(".",entry->d_name)==0 || strcmp("..",entry->d_name)==0 )
		continue; 	
		//cout<<entry->d_name<<endl;
		char path_file [100]="/home/maomao/school/recv/";
		char name[100]="";
		sprintf(name,"%s",entry->d_name);
		strcat(path_file,name);
		printf("%s\n",path_file);
		struct stat stbuf;
		int res =stat(path_file,&stbuf);
		

		/*if(res==-1 ||(stbuf.st_mode & S_IFMT)==S_IFDIR)
		{
			continue;	
		}
		else
		{*/
			printf("%8ld  %s\n",stbuf.st_size,name);
			add(stbuf.st_size,name);
		//}

	}	
	

}
void Mysql::add(long int size,char *name)
{
	
	char cmd2[200]="";
	sprintf(cmd2,"INSERT INTO ftpdata values('%s','%d');",name,size);
	puts(cmd2);
	if(mysql_real_query(mpcon,cmd2,strlen(cmd2)))
	{
		cerr<<"0 qurey fail:errno:"<<errno<<endl;
		return ;
	}


}


