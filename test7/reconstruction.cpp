//滤波反投影法重建图像
//陈家欢

#include<iostream>
#include<math.h>
#include"filterfuction.h"
#include"d2r.h"
#include"draw.h"
#include"input.h"
#include <fstream>

using namespace std;
int main()
{
	int i,j,l;


	//一.输入投影值

	//p为投影，有180个角度，每个角度有256个值，所以是180*256
	double **p;
	p=new double*[180];
	for(i=0;i<180;i++) p[i]=new double[256];
	for(i=0;i<180;i++)
	{
		for(j=0;j<256;j++) p[i][j]=0;
	}

	//根据平面几何，计算线积分，然后离散化。
	//shepp-logen共有10个椭圆，依次叠加到投影上。具体参数可见说明文档。

	//1
	for(i=0;i<180;i++)
	{
		for(j=0;j<256;j++) 
		{
			p[i][j]+=pinput(D2R(i+1.0)-D2R(90),j,2,0.92,0.69);
		}
	}

	//2
	for(i=0;i<180;i++)
	{
		for(j=0;j<256;j++) 
		{
			p[i][j]+=pinput(D2R(i+1.0)-D2R(90),j-sqrt(2.3552*2.3552)*cos(D2R(-90.0)-D2R(i+1.0)),-0.98,0.874,0.6624);
		}
	}
	//3
	for(i=0;i<180;i++)
	{
		for(j=0;j<256;j++) 
		{
			p[i][j]+=pinput(D2R(i+1.0)-D2R(72),j-sqrt(28.16*28.16)*cos(atan(0.0)-D2R(i+1.0)),-0.02,0.31,0.11);
		}
	}
	
	//4
	for(i=0;i<180;i++)
	{
		for(j=0;j<256;j++) 
		{
			p[i][j]+=pinput(D2R(i+1.0)-D2R(108),j+sqrt(28.16*28.16)*cos(atan(0.0)-D2R(i+1.0)),-0.02,0.41,0.16);
		}
	}
	
	//5
	for(i=0;i<180;i++)
	{
		for(j=0;j<256;j++) 
		{
			p[i][j]+=pinput(D2R(i+1.0)-D2R(90),j-sqrt(44.8*44.8)*cos(D2R(90)-D2R(i+1.0)),0.01,0.25,0.21);
		}
	}

	//6
	for(i=0;i<180;i++)
	{
		for(j=0;j<256;j++) 
		{
			p[i][j]+=pinput(D2R(i+1.0)-D2R(0),j-sqrt(12.8*12.8)*cos(D2R(90)-D2R(i+1.0)),0.01,0.046,0.046);
		}
	}

	//7
	for(i=0;i<180;i++)
	{
		for(j=0;j<256;j++) 
		{
			p[i][j]+=pinput(D2R(i+1.0)-D2R(0),j-sqrt(12.8*12.8)*cos(D2R(-90)-D2R(i+1.0)),0.01,0.046,0.046);
		}
	}

	//8
	for(i=0;i<180;i++)
	{
		for(j=0;j<256;j++) 
		{
			p[i][j]+=pinput(D2R(i+1.0)-D2R(0),j+sqrt(104.8576+5996.9536 )*cos(atan(0.605/0.08)-D2R(i+1.0)),0.01,0.046,0.023);
		}
	}

	//9
	for(i=0;i<180;i++)
	{
		for(j=0;j<256;j++) 
		{
			p[i][j]+=pinput(D2R(i+1.0)-D2R(0),j-sqrt(5996.9536 )*cos(D2R(-90)-D2R(i+1.0)),0.01,0.023,0.023);
		}
	}

	//10
	for(i=0;i<180;i++)
	{
		for(j=0;j<256;j++) 
		{
			p[i][j]+=pinput(D2R(i+1.0)-D2R(90),j-sqrt(5996.9536+ 58.9824  )*cos(atan(-0.605/0.06)-D2R(i+1.0)),0.01,0.046,0.023);
		}
	}


	//二、滤波

	//预处理
	//将投影p两边填充至180*766，即两边各增加255，以便于滤波
	//填充后存储在pa中
	double **pa;
	pa=new double*[180];
	for(i=0;i<180;i++) pa[i]=new double[766];

	for(i=0;i<180;i++)
	{
		for(j=0;j<766;j++)									
		{
			if(j<255) pa[i][j]=(p[i][0]+p[i][1])/2;
			else if(j<511) pa[i][j]=p[i][j-255];
			else pa[i][j]=(p[i][254]+p[i][255])/2;
		}
	}

	//释放p
	for(i=0;i<180;i++) delete[]p[i];
	delete[]p;

	//进行卷积滤波
	//滤波的方法就是将一个参与滤波的函数沿x轴翻转，然后依次相乘、相加。
	//由于滤波函数是偶函数，所以翻转后没有变化，故跳过了翻转这步骤
	double **pf;
	pf=new double*[180];
	for(i=0;i<180;i++) pf[i]=new double[256];

	for(i=0;i<180;i++)
	{
		for(j=0;j<256;j++)
		{
			pf[i][j]=0;
			for(l=-255;l<=255;l++) 
			{
				pf[i][j]+=pa[i][j+l+255]*h(l);
			}
		}
	}

	//释放pa
	for(i=0;i<180;i++) delete[]pa[i];
	delete[]pa;


	//三、反投影

	//a初始化，用于存放反投影的图像
	double **a;
	a=new double*[256];
	for(i=0;i<256;i++) a[i]=new double[256];
	for(i=0;i<256;i++)
	{
		for(j=0;j<256;j++)
		{
			a[i][j]=0;
		}
	}
	

	double cm,xr,d;
	int n;
	for(l=0;l<180;l++)											//选定一个投影角度
	{
		cm=127.5*(1-cos(D2R(l))-sin(D2R(l)));
		for(i=0;i<256;i++)										//在图像上的点（i,j）,找到对应投影值，通过差值求得投影值
		{														//具体推导可见说明文档	
			for(j=0;j<256;j++)
			{
				xr=cm+(i)*cos(D2R(l))+(j)*sin(D2R(l));			
				if(xr>0 && xr<255)
				{
					n=floor(xr);
					d=xr-n;
					a[i][j]+=((1-d)*pf[l][n]+d*pf[l][n+1])*3.1416/180;
				}
				else if(xr==0) a[i][j]+=pf[l][0];
				else if(xr==255) a[i][j]+=pf[l][255];
			}
		}
	}

	//a即为重建图像

	char* path = "a.txt";   //投影数据，可用matlab查看结果
	ofstream fout( path );
	for(i=0;i<180;i++)
	{
		for(j=0;j<255;j++)
		{
			fout<<a[i][j]<<" ";
		}
		fout<<endl;
	}
	fout.close(); 
	
	for(i=0;i<180;i++) delete[]pf[i];
	delete[]pf;


	//由于使用8位bmp格式的图，所以要把图像的值转换到[0,255]
	double max=a[0][0];
	double min=a[0][0];

	int **ai;
	ai=new int*[256];
	for(i=0;i<256;i++) ai[i]=new int[256];
	//找到最大、最小值
	for(i=0;i<256;i++)
	{
		for(j=0;j<256;j++) 
		{
			if(a[i][j]<min) min=a[i][j];
			if(a[i][j]>max) max=a[i][j];
		}
	}
	//把图像线性的映射到[0,255]
	for(i=0;i<256;i++)
	{
		for(j=0;j<256;j++) 
		{
			ai[i][j]=(a[i][j]-min)/(max-min)*255;
		}
	}

	for(i=0;i<256;i++) delete[]a[i];
	delete[]a;
	//调用生成bmp图像的函数
	draw(ai);                             //图像生成在当前文件夹，可是对比度不高，原因见报告

	for(i=0;i<256;i++) delete[]ai[i];
	delete[]ai;
	cout<<"end"<<endl;
	cin>>i;
	

	return 0;
}
