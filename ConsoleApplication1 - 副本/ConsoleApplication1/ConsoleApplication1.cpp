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
	// localhost:������ rootΪ�˺����� testΪ���ݿ��� 3306Ϊ�˿�  
	if(mysql_real_connect(&myCont, "124.205.118.164","pss","pss","test",10019,NULL,0))  
	{  
		cout<<"connect succeed!"<<endl;
        mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
        res=mysql_query(&myCont,"select * from commodity");//��ѯ
        if(!res)
        {
            result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
            if(result)
            {
                int i,j;
                cout<<"number of result: "<<(unsigned long)mysql_num_rows(result)<<endl;
                for(i=0;fd=mysql_fetch_field(result);i++)//��ȡ����
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
                while(sql_row=mysql_fetch_row(result))//��ȡ���������
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
    if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
    mysql_close(&myCont);//�Ͽ�����
	

	system("pause");
    return 0;
}
