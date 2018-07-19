#include <iostream>
#include <cstdarg>
using namespace std;

struct Array
{
	int *buffer;      // 数据区
	int *dimlength;   // 各维长度
	int *partlength;  // 换算辅助
	int dims;  // 维数
};

int InitArray(Array &A, int dims, ...)
{
	A.dims = dims;
	A.dimlength = new int[dims];
	A.partlength = new int[dims];

	va_list arg_ptr;
	va_start(arg_ptr, dims);

	int length = 1;    // 统计数据总数
	for (int i = 0; i < dims; i++)
	{
		int k = va_arg(arg_ptr, int);
		A.dimlength[i] = k;
		length *= k;
	}

	// 计算partlength
	A.partlength[dims - 1] = 1;
	for (int i = dims - 2; i >= 0; i--)
		A.partlength[i] = A.partlength[i + 1] * A.dimlength[i + 1];

	A.buffer = new int[length];

	va_end(arg_ptr);

	return 0;
}

int DestroyArray(Array &A)
{
	delete[]A.buffer;
	delete[]A.dimlength;
	A.buffer = NULL;
	A.dimlength = NULL;
	A.dims = 0;
	return 0;
}

int Get(Array &A, int i0, ...)
{
	va_list arg_ptr;
	va_start(arg_ptr, i0);

	int aIndex = i0*A.partlength[0];
	for (int i = 1; i < A.dims; i++)
	{
		aIndex += va_arg(arg_ptr, int)*A.partlength[i];
	}

	va_end(arg_ptr);
	return A.buffer[aIndex];
}

void Set(Array &A, int value, ...)
{
	va_list arg_ptr;
	va_start(arg_ptr, value);

	int aIndex = 0;
	for (int i = 0; i < A.dims; i++)
	{
		aIndex += va_arg(arg_ptr, int)*A.partlength[i];
	}

	va_end(arg_ptr);
	A.buffer[aIndex] = value;
}

int main()
{
	Array A;
	InitArray(A, 3, 4, 5, 6);
	for (int i = 0; i < A.dims; i++) cout << A.partlength[i] << ", "; cout << endl;

	Set(A, 11, 1, 2, 2);
	cout << Get(A, 1, 2, 2) << endl;

	DestroyArray(A);
	system("pause");
	return 0;
}