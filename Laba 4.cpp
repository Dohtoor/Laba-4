#include "stdafx.h"
#include "vector"
#include "iostream"
#include "string"

enum DIR				//энумератор для хранения направления
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

int main()
{
	int N = 0, M = 0;	//размеры матрицы 
	int k;				//счетчик
	std::string buffer;	//буффер для считывания размера
	bool error = 1;		//флаг для записи ошибок при считывании

	std::cout << "Enter array size using NxM format." << std::endl;

	while (error)		//до тех пор, пока считывание с ошибками, запрашиваем считывание
	{
		std::getline(std::cin, buffer);
		error = 0;		//устанавливаем флаг на отсутствие ошибок
		if (buffer.find_first_of('x') == std::string::npos)
						//если символа x нет, то флагом помечает ошибку
		{
			std::cout << "Please try again." << std::endl;
			error = 1;
			continue;
		}

		if (buffer.find_first_of('x') == buffer.length() - 1)
						//если строка заканчивается символом x, то флагом помечает ошибку
		{
			std::cout << "Please try again." << std::endl;
			error = 1;
			continue;
		}

		for (k = 0; k < buffer.find_first_of('x'); k++)	
						//считываем от начала до x
		{
			if ((static_cast<int>(buffer[k]) < 48) || (static_cast<int>(buffer[k]) > 57))
				error = 1;	
						//если символ не число, то это ошибка
			N = N * 10 + static_cast<int>(buffer[k]) - 48;
		}

		for (k = buffer.find_first_of('x') + 1; k < buffer.length(); k++)
						//считываем  от x до конца
		{				
			if ((static_cast<int>(buffer[k]) < 48) || (static_cast<int>(buffer[k]) > 57))
				error = 1;
			M = M * 10 + static_cast<int>(buffer[k]) - 48;
		}
		if (error)
						//если где-либо была ошибка, то обнуляем размеры и считываем еще раз
		{
			std::cout << "Please try again." << std::endl;
			N = M = 0;
		}
	}

	DIR direction = RIGHT;									//направление
	int left = 0, right = M - 1, top = 0, bottom = N - 1;	//размеры границ для заполнения
	int i = 0, j = 0;										//счетчики
	std::vector<std::vector <int>> 
		lul(N, std::vector<int>(M));						//заполняемая матрица
	for (k = 0; k < M*N; k++)								//заполняем до тех пор, пока не введем N*M элементов
	{
		lul[i][j] = k;
		if ((j == right) && (direction == RIGHT))			//если мы достигли границы, меняем направление												
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

		switch (direction)									//если граница не достигнута, то мы увеличиваем или уменьшаем нужный счетчик
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

	for (i = 0; i < N; i++)									//вывод
	{
		for (j = 0; j < M; j++)
			std::cout << lul[i][j] << "\t";
		std::cout << std::endl;
	}
	system("pause");
	return 0;
}
