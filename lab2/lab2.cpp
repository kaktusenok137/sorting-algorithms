#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

unsigned long CmpCount; // Счетчик сравнений
unsigned long MovCount; // Счетчик пересылок (присваиваний)

// Функция обнуления счетчиков
void ClearCoutn() {
	CmpCount = 0;
	MovCount = 0;
}

// Функция, возвращающая количество сделанных сравнений
unsigned long GetCmpCount() {
	return CmpCount;
}

// Функция возвращающая количество сделанных пересылок
unsigned long GetMovCount() {
	return MovCount;
}

// Функция возвращающая суммарное количеств сделанных сравнений и пересылок
unsigned long GetAllCount() {
	return CmpCount + MovCount;
}

// BaseType - тип элемента массива подверженного сортировке по полю Key
struct BaseType {
	int key;    // Ключевое поле

	// Преопределение оператора присваивания
	BaseType& operator=(const BaseType& Var) {
		key = Var.key;
		MovCount++;
		return *this;
	}

	// Переопределение оператора сравнения на меньше
	bool operator<(const BaseType& Var) const {
		CmpCount++;
		return(key < Var.key);
	}

	// Переопределение оператора сравнения на меньше или равно
	bool operator<=(const BaseType& Var) const {
		CmpCount++;
		return(key <= Var.key);
	}

	// Переопределение оператора сравнения на больше
	bool operator>(const BaseType& Var) const {
		CmpCount++;
		return(key > Var.key);
	}

	// Переопределение оператора сравнения на больше или равно
	bool operator>=(const BaseType& Var) const {
		CmpCount++;
		return(key >= Var.key);
	}

	// Переопределение оператора сравнения равенство
	bool operator==(const BaseType& Var) const {
		CmpCount++;
		return(key == Var.key);
	}

	// Переопределение оператора сравнения на неравенство
	bool operator!=(const BaseType& Var) const {
		CmpCount++;
		return(key != Var.key);
	}
};

// Функции формирования массивов элементов типа BaseType
// Имеют параметры
// a - указатель на массив,
// n - количество элементов

// Функция формирования массива случайным образом
void RandArray(BaseType* a, long n) {
	srand(time(NULL));
	for (long i = 0; i < n; i++) {
		a[i].key = rand() % 100;
	}
	/*for (long i = 0; i < n; i++)
		cout << a[i].key << " ";
	cout << endl;
	*/
}

// Функция формирования массива упорядоченного по возрастанию
void SortArray(BaseType* a, long n) {
	for (long i = 0; i < n; i++) {
		a[i].key = i;
	}
}

// Функция формирования массива упорядоченного по убыванию
void UnSortArray(BaseType* a, long n) {
	for (long i = 0; i < n; i++) {
		a[i].key = n - i;
	}
}

// Функция обмена значений переменных
template<class T>
void Swap(T& x, T& y) {
	T temp = x;
	x = y;
	y = temp;
}

// Сортировка вставками
template<class T>
void InsertSort(T* a, long array_sise) {
	for (long i = 1; i < array_sise; i++) {
		T x = a[i];
		long j = i - 1;
		for (; j >= 0 && a[j] > x; j--) a[j + 1] = a[j];
		a[j + 1] = x;
	}
}

// Сортировка выбором
template<class T>
void SelectionSort(T* a, long array_sise)
{
	int i, j, k;
	T temp;
	for (i = 0; i < array_sise - 1; i++)
	{
		temp = a[i];
		k = i;
		for (j = i + 1; j < array_sise; j++)
			if (a[j] < a[k]) k = j;
		if (k != i)
		{
			a[i] = a[k];
			a[k] = temp;
		}
	}
}

// Сортировка обменом (пузырек)
template<class T>
void BubbleSort(T* a, long array_sise) {
	for (long i = 0; i < array_sise - 1; i++)
		for (long j = array_sise - 1; j > i; j--)
			if (a[j - 1] > a[j]) Swap(a[j], a[j - 1]);
}

// Сортировка Шелла
template<class T>
void ShellSort(T* a, long  array_sise)
{
	T temp;
	int step, j;
	step = array_sise / 2;
	while (step > 0) {
		for (int i = 0; i < array_sise - step; i++) {
			j = i;
			while (j >= 0 && a[j] > a[j + step]) {
				temp = a[j];
				a[j] = a[j + step];
				a[j + step] = temp;
				j--;
			}
		}
		step = step / 2;
	}
}

// Быстрая сортировка (Хоара)
template<class T>
void QuickSort(T* a, long array_sise) {
	// На входе - массив a[], a[N] - его последний элемент.

	long i = 0, j = array_sise; // поставить указатели на исходные места
	T temp, mid;

	mid = a[array_sise / 2]; // центральный элемент
	// процедура разделения
	do {
		while (a[i] < mid) i++;
		while (a[j] > mid) j--;

		if (i <= j) {
			temp = a[i]; a[i] = a[j]; a[j] = temp;
			i++; j--;
		}
	} while (i <= j);

	// рекурсивные вызовы, если есть, что сортировать
	if (j > 0) QuickSort(a, j);
	if (array_sise > i) QuickSort(a + i, array_sise - i);
}

//Пирамидальна сортировка - 1) Функция "просеивания" через кучу - формирование кучи
 template<class T>
 void siftDown(T* numbers, int root, int bottom)
 {
	 int maxChild; // индекс максимального потомка
	 int done = 0; // флаг того, что куча сформирована
	 // Пока не дошли до последнего ряда
	 while ((root * 2 <= bottom) && (!done))
	 {
		 if (root * 2 == bottom)    // если мы в последнем ряду,
			 maxChild = root * 2;    // запоминаем левый потомок
		   // иначе запоминаем больший потомок из двух
		 else if (numbers[root * 2] > numbers[root * 2 + 1])
			 maxChild = root * 2;
		 else
			 maxChild = root * 2 + 1;
		 // если элемент вершины меньше максимального потомка
		 if (numbers[root] < numbers[maxChild])
		 {
			 T temp = numbers[root]; // меняем их местами
			 numbers[root] = numbers[maxChild];
			 numbers[maxChild] = temp;
			 root = maxChild;
		 }
		 else // иначе
			 done = 1; // пирамида сформирована
	 }
 }
 // 2) Функция пирамидальной сортировки на куче
 template <class T>
 void heapSort(T* a, long array_size)
 {
	 // Формируем нижний ряд пирамиды
	 for (int i = (array_size / 2) - 1; i >= 0; i--)
		 siftDown(a, i, array_size - 1);
	 // Просеиваем через пирамиду остальные элементы
	 for (int i = array_size - 1; i >= 1; i--)
	 {
		 T temp = a[0];
		 a[0] = a[i];
		 a[i] = temp;
		 siftDown(a, 0, i - 1);
	 }
 }

// Количество различных размерностей сортируемого массива
#define N 5

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");
	// Количество элементов в массиве
	int SizeArray[N] = { 5, 10, 15, 20, 25};
	// Массив указателей на случайные массивы
	BaseType* ProbArray[N];
	// Цикл по разной размерности 
	// для формирования массивов случайным образом
	for (int i = 0; i < N; i++)
	{
		ProbArray[i] = new BaseType[SizeArray[i]];
		RandArray(ProbArray[i], SizeArray[i]);
	}
	BaseType* a; // Указатель на сортируемый массив

	// Эксперименты с алгоритмом сортировки вставками
	cout << endl;
	cout << "\t \t Сортировка вставками:" << endl;
	// Цикл по разной размерности массива
	for (int i = 0; i < N; i++)
	{
		a = new BaseType[SizeArray[i]];
		// Исследование среднего случая (случайный массив)
		for (int j = 0; j < SizeArray[i]; j++) a[j] = ProbArray[i][j];
		cout << "Длина массива = " << SizeArray[i] << endl;
		cout << "Средний случай:" << endl;
		ClearCoutn();
		InsertSort(a, SizeArray[i]);
		cout << "Для случайно сгенерированного массива всего операций " << GetAllCount() << "\t Сравнений = " << GetCmpCount() << endl;
		// Исследование лучшего случая (упорядоченный массив)
		SortArray(a, SizeArray[i]);
		cout << "Лучший случай:" << endl;
		ClearCoutn();
		InsertSort(a, SizeArray[i]);
		cout << "Для упорядоченного массива всего операций " << GetAllCount() << "\t Сравнений = " << GetCmpCount() << endl;
		// Исследование худшего случая 
		// (массив, упорядоченный в обратном порядке)
		UnSortArray(a, SizeArray[i]);
		cout << "Худший случай:" << endl;
		ClearCoutn();
		InsertSort(a, SizeArray[i]);
		cout << "Для массива, упорядоченного в обратном порядке, всего операций " << GetAllCount() << "\t Сравнений = " << GetCmpCount() << endl;
		delete a;
	}

	// Эксперименты с алгоритмом сортировки выбором
	cout << endl;
	cout << "\t \t Сортировка Выбором:" << endl;
	// Цикл по разной размерности массива
	for (int i = 0; i < N; i++)
	{
		a = new BaseType[SizeArray[i]];
		// Исследование среднего случая (случайный массив)
		for (int j = 0; j < SizeArray[i]; j++) a[j] = ProbArray[i][j];
		cout << "Длина массива = " << SizeArray[i] << endl;
		cout << "Средний случай:" << endl;
		ClearCoutn();
		SelectionSort(a, SizeArray[i]);
		cout << "Для случайно сгенерированного массива всего операций " << GetAllCount() << "\t Сравнений = " << GetCmpCount() << endl;
		// Исследование лучшего случая (упорядоченный массив)
		SortArray(a, SizeArray[i]);
		cout << "Лучший случай:" << endl;
		ClearCoutn();
		SelectionSort(a, SizeArray[i]);
		cout << "Для упорядоченного массива всего операций " << GetAllCount() << "\t Сравнений = " << GetCmpCount() << endl;
		// Исследование худшего случая 
		// (массив, упорядоченный в обратном порядке)
		UnSortArray(a, SizeArray[i]);
		cout << "Худший случай:" << endl;
		ClearCoutn();
		SelectionSort(a, SizeArray[i]);
		cout << "Для массива, упорядоченного в обратном порядке, всего операций " << GetAllCount() << "\t Сравнений = " << GetCmpCount() << endl;
		delete a;
	}

	// Эксперименты с алгоритмом сортировки пузырьком
	cout << endl;
	cout << "\t \t Сортировка пузырьком:" << endl;
	// Цикл по разной размерности массива
	for (int i = 0; i < N; i++)
	{
		a = new BaseType[SizeArray[i]];
		// Исследование среднего случая (случайный массив)
		for (int j = 0; j < SizeArray[i]; j++) a[j] = ProbArray[i][j];
		cout << "Длина массива = " << SizeArray[i] << endl;
		cout << "Средний случай:" << endl;
		ClearCoutn();
		BubbleSort(a, SizeArray[i]);
		cout << "Для случайно сгенерированного массива всего операций " << GetAllCount() << "\t Сравнений = " << GetCmpCount() << endl;
		// Исследование лучшего случая (упорядоченный массив)
		SortArray(a, SizeArray[i]);
		cout << "Лучший случай:" << endl;
		ClearCoutn();
		BubbleSort(a, SizeArray[i]);
		cout << "Для упорядоченного массива всего операций " << GetAllCount() << "\t Сравнений = " << GetCmpCount() << endl;
		// Исследование худшего случая 
		// (массив, упорядоченный в обратном порядке)
		UnSortArray(a, SizeArray[i]);
		cout << "Худший случай:" << endl;
		ClearCoutn();
		BubbleSort(a, SizeArray[i]);
		cout << "Для массива, упорядоченного в обратном порядке, всего операций " << GetAllCount() << "\t Сравнений = " << GetCmpCount() << endl;
		delete a;
	}

	// Эксперименты с алгоритмом сортировки Шелла
	cout << endl;
	cout << "\t \t Сортировка Шелла:" << endl;
	// Цикл по разной размерности массива
	for (int i = 0; i < N; i++)
	{
		a = new BaseType[SizeArray[i]];
		// Исследование среднего случая (случайный массив)
		for (int j = 0; j < SizeArray[i]; j++) a[j] = ProbArray[i][j];
		cout << "Длина массива = " << SizeArray[i] << endl;
		cout << "Средний случай:" << endl;
		ClearCoutn();
		ShellSort(a, SizeArray[i]);
		cout << "Для случайно сгенерированного массива всего операций " << GetAllCount() << "\t Сравнений = " << GetCmpCount() << endl;
		// Исследование лучшего случая (упорядоченный массив)
		SortArray(a, SizeArray[i]);
		cout << "Лучший случай:" << endl;
		ClearCoutn();
		ShellSort(a, SizeArray[i]);
		cout << "Для упорядоченного массива всего операций " << GetAllCount() << "\t Сравнений = " << GetCmpCount() << endl;
		// Исследование худшего случая 
		// (массив, упорядоченный в обратном порядке)
		UnSortArray(a, SizeArray[i]);
		cout << "Худший случай:" << endl;
		ClearCoutn();
		ShellSort(a, SizeArray[i]);
		cout << "Для массива, упорядоченного в обратном порядке, всего операций " << GetAllCount() << "\t Сравнений = " << GetCmpCount() << endl;
		delete a;
	}

	// Эксперименты с алгоритмом быстрой сортировки
	cout << endl;
	cout << "\t \t Быстрая сортировка:" << endl;
	// Цикл по разной размерности массива
	for (int i = 0; i < N; i++)
	{
		a = new BaseType[SizeArray[i]];
		// Исследование среднего случая (случайный массив)
		for (int j = 0; j < SizeArray[i]; j++) a[j] = ProbArray[i][j];
		cout << "Длина массива = " << SizeArray[i] << endl;
		cout << "Средний случай:" << endl;
		ClearCoutn();
		QuickSort(a, SizeArray[i]-1);
		cout << "Для случайно сгенерированного массива всего операций " << GetAllCount() << "\t Сравнений = " << GetCmpCount() << endl;
		// Исследование лучшего случая (упорядоченный массив)
		SortArray(a, SizeArray[i]);
		cout << "Лучший случай:" << endl;
		ClearCoutn();
		QuickSort(a, SizeArray[i]-1);
		cout << "Для упорядоченного массива всего операций " << GetAllCount() << "\t Сравнений = " << GetCmpCount() << endl;
		// Исследование худшего случая 
		// (массив, упорядоченный в обратном порядке)
		UnSortArray(a, SizeArray[i]);
		cout << "Худший случай:" << endl;
		ClearCoutn();
		QuickSort(a, SizeArray[i]-1);
		cout << "Для массива, упорядоченного в обратном порядке, всего операций " << GetAllCount() << "\t Сравнений = " << GetCmpCount() << endl;
		delete a;
	}

	// Эксперименты с алгоритмом пирамидальной сортировки
	cout << endl;
	cout << "\t \t Пирамидальная сортировка:" << endl;
	// Цикл по разной размерности массива
	for (int i = 0; i < N; i++)
	{
		a = new BaseType[SizeArray[i]];
		// Исследование среднего случая (случайный массив)
		for (int j = 0; j < SizeArray[i]; j++) a[j] = ProbArray[i][j];
		cout << "Длина массива = " << SizeArray[i] << endl;
		cout << "Средний случай:" << endl;
		ClearCoutn();
		heapSort(a, SizeArray[i]);
		cout << "Для случайно сгенерированного массива всего операций " <<GetAllCount() << "\t Сравнений = " << GetCmpCount() << endl;
		// Исследование лучшего случая (упорядоченный массив)
		SortArray(a, SizeArray[i]);
		cout << "Лучший случай:" << endl;
		ClearCoutn();
		heapSort(a, SizeArray[i]);
		cout << "Для упорядоченного массива всего операций " << GetAllCount() << "\t Сравнений = " << GetCmpCount() << endl;
		// Исследование худшего случая 
		// (массив, упорядоченный в обратном порядке)
		UnSortArray(a, SizeArray[i]);
		cout << "Худший случай:" << endl;
		ClearCoutn();
		heapSort(a, SizeArray[i]);
		cout << "Для массива, упорядоченного в обратном порядке, всего операций " << GetAllCount() << "\t Сравнений = " << GetCmpCount() << endl;
		delete a;
	}

	for (int i = 0; i < N; i++) delete ProbArray[i];
	return 0;
}
