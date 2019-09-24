#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
struct mealcard{
     char num[15];
     int info;
     char name[20];
     double money;
}students[100];//建立一个饭卡信息的结构
int i=0;//记录学生个数
int count;//记录饭卡数量
int info;//判断是否挂失，1代表挂失,代表没有挂失
char num[15];//饭卡卡号
char name[20];//学生名字
double money;//金额
FILE *fp;

void creat();//创建饭卡信息文件
void buy();//输入前后饭卡余额
void con();//加钱，显示前后金额
void add();//添加新饭卡
void move();//注销没有用的饭卡
void set();//设置挂失信息，包括注销挂失和加挂失饭卡
void look();//查看饭卡信息
void puanduan();//判断饭卡号格式 是否正确
void read_file();//判断文件是否存在，读出文件信息 
int main(void)
{
     int choice;
     read_file();
     
     do 
     {   
          printf("  |------------主菜单------------|\n");
          printf("  |                              |\n");
          printf("  |----请输入要选择的操作编号----|\n");
          printf("  |----1---新建立饭卡文件--------|\n");
          printf("  |----2-------买饭--------------|\n");
          printf("  |----3-------充钱--------------|\n");
          printf("  |----4------添加新饭-----------|\n");
          printf("  |----5------注销旧饭卡---------|\n");
          printf("  |----6---添加挂失与解除挂失----|\n");
          printf("  |----7---查看所有信息----------|\n");
          printf("  |----0------退出系统-----------| \n");
          printf("  |------------------------------|\n");
          scanf("%d",&choice);
     switch(choice)
     {
          case 0:printf("--非常感谢您使用本软件,软件已经正常退出,按任意键可结束\n");
                 printf("--如果对我们软件有什么好的意见，欢迎提出，谢谢\n");
                 break;
          case 1:creat(); break;
          case 2:buy(); break; 
          case 3:con();break;
          case 4:add();break;
          case 5:move();break;
          case 6:set(); break;
          case 7:look();break;
          default: exit(0);
     }
     }while(choice!=0); 

     return 0;
}
void read_file()//判断文件是否存在，读出文件信息 
{
	 if((fp=fopen("card.dat.txt","r+"))!=NULL)//判断是否建立了文件
     {
          printf("文件已经存在\n\n");
          fseek(fp,0,2);//指向文件最后的位置
        if(ftell(fp)>0)//指针指向刚才定位的位置，判断文件是否非零
        {
          rewind(fp);//定位到首部 
          printf("并且文件已经存有以下学生饭卡号\n\n如果要继续【创建文件】信息请按1，要查看【金额】等信息请按7，谢谢\n");
          while(!feof(fp))
          {
          	fscanf(fp,"%s%s%lf%d\n",students[i].num,students[i].name,&students[i].money,&students[i].info);  
            printf("%s\n",students[i].num);//输出已经有的学生姓名
            i++;//记录个数
          }         
          if(fclose(fp))
          {
               printf("文件关闭失败\n");
               exit(0);
          }
        } 
         
      }
    else;
}
void puanduan()
{
	int j,c;
	 do//判断输入饭卡格式对不对 
      {
      	int n=strlen(num);
      	for(j=0;j<n;j++)
      	{
      		if(num[j]>='0'&&num[j]<='9')
      		{
      			c=1;
			}
			else
			{
				c=0;
				printf("您输入的饭卡号格式不对，请重新输入，谢谢\n");
				scanf("%s",num);
				break;
			}
		}
	
	  }while(c==0);
}
void creat()
{
		int k,a=0,b=0,c,j;        
    if((fp=fopen("card.dat.txt","w"))==NULL)//打开文件 
	{
		printf("文件打开错误\n");
		exit(0);
	}
     printf("请输入卡号，0表示停止创建饭卡信息，返回主菜单\n");
     printf("并且输入卡号不得超过15位数\n");
     
     do{
       scanf("%s",num);
      
	   puanduan();//调用判断函数判断饭卡号是否合法 
      for(k=0;k<i;k++)
	  {
		if(strcmp(students[k].num,num)==0)
		{
		   	b=1;
		   	printf("此卡号已经被注册了,请重新输入饭卡号，谢谢\n");
		   	break;
		}
		else b=0; 
	  }
   }while(b==1);
		   
	 while(1)
	 {
		
		 strcpy(students[i].num,num);
		 
		 printf("请输入你的姓名，谢谢\n");
		 scanf("%s",name);
		 strcpy(students[i].name,name);
		 printf("请输入你的饭卡钱，谢谢\n");
		 scanf("%lf",&money);
		 while(money<0)
		 {
		 	printf("输入的金额必须为正数\n");
		 	printf("请重新输入你的饭卡钱，谢谢\n");
		 	scanf("%lf",&money);
		 }
		 students[i].money=money;
		 printf("请输入你的挂失信息，0代表没有挂失，1代表挂失\n");
		 scanf("%d",&info);
		  while(info!=0&&info!=1)
		  {
		  	printf("挂失信息只能用1和0表示，请不要输入其他数字，谢谢\n");
		  	printf("请重新输入你的挂失信息，0代表没有挂失，1代表挂失\n");
		  	scanf("%d",&info);
		  }
		  students[i].info=info; 
		  fprintf(fp,"%s %s %.0f %d\n",students[i].num,students[i].name,students[i].money,students[i].info);//改的 
		  i++;// 
	
		   do
		   {
		   	printf("请接着输入你的卡号，0代表停止输入卡号\n");
		   	scanf("%s",num);
		   	puanduan();
		   if(strcmp(num,"0")==0)
		   {
		 	return ;
		   } 
		   	for(k=0;k<i;k++)
		   	{
		   	 if(strcmp(students[k].num,num)==0)
		   	 {
		   	 	a=1;
		   	 	printf("此卡号已经被注册了\n");
		   	 	break;
			 }
		   
		   else 
		   a=0; 
   	      }
	  } while(a==1);
	  
   }

	 if(fclose(fp))
	 {
		printf("文件关闭失败\n");
		exit(0);
 	 }
 	 printf("文件信息创建成功,返回主菜单\n\n"); 
    
    
}

void buy()//买饭 
{
	int j,flag=-1,sum=0,k;
	 if(i==0)
	 {
	 	printf("请先建立饭卡文件，谢谢\n");
	 	return ;
	 }
	if((fp=fopen("card.dat.txt","r+"))==NULL)//打开文件 
	{
		printf("文件打开错误\n");
		exit(0);
	}
	do
	 {
	 	printf("请输入你的卡号，并且不能超过15位数，0代表停止【买饭】，返回主菜单\n");
	 	scanf("%s",num);
	 	puanduan();
		if(strcmp(num,"0")==0)
		{
		 	return ;
		} 
	 	
	for(j=0;j<i;j++)//查找饭卡 
	{
		if(strcmp(students[j].num,num)==0)
		{
			flag=j;
			break;
		}
	}
		if(flag==-1)
		{
		printf("找不到该卡号，请重新输入，谢谢\n");
		sum++;	
		}
		if(sum==5)//限定输入次数 
		{
			printf("您输入的卡号已经达到5次了，系统将返回主菜单\n");
			return ;
		}		 
   }while(flag==-1);
        if(students[flag].info==1)//判断是否冻结 
        {
   	     printf("您输入的卡号已经冻结（挂失）\n");
   	     return ;
         }
         else if(students[flag].money<5)
         {
         	printf("余额不足,请加钱后再使用，谢谢\n");
         	return ;
		 }
		 else
		 {
		 	printf("请输入你要买饭的饭钱\n");
		 	scanf("%lf",&money);
		 }
		 while(money<0)
		 {
		 	printf("输入错误：输入的饭钱必须为正数\n");
		 	printf("请重新输入你的买饭钱\n");
		 	scanf("%lf",&money);
		 }
		 if(students[flag].money>=money)//输出买饭的前后金额 
		 {
		 	printf("买饭前:\n");
		 	printf("饭卡号：%s  金额：%.2f\n",students[flag].num,students[flag].money);
		 	students[flag].money=students[flag].money-money;
		 	printf("买饭后:\n");	
		 	printf("饭卡号：%s 金额：%.2f\n\n",students[flag].num,students[flag].money);
	        printf("您此次消费成功了,自动返回主菜单\n\n");
	     }
		else
		  {
		  	printf("余额不足，请加钱\n");
		  	return;
		  }
		for(j=0;j<i;j++)//写入文件 
	    {
		fprintf(fp,"%d %s %.0f %d\n",students[j].num,students[j].name,students[j].money,students[j].info);	
	    }
		if(fclose(fp))
   	    {
		printf("文件关闭失败\n");
		exit(0);
	    }
}

void con()//充值 
{
	 int j,flag=-1,sum=0; 
	 if(i==0)
	 {
	 	printf("请先建立饭卡文件，谢谢\n");
	 	return ;
	 }
	 else
	 {
	if((fp=fopen("card.dat.txt","w+"))==NULL)
	{
		printf("文件打开错误\n");
		exit(0);
	}
		  
	do
	 {
	 	printf("请输入你的卡号，并且不能超过15位数,输入0代表停止【充值】，返回主菜单\n");
	 	scanf("%s",num);
	 	puanduan();
	 	if(strcmp(num,"0")==0)//// 
		{
		 	return ;
		} 
	 
 	    for(j=0;j<i;j++)//查找饭卡 
	    {
		if(strcmp(students[j].num,num)==0)
		{
			flag=j;
			break;
		}
	    }
		if(flag==-1)
		{
		printf("找不到该卡号，请重新输入，谢谢\n");
		sum++;	
		}
		if(sum==5)
		{
			printf("您输入的卡号已经达到5次了，系统将返回主菜单\n");
			return ;
		}	 
   }while(flag==-1);
        if(students[flag].info==1)
        {
   	     printf("您输入的卡号已经冻结（挂失）\n");
   	     return ;
         }
         else
		 {
		 	printf("输入您需要【充值】的金额\n");
		 	scanf("%lf",&money); 
		    while(money<0)
		    {
		 	printf("输入错误：输入的金额必须为正数\n");
		 	printf("请重新输入你的充值金额\n");
		 	scanf("%lf",&money);
		    }
		    printf("充值前：\n");
		 	printf("饭卡号： %s 金额：%.2f\n",students[flag].num,students[flag].money);
		 	
		 	students[flag].money=students[flag].money+money;
		 	
		 	printf("充值后：\n");	
		 	printf("饭卡号：%s 金额：%.2f\n\n",students[flag].num,students[flag].money);
            for(j=0;j<i;j++)
  	        {
		     fprintf(fp,"%s %s %.0f %d\n",students[j].num,students[j].name,students[j].money,students[j].info);	
	        }

	        if(fclose(fp))
	        {
	         printf("文件关闭失败\n");
	          exit(0);
	        } 
		  
	         printf("您此次充值成功了,将返回主菜单\n\n");

		   }
	} 
}
void add()
{
	int j,flag=-1,sum=0; 
	
	if(i==0)
	{
		printf("请先建立饭卡文件\n");
		return ;
		
	}
	else if(i>100)
	{
		printf("数据库已经存满\n");
		return ;
		 
	}
	if((fp=fopen("card.dat.txt","w+"))==NULL)
	{
		printf("文件打开错误\n");
		exit(0);
	}
		  
	printf("请输入你要【添加】的卡号，并且不能超过15位数，0代表停止添加，返回主菜单\n");
	do
	{  
		scanf("%s",num);
		puanduan();
        if(strcmp(num,"0")==0)
		{
		   	return ;
		} 
	 	
 	    for(j=0;j<i;j++)//查找饭卡 
		if(strcmp(students[j].num,num)==0)
		{
			flag=1;
			sum++;
			printf("此号已经被注册,请重新输入，谢谢\n");
			break;
		}
		else
		flag=0;
	    
		if(sum==5)
		{
			printf("您输入的卡号已经达到5次了，系统将返回主菜单\n");
			return ;
		}	 
   }while(flag==1);
   strcpy(students[i].num,num); 
   printf("请输入您的姓名\n");
   scanf("%s",name);
   strcpy(students[i].name,name);
   printf("请输入您的初始饭卡钱\n");
   scanf("%lf",&money);
    while(money<0)
		    {
		 	printf("输入错误：输入的金额必须为正数\n");
		 	printf("请重新输入你的金额\n");
		 	scanf("%lf",&money);
		    }
		    students[i].money=money;
		    printf("请输入您的挂失信息,0代表没有挂失，1代表已经挂失\n");
		    scanf("%d",&info);
		    students[i].info=info;
		    i++;//计数饭卡数量 
		for(j=0;j<i;j++)
		{
		   fprintf(fp,"%s %s %.0f %d\n",students[j].num,students[j].name,students[j].money,students[j].info);	
		}
		
		if(fclose(fp))
	    {
		printf("文件关闭失败\n");
		exit(0);
	    } 
		printf("操作成功,将返回主菜单\n\n");
}
void move()//注销饭卡 
{
	int j,flag=-1,sum=0,k; 
	if(i==0)
	 {
	 	printf("请先建立饭卡文件，谢谢\n");
	 	return ;
	 }
	if((fp=fopen("card.dat.txt","w+"))==NULL)
		 	{
		 		printf("文件打开失败\n");
				 exit(0); 
			 }
	 do
	 {
	 	printf("请输入你要【注销】的卡号，并且卡号不能超过15位数,0代表取消操作\n");
	 	scanf("%s",num);
	 	puanduan();
	 	if(strcmp(num,"0")==0)
		{
		   	return ;
		} 
	 
		
	for(j=0;j<i;j++)//查找饭卡 
	{
		if(strcmp(students[j].num,num)==0)
		{
			flag=j;
			i--; //注销了i也要变化，减少一个 
			break;
		}
	}
		if(flag==-1)
		{
		printf("找不到该卡号，请重新输入，谢谢\n");
		sum++;	
		}
		if(sum==5)
		{
			printf("您输入的卡号已经达到5次了，系统将返回主菜单\n");
			return ;
		}	 
   }while(flag==-1);
   for(k=flag;k<i;k++)//全部向前移一个单位 
   {
   	students[k]=students[k+1];
    }
    for(j=0;j<i;j++)
	{
		   fprintf(fp,"%s %s %.0f %d\n",students[j].num,students[j].name,students[j].money,students[j].info);	
	}

	if(fclose(fp))
	{
	printf("文件关闭失败\n");
	exit(0);
	} 
   printf("操作成功，将返回主菜单\n\n");
	    
}
void set()// 添加或解除挂失 
{
	int j,flag=-1,info1,sum=0,k;
	if(i==0)
	
	{
		printf("请先建立文件,谢谢");
		return ; 
	}
    if((fp=fopen("card.dat.txt","w+"))==NULL)
	{
		printf("文件打开错误\n");
		exit(0);
	}
	do
	 {
	 	printf("请输入你要【添加或者解除挂失】的卡号，并且卡号不能超过15位数，0代表取消操作返回菜单\n");
	 	scanf("%s",num);
	 	puanduan();
	 	if(strcmp(num,"0")==0)
		{
		   	return ;
		} 
	 	
 	    for(j=0;j<i;j++)//查找饭卡 
	    {
		if(strcmp(students[j].num,num)==0)
		{
			flag=j;
			break;
		}
	    }
		if(flag==-1)
		{
		printf("找不到该卡号，请重新输入，谢谢\n");
		sum++;	
		}
		if(sum==5)
		{
			printf("您输入的卡号已经达到5次了，系统将返回主菜单\n");
			return ;
		}	 
   }while(flag==-1);
   printf("请输入您要改动的挂失信息，0代表没有挂失，1代表挂失\n");//改变挂失信息 
   scanf("%d",&info1);
   while(info1!=0&&info1!=1)
   {
   	printf("挂失信息输入不对，请重新输入\n");
   	scanf("%d",&info1);
   }
   students[flag].info=info1;
    for(j=0;j<i;j++)//写入文件 
	{
		fprintf(fp,"%s %s %.0f %d\n",students[j].num,students[j].name,students[j].money,students[j].info);	
	}

	if(fclose(fp))
	{
	printf("文件关闭失败\n");
	exit(0);
	} 
    printf("操作成功,将返回主菜单\n\n"); 

}
void look()//查看所有文件信息 
{
	int s=0,k;
	if(i==0)
	
	{
		printf("请先建立文件,谢谢\n");
		return ; 
	}
	if((fp=fopen("card.dat.txt","r+"))==NULL)
	{
		printf("文件打开错误\n");
		exit(0);
	}
	printf("文件所有信息如下，其中0代表没有挂失，1代表挂失\n");
           for(s=0;s<i;s++)
           {
		   
			 fscanf(fp,"%s%s%lf%d",students[s].num,students[s].name,&students[s].money,&students[s].info);//读出文件呢全部信息到结构数组中 
			 if(strcmp(students[s].num,"0")==0)
			 continue;
			 printf("饭卡号：%s\n姓名：%s\n金额： %.2f\n挂失信息：%d\n\n",students[s].num,students[s].name,students[s].money,students[s].info);

		      } 
		      if(fclose(fp))
		      {
		      	printf("关闭文件失败\n");
		      	exit(0);
			  }
}
