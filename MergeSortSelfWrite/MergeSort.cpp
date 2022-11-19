#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <chrono>

void inputArray(int* a, int& count) {
	std::string str;
	char* str1 = new char[500000];
	std::cout << "Please input the array you want to sort:" << std::endl;
	getline(std::cin, str);
	char* ch;
	str.copy(str1, 500000);
	ch = strtok(str1, " .");
	while (1) {
		a[count] = atoi(ch);
		ch = strtok(NULL, " .");
		if (ch == NULL || (ch[0] < 48 && ch[0] != 45) || ch[0] > 57) {
			count++;
			break;
		}
		count++;
	}
	delete[] str1;
	str1 = nullptr;
}

void swap(int& a, int& b) {
	a = a + b;
	b = a - b;
	a = a - b;
}

void printSortedArray(int* a, int count) {
	std::cout << "The Array after has been sorted is:\n";
	for (int j = 0; j < count; ++j)
		std::cout << a[j] << " ";
}

void Merge(int* a, const int& left, const int& mid, const int& right) {
	int temp;
	for (int i = mid + 1; i <= right; ++i) {
		temp = a[i];
		int j = i - 1;
		while (a[j] > temp && j >= 0) {
			--j;
		}
		for (int k = i; k > j + 1; --k)
			a[k] = a[k - 1];
		a[j + 1] = temp;
	}
}

void merge(int* a, const int& left, const int& mid, const int& right)
{
	int LeftArrayTotalElement = mid - left + 1;
	int rightArrayTotalElement = right - mid;
	int* leftArray = new int[LeftArrayTotalElement],
		*rightArray = new int[rightArrayTotalElement];
	for (int i = 0; i < LeftArrayTotalElement; ++i)
		leftArray[i] = a[left + i];
	for (int i = 0; i < rightArrayTotalElement; ++i)
		rightArray[i] = a[mid + 1 + i];
	int leftPos = 0,
		rightPos = 0,
		idx = left;
	while (leftPos < LeftArrayTotalElement && rightPos < rightArrayTotalElement)
		if (leftArray[leftPos] < rightArray[rightPos])
			a[idx++] = leftArray[leftPos++];
		else
			a[idx++] = rightArray[rightPos++];
	while (leftPos < LeftArrayTotalElement)
		a[idx++] = leftArray[leftPos++];
	while (rightPos < rightArrayTotalElement)
		a[idx++] = rightArray[rightPos++];	
	delete[] leftArray;
	delete[] rightArray;
}

void mergeSort(int* a, const int& left, const int& right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSort(a, left, mid);
		mergeSort(a, mid + 1, right);
		merge(a, left, mid, right);
	}
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	int* a = new int[10000];
	int count = 0;
	inputArray(a, count);
	auto start = std::chrono::high_resolution_clock::now();
	mergeSort(a, 0, count - 1);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	printSortedArray(a, count);
	std::cout << "\nExecute time of Insertion sort is :" << duration.count() << " microseconds" << std::endl;
	//printSortedArray(a, count);
	delete[] a;
	a = nullptr;
	return 0;
}