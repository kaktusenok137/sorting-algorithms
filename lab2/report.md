# Выполнение

Методы сортировки, в зависимости от лежащего в их основе приема, можно разбить на три базовых класса:
1)	сортировка вставками;
2)	сортировка выбором;
3)	сортировка обменом.

Реализация сортировок по возрастанию (чтобы изменить это – необходимо просто поменять знак в листинге). Для получения результатов количества операций создается массив, упорядоченный по убыванию. Результаты можно увидеть в таблице 3.1.

<p align="center">Таблица 3.1. Массив, упорядоченный в обратном порядке</p>

![image](https://user-images.githubusercontent.com/76211121/187222395-9a3f6798-8f25-4c1f-87a8-7f7bab73fc91.png)

![image](https://user-images.githubusercontent.com/76211121/187222442-4f4f0358-2773-4b1d-9fb9-25d779f0ea05.png)
<p align="center">Рисунок 1. График зависимостей количества операций от количества элементов в массиве</p>

В данном случае на вход в функции сортировок подается массив уже упорядоченный по возрастанию. Результаты можно увидеть в таблице 3.2.

<p align="center">Таблица 3.2. Упорядоченный массив</p>

![image](https://user-images.githubusercontent.com/76211121/187222876-58301076-b599-421d-a6fe-f55209f92679.png)

![image](https://user-images.githubusercontent.com/76211121/187222900-46ce8506-b74c-48a9-adb4-a5351428df88.png)
<p align="center">Рисунок 2. График зависимостей количества операций от количества элементов в массиве</p>

Следующий способ проверки работы сортировок – подача в функцию случайно сгенерированного массива в промежутке от 0 до 100. Результаты можно увидеть в таблице 3.3.

<p align="center">Таблица 3.3. Неупорядоченный массив</p>

![image](https://user-images.githubusercontent.com/76211121/187223076-8e0521de-3d08-4840-b31f-a4df58ae8c2e.png)

![image](https://user-images.githubusercontent.com/76211121/187223098-ae4611b1-d21f-471e-9ab1-479a8c6b5287.png)
<p align="center">Рисунок 3. График зависимостей количества операций от количества элементов в массиве</p>

Рассмотрим результаты операций на случайно сгенерированном массиве. Размеры массивов находятся в промежутке от 100 до 900 элементов.

<p align="center">Таблица 3.4. Случайно сгенерированный массив размером от 100 до 900 элементов</p>

![image](https://user-images.githubusercontent.com/76211121/187223306-5721b456-609a-47f6-9e63-744c1b9da3ab.png)

![image](https://user-images.githubusercontent.com/76211121/187223437-b5166834-7769-46d8-a7cf-7568c59b79ba.png)
<p align="center">Рисунок 4. График зависимостей количества операций от количества элементов в массиве</p>

# Выводы
Аналитические выражения функций зависимости количества операций сравнения от количества элементов в массиве.

<b>Сортировка вставками:</b>
<br>Упорядоченный массив: С(N)=N-1
<br>Массив, упорядоченный в обратном порядке: С(N)=(N-1) *N/2
<br>Случайный массив: С(N)=N

<b>Сортировка выбором:</b>
<br>Упорядоченный массив: С(N)= N*(N-1)/2
<br>Массив, упорядоченный в обратном порядке: С(N)= N*(N-1)/2
<br>Случайный массив: С(N)=N*(N-1)/2

<b>Сортировка обменом:</b>
<br>Упорядоченный массив: С(N)=N*(N-1)/2
<br>Массив, упорядоченный в обратном порядке: С(N)=N*(N-1)/2
<br>Случайный массив: С(N)=N*(N-1)/2

<b>Сортировка Шелла:</b>
<br>Упорядоченный массив: С(N)=N(log2N)/2
<br>Массив, упорядоченный в обратном порядке:  С(N)=N(log2N)
<br>Случайный массив: С(N)=N(log2N)

<b>Сортировка Хоара:</b>
<br>Упорядоченный массив: С(N)=N(log2N)
<br>Массив, упорядоченный в обратном порядке: С(N)=N(log2N)
<br>Случайный массив: С(N)=N(log2N) *1,5

<b>Пирамидальная сортировка:</b>
<br>Упорядоченный массив: С(N)=N(log2N) *2
<br>Массив, упорядоченный в обратном порядке: С(N)=N(log2N) *2
<br> массив: С(N)=N(log2N) *2

Наиболее эффективными сортировками на массивах размером от 5 до 45 элементов оказались сортировка Хоара (известная как быстрая сортировка) и сортировка вставками, проявившая себя на сортировке упорядоченного массива. Худшей сортировкой на массивах, упорядоченных в обратном порядке и на неупорядоченном массиве, оказалась сортировка обменом (известная как пузырек). На упорядоченном массиве худшей сортировкой стала пирамидальная.
При работе сортировок на массивах размером от 100 до 900 элементов лучшей стала сортировка Хоара, так как число операций на случайно сгенерированном массиве длинной 900 элементов не более 20000. Худшая сортировка – обменом (на 900 элементах количество операций более 810000).