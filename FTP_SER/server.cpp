#include"server.h"
//#include<regex>
#include<string>
#include<regex.h>
#define SER_PORT 7000
#define path "/bin/"
#include"my_sql.h"
void *thread_fun(void *arg);
class Mysql;
Mysql mysql;
Server::Server()
{
	//mysql.mpcon =mysql_init((MYSQL *)0);//初始化数据库

}
void Server::server_start(Mysql sql)
{
	mysql =sql;
	printf("create sockfd...\n");
	sockfd =socket_create();
	handle_message(sockfd);

}
int Server::socket_create()//创建套接字
{
	int sockfd =socket(AF_INET,SOCK_STREAM,0);
	if(sockfd ==-1)
		return -1;

	struct sockaddr_in saddr;
	memset(&saddr,0,sizeof(saddr));
	saddr.sin_family =AF_INET;
	saddr.sin_port =htons(SER_PORT);
	saddr.sin_addr.s_addr =htonl(INADDR_ANY);

	int res =bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	printf("res =%d\n",res);
	if(res ==-1)
		return -1;
	listen(sockfd,5);
	printf("start listening...\n");
	return sockfd;


}

void Server::handle_message(int sockfd)
{
	printf("sockfd =%d\n",sockfd);
	struct sockaddr_in caddr;
	while(1)
	{
		socklen_t len =sizeof(caddr);
		int c =accept(sockfd,(struct sockaddr *)&caddr,&len);
		
		if(c<0)
		{
			continue;
		}
		printf("accept cli =%d\n",c);
		printf("receive port =%s \r\n",inet_ntoa(caddr.sin_addr));
		pthread_t id;
		pthread_create(&id,NULL,thread_fun,(void *)&c);
	}

}

void Server::list(char *myargv[],int c)//buff为myargv，接受消息的容器
{
	printf("start list...\n");
	/*int fd[2];
	pipe(fd);
	pid_t pid =fork();
	assert(pid!=-1);

	if(pid ==0)
	{
	
		dup2(fd[1],1);
		dup2(fd[1],2);
		
		execvp(myargv[0],myargv);
		perror("execvp error");

	}
	close(fd[1]);
	char readbuff[1024]={"ok#"};
	read(fd[0],readbuff+3,1020);
	printf("read =%s\n",readbuff);
	printf("c =%d\n",c);

	send(c,readbuff,strlen(readbuff),0);
	memset(readbuff,0,strlen(readbuff));
	close(fd[0]);*/
	printf("c=%d\n",c);
	Mysql mysql2;

	//mysql2.mp_res =mysql_store_result(mysql2.mpcon);
	//mysql2.mp_row =mysql_fetch_row(mysql2.mp_res);
	char readbuff[1024]={"ok#"};
	char *s =NULL;
	while((mysql2.mp_row =mysql_fetch_row(mysql2.mp_res)))
	{
		int i=0;
		for(;i<mysql2.mp_res->field_count;i++)
		{
			cout<<mysql2.mp_row[i]<<endl;
			s =mysql2.mp_row[i];
			cout<<mysql2.mp_row[i]<<endl;
			strcat(readbuff,s);
			strcat(readbuff,"\n");
			//cout<<readbuff[i]<<endl;
		}
		cout<<endl;
	}
	

	send(c,readbuff,strlen(readbuff),0);
	cout<<endl;

}

void Server::thread_receive_file(char *myargv[],int c)
{
	printf("name=%s,size=%s\n",myargv[1],myargv[2]);
	char *name=myargv[1];
	//sprintf(name,"/home/maomao/school/recv/%s",myargv[1]);
	char path_file[100] ="/home/maomao/school/recv/";
	strcat(path_file,name);
	printf("name=%s\n",path_file);
	int size =atoi(myargv[2]);
	int cur_num =0;
    if(size%1000==0)
	{
		cur_num =size/1000;

	}
	else
	{
		cur_num =size/1000+1;
	}

	int fd =open(path_file,O_WRONLY|O_CREAT,0777);
	if(fd==-1)
	{
		printf("open file error\n");
		return;
	}
	send(c,"ok",2,0);//发送确认信息
	
	char buff[1024]={0};
	int num=0;
	int cur_size=0;

	int cout =0;
	printf("c=%d\n",c);
	c=7;
	printf("c=%d\n",c);
	while((num=recv(c,buff,1002,0))>0)
	{
		printf("num =%d\n",num);
		printf("%s\n",buff);
		char xulie[2]="";
		xulie[0]=buff[0];
		xulie[1]=buff[1];
		//cout<<"xulie="<<xulie;
		printf("xulie=%s\n",xulie);
		int pro_xulie =atoi(xulie);//求出线程数
		printf("id =%d\n",pro_xulie);
		cout++;
		num-=2;
		printf("%s\n",buff);
		printf("len=%d\n",strlen(buff));
		cur_size+=num;
		printf("cur_size=%d\n",cur_size);
		
		printf("线程id=%d\n",pro_xulie);
		
		int off=lseek(fd,pro_xulie*1000,SEEK_SET);
		printf("偏移字节=%d\n",off);

		write(fd,buff+2,strlen(buff)-2);
		memset(buff,0,sizeof(buff));
		lseek(fd,0,SEEK_SET);
		printf("-----------------------------------=--------------\n");
		printf("cur_size=%d\n",cur_size);
		if(cur_size>=size )
		{
			break;
		}


	}
	mysql.add(size,name);//插入数据库
	printf("cur_total=%d\n",cur_size);
	printf("total=%d\n",size);
	close(fd);

}
void Server::receive_file(char *myargv[],int c)
{
	printf("name =%s,size=%s\n",myargv[2],myargv[3]);
	char *name=myargv[2];
	//sprintf(name,"/home/maomao/school/recv/%s",myargv[2]);
	printf("name=%s\n",name);
	int size =atoi(myargv[3]);
	printf("size=%d\n",size);
	int fd =open(name,O_WRONLY|O_CREAT,0777);
	if(fd ==-1)
	{

		printf("open error\n");
		return ;
	}
	char ok[256]={0};
	sprintf(ok,"ok#%s",myargv[1]);
	printf("ok =%s",ok);
	send(c,ok,strlen(ok),0);
	int num =0;
	int cur_size =0;
	char recvbuff[128]={0};
	while((num =recv(c,recvbuff,127,0))>0)
	{
		cur_size +=num;
		write(fd,recvbuff,num);
		if(cur_size ==size)
		{
			break;
		}

	}
	close(fd);

}

void Server::send_file(char *myargv[],int c)
{
	printf("down_c =%d\n",c);
	printf("name1=%s\n",myargv[1]);
	char *name =myargv[1];
	char path_down[100] ="/home/maomao/school/recv/";
	strcat(path_down,name);
	cout<<path_down<<endl;
	int fd =open(path_down,O_RDONLY);
	if(fd ==-1)
	{
		printf("file open fail\n");
		return ;
	}
	int size =lseek(fd,0,SEEK_END);
	lseek(fd,0,SEEK_SET);
	char st_buff[32]={0};
	sprintf(st_buff,"ok#%d",size);
	send(c,st_buff,strlen(st_buff),0);
	if(size==0)
	{return;}
	char status[32]={0};
	if(recv(c,status,31,0)<=0)
	{
		return;
	}
	if(strcmp(status,"ok")!=0)
	{
		return;
	}

	char sendbuff[256]={0};
	int n=0;
	while((n=read(fd,sendbuff,256))>0)
	{
		printf("n=%d\n",n);
		send(c,sendbuff,n,0);
	}
	close (fd);
	printf("send finish\n");	

}

void * thread_fun(void *arg)
{
	Server ser;
	int c =*(int*)arg;
	
	while(1)
	{
		char buff[128]="";
		int n =recv(c,buff,127,0);
		printf("recv =%s\n",buff);
		printf("c=%d\n",c);
		if(n<0)
			break;
		else
		{
			printf("recv =%s\n",buff);
		}
		char *myargv[50]={0};
		char *ptr =NULL;
		char *p =strtok_r(buff," ",&ptr);
		if(p==NULL)
			continue;
		myargv[0]=p;/////得到指令list ，put，download
		int i =1;
		while((p=strtok_r(NULL," ",&ptr))!=NULL)
		{
			myargv[i++]=p;
		}
	/*	switch(myargv[0][0])
		{
			case 'l':ser.list();break;
			case 'u':ser.receive_file();break;
			case 'd':ser.send_file();break;
		}
	*/
		printf("argv =%s\n",myargv[0]);
		if(strcmp(myargv[0],"ls")==0)
		{
			ser.list(myargv,c);

		}
		else if(strcmp(myargv[0],"upload")==0)
		{
			printf("start in to upload\n");
			ser.thread_receive_file(myargv,c);

		}
		else if(strcmp(myargv[0],"download")==0)
		{
			printf("start to download\n");
			ser.send_file(myargv,c);

		}
		else
			break;
	}
}

int Server::getsocket()
{
	return sockfd;
}
