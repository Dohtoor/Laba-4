#include "stdafx.h"
#include "vector"
#include "iostream"
#include "string"

enum DIR				//���������� ��� �������� �����������
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

int main()
{
	int N = 0, M = 0;	//������� ������� 
	int k;				//�������
	std::string buffer;	//������ ��� ���������� �������
	bool error = 1;		//���� ��� ������ ������ ��� ����������

	std::cout << "Enter array size using NxM format." << std::endl;

	while (error)		//�� ��� ���, ���� ���������� � ��������, ����������� ����������
	{
		std::getline(std::cin, buffer);
		error = 0;		//������������� ���� �� ���������� ������
		if (buffer.find_first_of('x') == std::string::npos)
						//���� ������� x ���, �� ������ �������� ������
		{
			std::cout << "Please try again." << std::endl;
			error = 1;
			continue;
		}

		if (buffer.find_first_of('x') == buffer.length() - 1)
						//���� ������ ������������� �������� x, �� ������ �������� ������
		{
			std::cout << "Please try again." << std::endl;
			error = 1;
			continue;
		}

		for (k = 0; k < buffer.find_first_of('x'); k++)	
						//��������� �� ������ �� x
		{
			if ((static_cast<int>(buffer[k]) < 48) || (static_cast<int>(buffer[k]) > 57))
				error = 1;	
						//���� ������ �� �����, �� ��� ������
			N = N * 10 + static_cast<int>(buffer[k]) - 48;
		}

		for (k = buffer.find_first_of('x') + 1; k < buffer.length(); k++)
						//���������  �� x �� �����
		{				
			if ((static_cast<int>(buffer[k]) < 48) || (static_cast<int>(buffer[k]) > 57))
				error = 1;
			M = M * 10 + static_cast<int>(buffer[k]) - 48;
		}
		if (error)
						//���� ���-���� ���� ������, �� �������� ������� � ��������� ��� ���
		{
			std::cout << "Please try again." << std::endl;
			N = M = 0;
		}
	}

	DIR direction = RIGHT;									//�����������
	int left = 0, right = M - 1, top = 0, bottom = N - 1;	//������� ������ ��� ����������
	int i = 0, j = 0;										//��������
	std::vector<std::vector <int>> 
		lul(N, std::vector<int>(M));						//����������� �������
	for (k = 0; k < M*N; k++)								//��������� �� ��� ���, ���� �� ������ N*M ���������
	{
		lul[i][j] = k;
		if ((j == right) && (direction == RIGHT))			//���� �� �������� �������, ������ �����������												
		{
			top++;
			direction = DOWN;
			i++;
			continue;
		}

		if ((j == left) && (direction == LEFT))
		{
			bottom--;
			direction = UP;
			i--;
			continue;
		}

		if ((i == top) && (direction == UP))
		{
			left++;
			direction = RIGHT;
			j++;
			continue;
		}

		if ((i == bottom) && (direction == DOWN))
		{
			right--;
			direction = LEFT;
			j--;
			continue;
		}

		switch (direction)									//���� ������� �� ����������, �� �� ����������� ��� ��������� ������ �������
		{
		case UP:
			i--;
			break;
		case DOWN:
			i++;
			break;
		case RIGHT:
			j++;
			break;
		case LEFT:
			j--;
			break;
		}
	}

	for (i = 0; i < N; i++)									//�����
	{
		for (j = 0; j < M; j++)
			std::cout << lul[i][j] << "\t";
		std::cout << std::endl;
	}
	system("pause");
	return 0;
}
