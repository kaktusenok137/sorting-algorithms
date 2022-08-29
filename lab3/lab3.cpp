#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

unsigned long CmpCount; // Счетчик сравнений

// Функция обнуления счетчика
void ClearCount() {
	CmpCount = 0;
}

// Функция, возвращающая количество сделанных сравнений
unsigned long GetCmpCount() {
	return CmpCount;
}

// BaseType - тип элемента массива подверженного поиску
// по полю Key

struct BaseType {

	int key; // Ключевое поле

	// Переопределение оператора сравнения на меньше
	bool operator < (const BaseType& Var) const {
		CmpCount++;
		return(key < Var.key);
	}

	// Переопределение оператора сравнения на меньше или равно
	bool operator <= (const BaseType& Var) const {
		CmpCount++;
		return(key <= Var.key);
	}

	// Переопределение оператора сравнения на больше
	bool operator > (const BaseType& Var) const {
		CmpCount++;
		return(key > Var.key);
	}

	// Переопределение оператора сравнения на больше или равно
	bool operator >= (const BaseType& Var) const {
		CmpCount++;
		return(key >= Var.key);
	}

	// Переопределение оператора сравнения равенство
	bool operator == (const BaseType& Var) const {
		CmpCount++;
		return(key == Var.key);
	}

	// Переопределение оператора сравнения на неравенство
	bool operator != (const BaseType& Var) const {
		CmpCount++;
		return(key != Var.key);
	}

};

int const N = 50;
int SizeArray = 50;
int mas[N];
int masUp[N];

// Функция формирования массива случайным образом
void RandArray(BaseType* a, long n) {
	srand(time(0));
	for (long i = 0; i < n; i++) {
		a[i].key = rand() % 1000;
		mas[i] = a[i].key;
	}
	/*for (long i = 0; i < n; i++)
		cout <<  a[i].key << " ";
	cout << endl;
	*/
}

// Функция формирования массива упорядоченного по возрастанию
void SortArray(BaseType* a, long n) {
	for (long i = 0; i < n; i++) {
		a[i].key = i;
	}
}

//Линейный поиск
int linearSearch(BaseType* a, long first, long array_size, BaseType element)
{
	for (int i = first; i < array_size; i++)
	{
		CmpCount++;
		if (a[i] == element)
		{
			cout << "Индекс искомого элемента: ";
			return i;
		}	
	}
	cout << "Такого элемента нет! ";
	return -1;
}

//Линейный поиск для блочного
int linearSearch2(BaseType* a, long first, long array_size, BaseType element)
{
	for (int i = first; i < array_size; i++)
	{
		if (a[i] == element)
			return i;
	}
	return -1;
}

//Быстрый линейный поиск
int bLinearSearch(BaseType* a, long first, long array_size, BaseType element)
{
	BaseType temp;
	temp = a[array_size - 1];
	a[array_size - 1] = element;
	int i = first;
	while (element != a[i])
	{
		i++;
	}
	a[array_size - 1] = temp;
	CmpCount++;

	if (i == array_size - 1) { cout << "Такого элемента нет! "; return -1; }
	else { cout << "Индекс искомого элемента: "; return i; }
}

//Быстрый линейный поиск для упорядоченного массива
int bLinearSearchUp(BaseType* a, long first, long array_size, BaseType element)
{
	BaseType temp;
	temp = a[array_size - 1];
	a[array_size - 1] = element;
	int i = first;
	while (element != a[i])
	{
		i++;
	}
	a[array_size - 1] = temp;
	CmpCount++;

	if (i == array_size - 1) { cout << "Такого элемента нет! "; return -1; }
	else { cout << "Индекс искомого элемента: "; return i; }
}

//Бинарный поиск
int binSearch(BaseType* a, long first, long array_size, BaseType element)
{	
	int i = first;
	int j;
	while (i < array_size)
	{
		j = i + ((array_size - i) / 2);
		if (a[j] >= element) { array_size = j; }

		else { i = j + 1; }
	}
	if (a[i] == element) { cout << "Индекс искомого элемента: "; return i; }
	else { cout << "Такого элемента нет! ";  return -1; }


}

//Блочный поиск
int blockSearch(BaseType* a, long first, long array_size, BaseType element)
{
	int p;
	bool F = 1;
	int h = sqrt(array_size - first);
	int i = first + h;
	while (F && i < array_size) {
		if (element <= a[i - 1]) {
			F = 0;
			p = linearSearch2(a, i - h, i, element);
		}
		i = i + h;
	}
	if (F) {
		if (element <= a[array_size - 1]) {
			p = linearSearch2(a, i - h, array_size, element);
		}
		else { cout << "Такого элемента нет! "; p = -1; }
	}
	cout << "Индекс искомого элемента: ";
	return p;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	BaseType requiredKey;
	int SumCount = 0;

	for (int i = 0; i < N; i++)
	{
		masUp[i] = i;
	}

	// Массив указателей на случайные массивы
	BaseType* ProbArray[N];

	// Цикл по разной размерности для формирования массивов случайным образом
	for (int i = 0; i < N; i++) {
		ProbArray[i] = new BaseType[SizeArray];
		RandArray(ProbArray[i], SizeArray);
	}
	BaseType* a; // Указатель на сортируемый массив

	cout << "\tНЕУПОРЯДОЧЕННЫЙ МАССИВ" << endl;
	cout << "\tЛинейный поиск " << endl;
	// Цикл по разной размерности массива
	for (int i = 0; i < N; i++)
	{
		a = new BaseType[SizeArray];
		//(случайный массив)
		for (int j = 0; j < SizeArray; j++)
		{
			a[j] = ProbArray[i][j];
		}
		cout << endl << "Искомый элемент: ";
		requiredKey.key = mas[i];
		cout << requiredKey.key << endl;
		cout << endl << "Кол-во элементов в массиве: " << SizeArray << endl;
		ClearCount();
		cout << linearSearch(a, 0, SizeArray, requiredKey);
		cout << endl << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		SumCount = SumCount + GetCmpCount();
		delete a;
	}
	cout << "Средний cлучай линейного поиска в неупоряд. мас. = " << SumCount / N << endl;
	SumCount = 0;
	system("pause");

	cout << "\tБыстрый линейный поиск:" << endl;
	// Цикл по разной размерности массива
	for (int i = 0; i < N; i++)
	{
		a = new BaseType[SizeArray];
		//(случайный массив)
		for (int j = 0; j < SizeArray; j++)
		{
			a[j] = ProbArray[i][j];
		}
		cout << endl << "Искомый элемент: ";
		requiredKey.key = mas[i];
		cout << requiredKey.key << endl;
		cout << endl << "Кол-во элементов в массиве: " << SizeArray << endl;
		ClearCount();
		cout << bLinearSearch(a, 0, SizeArray, requiredKey);
		cout << endl << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		SumCount = SumCount + GetCmpCount();
		delete a;
	}
	cout << "Средний cлучай быстрого линейного поиска в неупоряд. мас. = " << SumCount / N << endl;
	SumCount = 0;
	system("pause");

	cout << "\tУПОРЯДОЧЕННЫЙ МАССИВ" << endl;
	cout << "\tБыстрый линейный поиск " << endl;
	// Цикл по разной размерности массива
	for (int i = 0; i < N; i++)
	{
		a = new BaseType[SizeArray];
		//(случайный массив)
		for (int j = 0; j < SizeArray; j++)
		{
			a[j] = ProbArray[i][j];
		}
		cout << endl << "Искомый элемент: ";
		SortArray(a, SizeArray);
		requiredKey.key = masUp[i];
		cout << requiredKey.key << endl;
		cout << endl << "Кол-во элементов в массиве: " << SizeArray << endl;
		ClearCount();
		cout << bLinearSearchUp(a, 0, SizeArray, requiredKey);
		cout << endl << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		SumCount = SumCount + GetCmpCount();
		delete a;
	}
	cout << "Средний cлучай быстрого линейного поиска в упоряд. мас. = " << SumCount / N << endl;
	SumCount = 0;
	system("pause");

	cout << "\tБинарный поиск" << endl;
	// Цикл по разной размерности массива
	for (int i = 0; i < N; i++)
	{
		a = new BaseType[SizeArray];
		//(случайный массив)
		for (int j = 0; j < SizeArray; j++)
		{
			a[j] = ProbArray[i][j];
		}
		cout << endl << "Искомый элемент: ";
		SortArray(a, SizeArray);
		requiredKey.key = masUp[i];
		cout << requiredKey.key << endl;
		cout << endl << "Кол-во элементов в массиве: " << SizeArray << endl;
		ClearCount();
		cout << binSearch(a, 0, SizeArray-1, requiredKey);
		cout << endl << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		SumCount = SumCount + GetCmpCount();
		delete a;
	}
	cout << "Средний cлучай бинарного поиска в упоряд. мас. = " << SumCount / N << endl;
	SumCount = 0;
	system("pause");

	cout << "\tБлочный поиск" << endl;
	// Цикл по разной размерности массива
	for (int i = 0; i < N; i++)
	{
		a = new BaseType[SizeArray];
		//(случайный массив)
		for (int j = 0; j < SizeArray; j++)
		{
			a[j] = ProbArray[i][j];
		}
		cout << endl << "Искомый элемент: ";
		SortArray(a, SizeArray);
		requiredKey.key = masUp[i];
		cout << requiredKey.key << endl;
		cout << endl << "Кол-во элементов в массиве: " << SizeArray << endl;
		ClearCount();
		cout << blockSearch(a, 0, SizeArray, requiredKey);
		cout << endl << "Кол-во операций сравнений: " << GetCmpCount() << endl;
		SumCount = SumCount + GetCmpCount();
		delete a;
	}
	cout << "Средний cлучай блочного поиска в упоряд. мас. = " << SumCount / N << endl;
	SumCount = 0;

	for (int i = 0; i < N; i++) delete ProbArray[i];
	return 0;
}
