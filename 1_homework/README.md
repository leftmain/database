Cache-oblivious алгоритм  

1) сравнение Б-дерева и бинарного дерева (базовый элемент - int):  
  алгоритм: поиск всех элементов дерева.  
  файл для теста, например: https://github.com/leftmain/big_files/blob/master/unique_10000000.txt  
  Б-дерево стабильно быстрее в 4-5 раз, m клал от 128 до 1024; чем больше m, тем быстрее поиск, но медленнее чтение.  

		сборка: make  
		запуск:  
			Б-дерево: ./a [m] [file]  
					где 2m - длина массива в узле, file - тествый файл  
			бинарное дерево: ./a [file]  
					где file - тествый файл  

2) транспонирование в лоб vs cache-blocked алгоритм:  
  файл для теста, например: https://github.com/leftmain/big_files/blob/master/i_100000000.txt  
  cache-blocked алгоритм делит матрицу на много маленьких блоков (их размер задефайнен в SIZE в matrix.cpp и по умолчанию стоит 32, алгоритм работает только для таких n, что SIZE | 2^n) и транспонирует эти блоки поочереди.  
  
		сборка: make  
		запуск:  
			./a            - размер матрицы 8192, составляется по формуле (формула задается функцией f в main.cpp)  
			./a [n]        - размер матрицы 2^n, составляется по формуле  
			./a [n] [file] - размер матрицы n, читает из файла file  
	
