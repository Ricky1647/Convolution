// ConsoleApplication1.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

int main()
{
	int data_height;     //矩陣高度
	int data_width;      //矩陣寬度
	srand(time(0));      //設定亂數
	data_height = (rand() * 6 / 32767 + 4);  //設定矩陣高度在4~10之間
	data_width = (rand() * 6 / 32767 + 4);    //設定矩陣寬度在4~10之間
	double mask_A[3][3] = { { 0.0,-0.5,0.0 },{ -0.5, 0.0, 0.5 },{ 0.0,-0.5,0.0 } };    //設遮罩A
	double mask_B[3][3] = { { 0.5,0.25,0.5 },{ 0.25, 1.0, 0.25 },{ 0.5,-0.5,0.5 } }; //設遮罩B
	int a = data_height - 2; //因為折積所做的運算，只有從(1.1)到(a,b)有變動值，所以在設定一個區間
	int b = data_width - 2;
	double**data;
	double**data_A;
	double**data_B;
	data = new double*[data_height];        //動態配置三個二維 double 矩陣
	data_A = new double*[data_height];
	data_B = new double*[data_height];
	for (int i = 0; i < data_height; i++)
	{
		data[i] = new double[data_width];
		data_A[i] = new double[data_width];
		data_B[i] = new double[data_width];

	}
	for (int i = 0; i < data_height; i++)     //將0~255之間的亂數存入舉陣中
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
	for (int i = 1; i < 1 + a; i++)          //進行遮罩A的運算
	{
		for (int j = 1; j < 1 + b; j++)
		{
			data_A[i][j] = data[i - 1][j - 1] * mask_A[0][0] + data[i - 1][j] * mask_A[0][1] + data[i - 1][j + 1] * mask_A[0][2]
				+ data[i][j - 1] * mask_A[1][0] + data[i][j] * mask_A[1][1] + data[i][j + 1] * mask_A[1][2]
				+ data[i + 1][j - 1] * mask_A[2][0] + data[i + 1][j] * mask_A[2][1] + data[i + 1][j + 1] * mask_A[2][2];
		}
	}
	for (int i = 1; i < 1 + a; i++)         //進行遮罩B的運算
	{
		for (int j = 1; j < 1 + b; j++)
		{
			data_B[i][j] = data[i - 1][j - 1] * mask_B[0][0] + data[i - 1][j] * mask_B[0][1] + data[i - 1][j + 1] * mask_B[0][2]
				+ data[i][j - 1] * mask_B[1][0] + data[i][j] * mask_B[1][1] + data[i][j + 1] * mask_B[1][2]
				+ data[i + 1][j - 1] * mask_B[2][0] + data[i + 1][j] * mask_B[2][1] + data[i + 1][j + 1] * mask_B[2][2];
		}
	}
	double max_A = 0;         //利用for 迴圈和if來比大小，最大的存入max_A 最大的位置存入 x_A = i; y_A = j;
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
	double max_B = 0;     //利用for 迴圈和if來比大小，最大的存入max_B 最大的位置存入 x_B = i; y_B = j;
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
	cout << "imgae data" << endl;             //把初始矩陣輸出出來
	for (int i = 0; i < data_height; i++)
	{
		for (int j = 0; j < data_width; j++)
		{
			//cout << setw(5) << data[j]; 這樣只輸出j阿
			cout << std::left << setw(10) << data[i][j];
		}
		cout << endl;
	}
	cout << endl;
	cout << "imgae convolution with mask A" << endl;  //把經過遮罩A運算的矩陣輸出出來
	for (int i = 0; i < data_height; i++)
	{
		for (int j = 0; j < data_width; j++)
		{
			cout << std::left << setw(10) << data_A[i][j];
		}
		cout << endl;
	}
	cout << "The max value " << max_A << " is at " << "(" << x_A << ", " << y_A << ")" << endl; //輸出最大值及位置
	cout << "--------------------------------------------" << endl;
	cout << "imgae convolution with mask B" << endl;  //把經過遮罩B運算的矩陣輸出出來
	for (int i = 0; i < data_height; i++)
	{
		for (int j = 0; j < data_width; j++)
		{
			cout << std::left << setw(10) << data_B[i][j];
		}
		cout << endl;
	}
	cout << "The max value " << max_B << " is at " << "(" << x_B << ", " << y_B << ")" << endl;//輸出最大值及位置
	for (int i = 0; i < data_height; i++) //釋放記憶體空間
		delete[] data[i];
	delete[]data;

	return 0;
}

