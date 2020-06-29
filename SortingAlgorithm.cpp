#include "pch.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <cstring>
#include <chrono>

using namespace std;

class Data
{
	int *mass;
	int size;

public:
	Data();
	Data(int);
	Data(int, int, int);
	~Data();

	// Заполнить массив 
	void Uniform(int, int);
	// Печать массива
	void Print();
	// Перегрузка присваивания
	Data & operator = (const Data&);

	// Сортировка Пузырьком
	void BubbleSort();
	// Сортировка Шелла
	void ShellSort();
	// Сортировка расческой
	void CombSort();
	// Быстрая сортировка
	void QuickSort();
	// Сортировка слиянием
	void MergerSort();
	// Сортировка кучей
	void HeapSort();
	// Поразрядная сортировка
	void RadixSort();
	// Встроенная сортировка C++
	void CSort();
	
private:
	// Быстрая сортировка (Рекурсия)
	void QuickSort(int *, int, int);
	// Сортировка слиянием (Рекурсия)
	void MergerSort(int *, int, int);
	// Слияние
	void Merge(int *, int, int);
	// Сортировка кучей (Рекурсия)
	void HeapSort(int *, int, int);
};

int main()
{
	srand(time(NULL));
	int n; cin >> n;

	/*Data mass = Data(0, 9, n);
	Data temp_mass = Data();
	temp_mass = mass;*/
	//mass.Print();
	
	double mean_t = 0;
	Data mass = Data(0, 1000, n);
	Data temp_mass = Data();
	temp_mass = mass;
	auto start = std::chrono::high_resolution_clock::now();
	//mass.BubbleSort();
	//mass.ShellSort();
	//mass.CombSort();
	//mass.QuickSort();
	//mass.MergerSort();
	//mass.HeapSort();
	mass.RadixSort();
	//mass.CSort();
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time - " << elapsed.count() << "s\n";

	mass.Print();

	return 0;
}

// Конструкторы/методы класса
Data::Data()
{
	mass = NULL;
	size = 0;
}
Data::Data(int size)
{
	this->size = size;
	mass = new int[size];
}
Data::Data(int min, int max, int size)
{
	this->size = size;
	mass = new int[size];
	Uniform(min, max);
}
Data::~Data()
{
	delete[] mass;
}
void Data::Uniform(int min, int max)
{
	for (int i = 0; i < size; i++)
		mass[i] = rand() % (max - min + 1) + min;
}
void Data::Print()
{
	for (int i = 0; i < size; i++)
		cout << mass[i] << ' ';
	cout << endl;
}
Data& Data::operator = (const Data& vec)
{
	if (size != vec.size)
	{
		size = vec.size;
		delete[] mass;
		mass = new int[size]{ 0 };
	}
	for (int i = 0; i < size; i++)
		mass[i] = vec.mass[i];
	return *this;
}

// Методы алгоритмов
void Data::BubbleSort()
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size - 1 - i; j++)
			if (mass[j] > mass[j + 1])
				swap(mass[j], mass[j + 1]);
}

void Data::ShellSort()
{
	for (int step = size / 2; step > 0; step /= 2)
		for (int i = step; i < size; i++)
			for (int j = i - step; j >= 0 && mass[j] > mass[j + step]; j -= step)
				swap(mass[j], mass[j + step]);
}

void Data::CombSort()
{
	double factor = 1.247330950103979f;
	for (int step = size; step >= 1; step /= factor)
		for (int i = 0; i + step < size; i++)
			if (mass[i] > mass[i + step])
				swap(mass[i], mass[i + step]);
}

void Data::QuickSort()
{
	QuickSort(mass, 0, size - 1);
}

void Data::QuickSort(int *mass, int start, int end)
{
	if (start >= end) return;
	int left = start, right = end, mid = mass[(left + right) / 2];
	do
	{
		while (mass[left] < mid) left++;
		while (mass[right] > mid) right--;
		if (left <= right)
			swap(mass[left], mass[right]), left++, right--;
	} while (left <= right);

	QuickSort(mass, start, right);
	QuickSort(mass, left, end);
}

void Data::MergerSort()
{
	MergerSort(mass, 0, size - 1);
}

void Data::MergerSort(int *mass, int start, int end)
{
	if (start < end)
	{
		int mid = (start + end) / 2;
		MergerSort(mass, start, mid);
		MergerSort(mass, mid + 1, end);
		Merge(mass, start, end);
	}
}

void Data::Merge(int *mass, int left, int right)
{
	int mid = left + (right - left) / 2;
	int i = left, j = mid + 1;
	int k = 0;

	int t_size = right - left + 1;
	int *temp = new int[t_size];
	for (int index = 0; index < t_size; index++)
		temp[index] = mass[index + left];

	while (i <= mid && j <= right)
		if (mass[i] <= mass[j])
			temp[k++] = mass[i++];
		else
			temp[k++] = mass[j++];
	while (i <= mid) temp[k++] = mass[i++];
	while (j <= right) temp[k++] = mass[j++];
	
	for (int index = 0; index < t_size; index++)
		mass[index + left] = temp[index];
}

void Data::HeapSort()
{
	for (int i = size / 2 - 1; i >= 0; i--)
		HeapSort(mass, size, i);
 
	for (int i = size - 1; i > 0; i--)
	{ 
		swap(mass[0], mass[i]);
		HeapSort(mass, i, 0);
	}
}

void Data::HeapSort(int *mass, int n, int i)
{
	int largest = i, l = 2 * i + 1, r = 2 * i + 2;
 
	if (l < n && mass[l] > mass[largest])
		largest = l;

	if (r < n && mass[r] > mass[largest])
		largest = r;

	if (largest != i)
	{
		swap(mass[i], mass[largest]); 
		HeapSort(mass, n, largest);
	}
}

void Data::RadixSort()
{
	/*string *txt_mass = new string[size];
	ostringstream out;
	for (int i = 0; i < size; i++)
	{
		out << mass[i];
		txt_mass[i] = out.str();
		out.str(""), out.clear();
	}*/
	
	int max = -9999999;
	for (int i = 0; i < size; i++)
		if (mass[i] > max) max = mass[i];

	int step = 1;
	while (max / step > 0)
	{
		int *temp = new int[size]{ 0 };
		int *count = new int[10]{ 0 };

		for (int i = 0; i < size; i++)
			count[(mass[i] / step) % 10] += 1;

		for (int i = 1; i < 10; i++)
			count[i] += count[i - 1];

		for (int k = size - 1; k >= 0; k--)
		{
			int index = mass[k] / step;
			temp[count[index % 10] - 1] = mass[k];
			count[index % 10] -= 1;
		}

		for (int i = 0; i < size; i++)
			mass[i] = temp[i];

		delete[] temp;
		delete[] count;
		step *= 10;
	}
	//delete[] txt_mass;
}

void Data::CSort()
{
	sort(mass, mass + size);
}
