// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	MYSQL myCont;
    MYSQL_RES *result=NULL;
    MYSQL_ROW sql_row;
    MYSQL_FIELD *fd;
    char column[32][32];
    int res;
    mysql_init(&myCont);
	// localhost:服务器 root为账号密码 test为数据库名 3306为端口  
	if(mysql_real_connect(&myCont, "124.205.118.164","pss","pss","test",10019,NULL,0))  
	{  
		cout<<"connect succeed!"<<endl;
        mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
        res=mysql_query(&myCont,"select * from commodity");//查询
        if(!res)
        {
            result=mysql_store_result(&myCont);//保存查询到的数据到result
            if(result)
            {
                int i,j;
                cout<<"number of result: "<<(unsigned long)mysql_num_rows(result)<<endl;
                for(i=0;fd=mysql_fetch_field(result);i++)//获取列名
                {
                    strcpy_s(column[i],fd->name);
                }
                j=mysql_num_fields(result);
                for(i=0;i<j;i++)
                {
                    printf("%s\t",column[i]);
                }
                printf("\n");
				int ii=0;
				ofstream write("at.txt",ios::app);
                while(sql_row=mysql_fetch_row(result))//获取具体的数据
                {
                    for(i=1;i<2;i++)
                    {
                        write<<sql_row[i]<<endl;
						ii++;
                    }
					
                    printf("\n");
                }cout<<ii<<endl;
            }
        }
        else
        {
            cout<<"query sql failed!"<<endl;
        }
    }
    else
    {
        cout<<"connect failed!"<<endl;
    }
    if(result!=NULL) mysql_free_result(result);//释放结果资源
    mysql_close(&myCont);//断开连接
	

	system("pause");
    return 0;
}
