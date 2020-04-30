// ConsoleApplication1.cpp : �w�q�D���x���ε{�����i�J�I�C
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

int main()
{
	int data_height;     //�x�}����
	int data_width;      //�x�}�e��
	srand(time(0));      //�]�w�ü�
	data_height = (rand() * 6 / 32767 + 4);  //�]�w�x�}���צb4~10����
	data_width = (rand() * 6 / 32767 + 4);    //�]�w�x�}�e�צb4~10����
	double mask_A[3][3] = { { 0.0,-0.5,0.0 },{ -0.5, 0.0, 0.5 },{ 0.0,-0.5,0.0 } };    //�]�B�nA
	double mask_B[3][3] = { { 0.5,0.25,0.5 },{ 0.25, 1.0, 0.25 },{ 0.5,-0.5,0.5 } }; //�]�B�nB
	int a = data_height - 2; //�]����n�Ұ����B��A�u���q(1.1)��(a,b)���ܰʭȡA�ҥH�b�]�w�@�Ӱ϶�
	int b = data_width - 2;
	double**data;
	double**data_A;
	double**data_B;
	data = new double*[data_height];        //�ʺA�t�m�T�ӤG�� double �x�}
	data_A = new double*[data_height];
	data_B = new double*[data_height];
	for (int i = 0; i < data_height; i++)
	{
		data[i] = new double[data_width];
		data_A[i] = new double[data_width];
		data_B[i] = new double[data_width];

	}
	for (int i = 0; i < data_height; i++)     //�N0~255�������üƦs�J�|�}��
	{
		for (int j = 0; j < data_width; j++)
		{

			int number = (rand() * 255 / 32767 + 0);
			data[i][j] = number;
			data_A[i][j] = data[i][j];
			data_B[i][j] = data[i][j];
			//data[j]=&number
		}
	}
	for (int i = 1; i < 1 + a; i++)          //�i��B�nA���B��
	{
		for (int j = 1; j < 1 + b; j++)
		{
			data_A[i][j] = data[i - 1][j - 1] * mask_A[0][0] + data[i - 1][j] * mask_A[0][1] + data[i - 1][j + 1] * mask_A[0][2]
				+ data[i][j - 1] * mask_A[1][0] + data[i][j] * mask_A[1][1] + data[i][j + 1] * mask_A[1][2]
				+ data[i + 1][j - 1] * mask_A[2][0] + data[i + 1][j] * mask_A[2][1] + data[i + 1][j + 1] * mask_A[2][2];
		}
	}
	for (int i = 1; i < 1 + a; i++)         //�i��B�nB���B��
	{
		for (int j = 1; j < 1 + b; j++)
		{
			data_B[i][j] = data[i - 1][j - 1] * mask_B[0][0] + data[i - 1][j] * mask_B[0][1] + data[i - 1][j + 1] * mask_B[0][2]
				+ data[i][j - 1] * mask_B[1][0] + data[i][j] * mask_B[1][1] + data[i][j + 1] * mask_B[1][2]
				+ data[i + 1][j - 1] * mask_B[2][0] + data[i + 1][j] * mask_B[2][1] + data[i + 1][j + 1] * mask_B[2][2];
		}
	}
	double max_A = 0;         //�Q��for �j��Mif�Ӥ�j�p�A�̤j���s�Jmax_A �̤j����m�s�J x_A = i; y_A = j;
	int x_A = 0; int y_A = 0;
	for (int i = 0; i < data_height; i++)
	{
		for (int j = 0; j < data_width; j++)
		{
			if (data_A[i][j] > max_A)
			{
				max_A = data_A[i][j];
				x_A = i; y_A = j;
			}
		}
	}
	double max_B = 0;     //�Q��for �j��Mif�Ӥ�j�p�A�̤j���s�Jmax_B �̤j����m�s�J x_B = i; y_B = j;
	int x_B = 0; int y_B = 0;
	for (int i = 0; i < data_height; i++)
	{
		for (int j = 0; j < data_width; j++)
		{
			if (data_B[i][j] > max_B)
			{
				max_B = data_B[i][j];
				x_B = i; y_B = j;
			}
		}
	}
	cout << "imgae data" << endl;             //���l�x�}��X�X��
	for (int i = 0; i < data_height; i++)
	{
		for (int j = 0; j < data_width; j++)
		{
			//cout << setw(5) << data[j]; �o�˥u��Xj��
			cout << std::left << setw(10) << data[i][j];
		}
		cout << endl;
	}
	cout << endl;
	cout << "imgae convolution with mask A" << endl;  //��g�L�B�nA�B�⪺�x�}��X�X��
	for (int i = 0; i < data_height; i++)
	{
		for (int j = 0; j < data_width; j++)
		{
			cout << std::left << setw(10) << data_A[i][j];
		}
		cout << endl;
	}
	cout << "The max value " << max_A << " is at " << "(" << x_A << ", " << y_A << ")" << endl; //��X�̤j�ȤΦ�m
	cout << "--------------------------------------------" << endl;
	cout << "imgae convolution with mask B" << endl;  //��g�L�B�nB�B�⪺�x�}��X�X��
	for (int i = 0; i < data_height; i++)
	{
		for (int j = 0; j < data_width; j++)
		{
			cout << std::left << setw(10) << data_B[i][j];
		}
		cout << endl;
	}
	cout << "The max value " << max_B << " is at " << "(" << x_B << ", " << y_B << ")" << endl;//��X�̤j�ȤΦ�m
	for (int i = 0; i < data_height; i++) //����O����Ŷ�
		delete[] data[i];
	delete[]data;

	return 0;
}

