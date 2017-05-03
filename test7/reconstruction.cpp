//�˲���ͶӰ���ؽ�ͼ��
//�¼һ�

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


	//һ.����ͶӰֵ

	//pΪͶӰ����180���Ƕȣ�ÿ���Ƕ���256��ֵ��������180*256
	double **p;
	p=new double*[180];
	for(i=0;i<180;i++) p[i]=new double[256];
	for(i=0;i<180;i++)
	{
		for(j=0;j<256;j++) p[i][j]=0;
	}

	//����ƽ�漸�Σ������߻��֣�Ȼ����ɢ����
	//shepp-logen����10����Բ�����ε��ӵ�ͶӰ�ϡ���������ɼ�˵���ĵ���

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


	//�����˲�

	//Ԥ����
	//��ͶӰp���������180*766�������߸�����255���Ա����˲�
	//����洢��pa��
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

	//�ͷ�p
	for(i=0;i<180;i++) delete[]p[i];
	delete[]p;

	//���о���˲�
	//�˲��ķ������ǽ�һ�������˲��ĺ�����x�ᷭת��Ȼ��������ˡ���ӡ�
	//�����˲�������ż���������Է�ת��û�б仯���������˷�ת�ⲽ��
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

	//�ͷ�pa
	for(i=0;i<180;i++) delete[]pa[i];
	delete[]pa;


	//������ͶӰ

	//a��ʼ�������ڴ�ŷ�ͶӰ��ͼ��
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
	for(l=0;l<180;l++)											//ѡ��һ��ͶӰ�Ƕ�
	{
		cm=127.5*(1-cos(D2R(l))-sin(D2R(l)));
		for(i=0;i<256;i++)										//��ͼ���ϵĵ㣨i,j��,�ҵ���ӦͶӰֵ��ͨ����ֵ���ͶӰֵ
		{														//�����Ƶ��ɼ�˵���ĵ�	
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

	//a��Ϊ�ؽ�ͼ��

	char* path = "a.txt";   //ͶӰ���ݣ�����matlab�鿴���
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


	//����ʹ��8λbmp��ʽ��ͼ������Ҫ��ͼ���ֵת����[0,255]
	double max=a[0][0];
	double min=a[0][0];

	int **ai;
	ai=new int*[256];
	for(i=0;i<256;i++) ai[i]=new int[256];
	//�ҵ������Сֵ
	for(i=0;i<256;i++)
	{
		for(j=0;j<256;j++) 
		{
			if(a[i][j]<min) min=a[i][j];
			if(a[i][j]>max) max=a[i][j];
		}
	}
	//��ͼ�����Ե�ӳ�䵽[0,255]
	for(i=0;i<256;i++)
	{
		for(j=0;j<256;j++) 
		{
			ai[i][j]=(a[i][j]-min)/(max-min)*255;
		}
	}

	for(i=0;i<256;i++) delete[]a[i];
	delete[]a;
	//��������bmpͼ��ĺ���
	draw(ai);                             //ͼ�������ڵ�ǰ�ļ��У����ǶԱȶȲ��ߣ�ԭ�������

	for(i=0;i<256;i++) delete[]ai[i];
	delete[]ai;
	cout<<"end"<<endl;
	cin>>i;
	

	return 0;
}
