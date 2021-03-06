// Библиотека шаблон класса матрицы(С основными частями Объектно-орентированого програмирования)
// Автор: Вирясов Владислав Евгеньевич
#include "pch.h"
#include <iostream>
#include <time.h>
#include <iomanip>
#include <fstream>
#include <clocale>

using namespace std;

template <typename T> class Matrix // Класс матриц
{
protected:
	T **matrix; // Матрица
	int n; // Кол-во строк
	int m; // Кол-во столбцов
	double RecursiveDetermaniant(T **, int); // Рекурсивная функция нахождение Determaniant
	void GetMat(T **, T **, int, int, int); // Получение матрицы без i-й строки и j-го столбца
public:
	Matrix(); // Конструктор по умолчанию
	Matrix(int, int); // Конструктор с параметрами
	Matrix(const Matrix&); // Конструктор копирования
	~Matrix(); // Деструктор
	template <typename T> friend istream& operator>>(istream&, const Matrix<T>&); // Оператор ввода
	template <typename T> friend ostream& operator<<(ostream&, const Matrix<T>&); // Оператор вывода
	Matrix & operator = (const Matrix&); // Оператор присваивания
	bool operator == (const Matrix&); // Оператор сравнения
	bool operator != (const Matrix&); // Оператор сравнения
	Matrix operator + (Matrix); // Оператор сложения
	Matrix operator - (Matrix); // Оператор вычитания
	Matrix operator * (Matrix); // Оператор умножения матриц
	Matrix operator * (int); // Оператор умножения на число
	Matrix operator / (int); // Оператор деления на число
	T& operator[] (int); // Оператор операция обеспечения доступа к заданному элементу матрицы
	//Matrix[int]& operator[] (); // Оператор операция обеспечения доступа к заданному элементу матрицы
	void Rand(int, int); // Рандомное заполнение
	bool is_Square(); // Квадратная ли матица
	bool is_Single(); // Единичная ли матрица
	bool is_Simmetric(); // Симметричная ли матрица
	bool is_Triangular(); // Треугольная ли матрица
	double Determaniant(); // Нахождение определителя
};
template <typename T> void Matrix<T>::GetMat(T **mat, T **p, int i, int j, int m)
{
	int ki, kj, di, dj;
	di = 0;
	for (ki = 0; ki < m - 1; ki++) { // проверка индекса строки
		if (ki == i) di = 1;
		dj = 0;
		for (kj = 0; kj < m - 1; kj++) { // проверка индекса столбца
			if (kj == j) dj = 1;
			p[ki][kj] = mat[ki + di][kj + dj];
		}
	}
}
template <typename T> double Matrix<T>::RecursiveDetermaniant(T **mas, int m)
{
	int i, j, k, nn;
	double d;
	T **p;
	p = new T*[m];
	for (i = 0; i < m; i++)
		p[i] = new T[m];
	j = 0; d = 0;
	k = 1; //(-1) в степени i
	nn = m - 1;
	if (m < 1) throw 1;
	if (m == 1) {
		d = mas[0][0];
		return d;
	}
	if (m == 2) {
		d = mas[0][0] * mas[1][1] -(mas[1][0] * mas[0][1]);
		return d;
	}
	if (m > 2) {
		for (i = 0; i < m; i++) {
			GetMat(mas, p, i, 0, m);
			cout << mas[i][j] << endl;
			d = d + k * mas[i][0] * RecursiveDetermaniant(p, n);
			k = -k;
		}
	}
	return d;
}
template <typename T> double Matrix<T>::Determaniant()
{
	if (!is_Square())
		throw 1;
	if (!is_Single()) // У треугольной матрицы легко найти Determaniant
	{
		int d = 1;
		for (int i = 0; i < n; i++)
			d *= matrix[i][i];
		return d;
	}
	return RecursiveDetermaniant(matrix, n);
}
template <typename T> bool Matrix<T>::is_Triangular()
{
	if (!is_Square())
		return false;
	bool check = true;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < m; j++)
			if (matrix[i][j] != 0)
				check = false;
	if (check) return check;
	else check = true;
	for (int i = n - 1; i >= 0; i--)
		for (int j = i - 1; j >= 0; j--)
			if (matrix[i][j] != 0)
				check = false;
	return check;
}
template <typename T> bool Matrix<T>::is_Simmetric()
{
	if (!is_Square())
		return false;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < m; j++)
			if (matrix[i][j] != matrix[j][i])
				return false;
	return true;
}
template <typename T> bool Matrix<T>::is_Single()
{
	if (!is_Square())
		return false;
	for (int i = 0; i < n; i++)
	{
		if (matrix[i][i] == 1) return false;
		for (int j = i; j < m; j++)
			if (matrix[i][j] != 0 || matrix[j][i] != 0)
				return false;
	}
	return true;
}
template <typename T> bool Matrix<T>::is_Square()
{
	return n == m ? true : false;
}
template <typename T> void Matrix<T>::Rand(int a, int b)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			matrix[i][j] = (rand() % b) + a;
}
template <typename T> Matrix<T>::Matrix()
{
	n = 1;
	m = 1;
	matrix = new T*[1];
	matrix[0] = new T[1];
}
template <typename T> Matrix<T>::Matrix(int n, int m)
{
	this->n = n;
	this->m = m;
	matrix = new T*[n];
	for (int i = 0; i < n; i++)
		matrix[i] = new T[m];
}

template <typename T> Matrix<T>::Matrix(const Matrix<T> &mat)
{
	n = mat.n;
	m = mat.m;
	matrix = new T*[n];
	for (int i = 0; i < n; i++)
		matrix[i] = new T[m];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			matrix[i][j] = mat.matrix[i][j];
}

template <typename T> Matrix<T>::~Matrix()
{
	for (int i = 0; i < n; i++)
		delete matrix[i];
	delete matrix;
}

template <typename T> Matrix<T> Matrix<T>::operator+(Matrix<T> mat)
{
	if (n != mat.n || m != mat.m)
		throw 1;
	Matrix<T> res(mat);
	res.n = n;
	res.m = m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			res.matrix[i][j] = matrix[i][j] + mat.matrix[i][j];
	return res;
}

template <typename T> Matrix<T> Matrix<T>::operator-(Matrix<T> mat)
{
	if (n != mat.n || m != mat.m)
		throw 1;
	Matrix<T> res(mat);
	res.n = n;
	res.m = m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			res.matrix[i][j] = matrix[i][j] - mat.matrix[i][j];
	return res;
}

template <typename T> Matrix<T> Matrix<T>::operator*(Matrix<T> mat)
{
	if (n != mat.n || m != mat.m)
		throw 1;
	Matrix<T> res(mat);
	res.n = n;
	res.m = m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < mat.m; j++)
		{
			res.matrix[i][j] = 0;
			for (int k = 0; k < m; k++)
				res.matrix[i][j] += matrix[i][k] * mat.matrix[k][j];
		}
	return res;
}

template <typename T> Matrix<T> Matrix<T>::operator *(int a)
{
	Matrix<T> res;
	res.n = n;
	res.m = m;
	res.matrix = new T*[n];
	for (int i = 0; i < n; i++)
		res.matrix[i] = new T[m];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			res.matrix[i][j] = matrix[i][j] * a;
	return res;
}

template <typename T> Matrix<T> Matrix<T>::operator /(int a)
{
	if (a == 0)
		throw 1;
	Matrix<T> res;
	res.n = n;
	res.m = m;
	res.matrix = new T*[n];
	for (int i = 0; i < n; i++)
		res.matrix[i] = new T[m];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			res.matrix[i][j] = matrix[i][j] / a;
	return res;
}

template <typename T> T& Matrix<T>::operator[](int a)
{
	if (a < 0 && a >= n)
		throw 1;
	return matrix[a];
}

template <typename T> Matrix<T>& Matrix<T>::operator = (const Matrix<T>& mat)
{
	if (n != mat.n || m != mat.m)
	{
		for (int i = 0; i < n; i++)
			delete matrix[i];
		delete matrix;
		n = mat.n; m = mat.m;
		matrix = new T*[n];
		for (int i = 0; i < n; i++)
			matrix[i] = new T[m];
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			matrix[i][j] = mat.matrix[i][j];
	return *this;
}
template <typename T> bool Matrix<T>::operator == (const Matrix<T>& mat)
{
	if (n != mat.n || m != mat.m)
		throw 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (matrix[i][j] != mat.matrix[i][j])
				return false;
	return true;
}
template <typename T> bool Matrix<T>::operator != (const Matrix<T>& mat)
{
	if (n != mat.n || m != mat.m)
		throw 1;
	return !(*this == mat);
}
template <typename T> istream& operator>>(istream& in, const Matrix<T>& mat)
{
	for (int i = 0; i < mat.n; i++)
		for (int j = 0; j < mat.m; j++)
		{
			cout << "[" << i << "][" << j << "]:";
			in >> mat.matrix[i][j];
		}
	return in;
}
template <typename T> ostream& operator<<(ostream& out, const Matrix<T>& mat)
{
	for (int i = 0; i < mat.n; out << endl && i++)
		for (int j = 0; j < mat.m; j++)
			out << setw(3) << mat.matrix[i][j];
	return out;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	Matrix<int> Mat(3, 3);
	Mat.Rand(0, 5);
	cout << Mat;
}
