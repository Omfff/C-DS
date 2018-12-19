#include<iostream>
#include<algorithm>
#include<iomanip>
#include<time.h>
#include<random>
#include<math.h>
using namespace std;
static unsigned long quickSortCount = 0;
static unsigned long mergeSortCount = 0;
static unsigned long radixSortCount = 0;
const int radix = 10;
template<class T>
void printResult(T*(&data), int n)
{
	for (int i = 0; i < n; i++)
		cout << data[i] << " ";
	cout << endl;
}
template<class T>
bool checkResult(T*(&data), int n)
{
	for (int i = 0; i < n - 1; i++)
		if (data[i] > data[i + 1])
			return false;
	return true;
}
template<class T>
int getDigit(T & num, int d) {
	int a[10] = { 1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000 };
	return abs(num / a[d-1])%10;
}
template<class T>
void radixSort(T*(&data), int left, int right, int d) {
	int count[radix];
	if (d <= 0)return;
	T  * bucket = new T[right - left + 1];

	for (int i = 0; i < radix; i++, radixSortCount++)count[i] = 0;
	for (int i = left; i <= right; i++, radixSortCount++) {
		count[getDigit(data[i], d)]++;
	}
	for (int j = 1; j < radix; j++, radixSortCount++)
		count[j] = count[j] + count[j - 1];
	int lastPos = count[radix - 1];
	for (int i = left; i <= right; i++) {
		int temp = getDigit(data[i], d);
		bucket[count[temp] - 1] = data[i];
		count[temp]--;
		radixSortCount++;
	}
	for (int i = left, j = 0; i <= right; i++, j++, radixSortCount++)
		data[i] = bucket[j];
	int p1, p2;
	//cout << left << " " << right << " " << d;
	//printResult(data, 15);
	delete[]bucket;
	for (int i = 0; i <radix; i++) {	
		p1 = count[i] + left;
		if (i == 9)
			p2 = lastPos - 1 + left;
		else
			p2 = count[i + 1] - 1 + left;
		radixSortCount++;
		if (p1 < p2&&d>1)
			radixSort(data, p1, p2, d - 1);
		}
	
}
template <class T>
class Heap {
public:
	static unsigned long count;
	int maxSize;
	T * heap;
	Heap(T * (&arr), int n) {
		heap = arr;
		maxSize = n;
	}
	~Heap();
	void siftDown(int start, int end) {
		int temp1 = 2 * start + 1;
		int temp2 = start;
		while (temp1 <= end) {
			if (temp1 + 1 <= end && heap[temp1] < heap[temp1 + 1])temp1++;
			if (heap[temp2] > heap[temp1])break;
			else {
				int temp = heap[temp1];
				heap[temp1] = heap[temp2];
				heap[temp2] = temp;
				temp2 = temp1;
				temp1 = temp1 * 2 + 1;
				count = count + 1;
			}
		}
	}
	unsigned long sort() {
		T temp;
		int begin = maxSize / 2;
		for (int i = begin; i >= 0; i--) {
			siftDown(i, maxSize - 1);
		}
		//printResult(heap, maxSize);
		for (int i = 0; i < maxSize - 1; i++) {
			temp = heap[maxSize - i - 1];
			heap[maxSize - i - 1] = heap[0];
			heap[0] = temp;
			siftDown(0, maxSize - i - 2);
			//printResult(heap, maxSize);
		}
		return count;
	}

};
template<class T>
 Heap<T>::~Heap() {}
template<class T>
unsigned long Heap<T>::count =0;
int getLength(int x)
{
	int length = 0;
	if (x == 0)
		return 1;
	while (x)
	{
		radixSortCount++;
		x /= 10;
		length++;
	}
	return length;
}
template<class T>
void reverseArray(T*(data), int left, int right) {
	T temp;
	//printResult(data, right - left + 1);
	for (int i = left, j = right; i < j; i++,j--) {
		temp = data[i];
		data[i] = data[j];
		data[j] = temp;
		radixSortCount++;
	}
}
template<class T>
void radixSortPre(T*(data), int n) {
	T temp;
	int nevigativeMax=0;
	int positiveMax=-1;
	int pivot;
	//printResult(data, n);
	for (int i = 0, j = n - 1; i != j;) {
		while (data[i] < 0 && i < j) {
			if (data[i] < nevigativeMax)
				nevigativeMax = data[i];
			i++;
			radixSortCount++;
		}
		while (data[j] >= 0 && i < j) {
			if (data[j] > positiveMax)
				positiveMax = data[j];
			j--;
			radixSortCount++;
		}
		if (i != j) {
			temp = data[i];
			data[i] = data[j];
			data[j] = temp;
			radixSortCount++;
		}
		else
			pivot = j;
		//printResult(data, n);
	}
	if (data[pivot] >= 0) {
		radixSort(data, pivot, n - 1, getLength(positiveMax));
		radixSort(data, 0, pivot - 1, getLength(nevigativeMax));
		reverseArray(data, 0, pivot - 1);
	}
	else {
		radixSort(data, pivot+1, n - 1, getLength(positiveMax));
		radixSort(data, 0, pivot, getLength(nevigativeMax));
		reverseArray(data, 0, pivot);
	}
}
template<class T>
void mergeSort(T*(&data), int left,int right,T*(&auxiliary) ){
	if (left < right) {
		int mid = (left + right) / 2;
		mergeSort(data, left, mid, auxiliary);
		mergeSort(data, mid+1, right, auxiliary);
		for (int i = left; i <= mid; i++,mergeSortCount++)
			auxiliary[i] = data[i];
		for (int i = mid+1;i <= right; i++,mergeSortCount++)
			auxiliary[i] = data[i];
		//printResult(auxiliary, 10);
		int iteL, iteR, iteD;
		for (iteL = left, iteR = mid + 1, iteD = left; iteL <= mid&&iteR <= right;mergeSortCount++) {
			data[iteD++] = auxiliary[iteL] <= auxiliary[iteR] ? auxiliary[iteL++] : auxiliary[iteR++];
		}
		if (iteL <= mid) {
			while (iteL <= mid) {
				data[iteD++] = auxiliary[iteL++];
				mergeSortCount++;
			}
		}
		if (iteR <= right) {
			while (iteR <= right) {
				data[iteD++] = auxiliary[iteR++];
				mergeSortCount++;
			}
		}
		//printResult(data, 10);
	}
}
template<class T>
unsigned long  heapSort(T*(&data), int n) {
	Heap<T> * heap = new Heap<T>(data, n);
	return heap->sort();	
}
template<class T>
unsigned long selectSort(T*(&data), int n) {
	int pos;
	T  temp;
	unsigned long count=0;
	for (int i = n-1; i > 0; i--) {
		temp = data[0];
		pos = 0;
		for (int j = 0; j <= i; j++) {
			if (data[j] > temp) {
				temp = data[j];
				pos = j;
				count++;
			}
		}
		temp = data[i];
		data[i] = data[pos];
		data[pos] = temp;
		count++;
	}
	return count;
}
template<class T>
unsigned long shellSort(T*(&data),int n) {
	T temp;
	int pos;
	unsigned long count=0;
	for (int gap = n / 3 + 1; gap >=1; gap = gap / 3 + 1) {
			for (int k = n-1; k >= 0; k--){
				temp = data[k];
				pos = k;
			for (int j = k; j < n; j += gap) {
				if (data[j] < temp) {
					data[j - gap] = data[j];
					count++;
					pos = j;
				}
				else if (temp < data[j])
					break;
				else
					continue;
			}
			data[pos] = temp;
			//printResult(data, n);
			count++;
		}
		if (gap == 1)
			break;
	}
	return count;
}
template<class T>
unsigned long insertSort(T*(&data), int n) {
	T temp;
	int pos;
	unsigned long count = 0;
	for (int i = n - 1; i >= 0; i--) {
		temp = data[i];
		pos = i;
		for (int j = i; j < n; j++) {
			if (temp > data[j]) {
				data[j - 1] = data[j];
				count++;
				pos = j;
			}
			else if (temp < data[j])
				break;
			else
				continue;
		}
		data[pos] = temp;
		count++;
	}
	return count;
}
template<class T>
unsigned long quickSort(T * (&data), const int left,const int right) {
	if (left < right) {
		T base=data[left],temp;
		int pivot;
		for (int i = left, j = right; i != j;) {
			while (data[i] <= base&&i < j)
				i++;
			while(data[j]>base&&i<j)
				j--;
			temp = data[j];
			data[j] = data[i];
			data[i] = temp;
			quickSortCount++;
			if (i == j) {
				if (base >= data[j])
					pivot = j;
				else
					pivot = j - 1;
			}
		}
		data[left] = data[pivot];
		data[pivot] = base;//printResult(data, 10);
		quickSort(data, left, pivot - 1);
		quickSort(data, pivot + 1, right);
	}
	return quickSortCount;
}
template<class T>
unsigned long bubbleSort(T*(&data),int n) {
	T temp;
	unsigned long count = 0;
	for (int i = n-1; i > 0; i--) {
		bool isReplace = false;
		for (int j = 0; j < i; j++) {
			if (data[j] > data[j + 1]) {
				temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
				count++;
				isReplace = true;
			}
		}
		if (isReplace == false)
			return count;
	}
	return count;
}
void mySort(int type, int n) {
	int * data = new int[n];
	int * auxilary = new int[n];
	default_random_engine e;
	for (int i = 0; i < n; i++) {
		data[i] = e();
	}
	//data[2] = 0;
	time_t start, ends;
	clock_t cstart, cends;
	unsigned long count;
	start = time(NULL);
	cstart = clock();
	switch (type) {
	case 1:
		count = bubbleSort(data,n);
		break;
		case 2:
			count = selectSort(data,n);
			break;
		case 3:
			count = insertSort(data,n);
			break;
		case 4:
			count = shellSort(data,n);
			break;
		case 5:
			//printResult(data, n);
			count = quickSort(data,0,n-1);
			break;
		case 6:
			count = heapSort(data,n);
			break;
		case 7:
			mergeSort(data, 0, n - 1, auxilary);
			count = mergeSortCount;
			break;
		case 8:
			radixSortPre(data, n);
			count = radixSortCount;
			break;
	}
	ends = time(NULL);
	cends = clock();
	//printResult(data, n);
	if (checkResult(data, n)) {
		switch (type) {
		case 1:
			cout << "冒泡排序交换次数：" << count << endl;
			cout << "冒泡排序所用时间：" << difftime(ends, start) << endl;
			cout << "冒泡排序Clock时间差：" << cends - cstart << endl;
			cout << endl;
			break;
		case 2:
			cout << "选择排序交换次数：" << count << endl;
			cout << "选择排序所用时间：" << difftime(ends, start) << endl;
			cout << "选择排序Clock时间差：" << cends - cstart << endl;
			cout << endl;
			break;
		case 3:
			cout << "插入排序交换次数：" << count << endl;
			cout << "插入排序所用时间：" << difftime(ends, start) << endl;
			cout << "插入排序Clock时间差：" << cends - cstart << endl;
			cout << endl;
			break;
		case 4:
			cout << "希尔排序交换次数:" << count << endl;
			cout << "希尔排序所用时间：" << difftime(ends, start) << endl;
			cout << "希尔排序Clock时间差：" << cends - cstart << endl;
			cout << endl;
			break;
		case 5:
			cout << "快速排序交换次数:" << count << endl;
			cout << "快速排序所用时间：" << difftime(ends, start) << endl;
			cout << "快速排序Clock时间差：" << cends - cstart << endl;
			cout << endl;
			break;
		case 6:
			cout << "堆排序交换次数:" << count << endl;
			cout << "堆排序所用时间：" << difftime(ends, start) << endl;
			cout << "堆排序Clock时间差：" << cends - cstart << endl;
			cout << endl;
			break;
		case 7:
			count = mergeSortCount;
			cout << "归并排序交换次数:" << count << endl;
			cout << "归并排序所用时间：" << difftime(ends, start) << endl;
			cout << "归并排序Clock时间差：" << cends - cstart << endl;
			cout << endl;
			break;
		case 8:
			count = radixSortCount;
			cout << "基数排序交换次数:" << count << endl;
			cout << "基数排序所用时间：" << difftime(ends, start) << endl;
			cout << "基数排序Clock时间差：" << cends - cstart << endl;
			cout << endl;
			break;
		}
	}
	delete[]data;
	delete[]auxilary;
	//printResult(data, n);
}

int main() {
	cout << "**" << setw(12) << " " << "排序算法比较" << setw(16) << " " << "**" << endl;
	cout << setfill('=') << setw(44) << "=" << endl;
	cout << "**" << setfill(' ') << setw(12) << " " << "1 --- 冒泡排序" << setw(14) << " " << "**" << endl;
	cout << "**" << setw(12) << " " << "2 --- 选择排序" << setw(14) << " " << "**" << endl;
	cout << "**" << setw(12) << " " << "3 --- 直接插入排序" << setw(10) << " " << "**" << endl;
	cout << "**" << setw(12) << " " << "4 --- 希尔排序" << setw(14) << " " << "**" << endl;
	cout << "**" << setw(12) << " " << "5 --- 快速排序" << setw(14) << " " << "**" << endl;
	cout << "**" << setw(12) << " " << "6 --- 堆排序" << setw(16) << " " << "**" << endl;
	cout << "**" << setw(12) << " " << "7 --- 归并排序" << setw(14) << " " << "**" << endl;
	cout << "**" << setw(12) << " " << "8 --- 基数排序" << setw(14) << " " << "**" << endl;
	cout << "**" << setw(12) << " " << "9 --- 退出程序" << setw(14) << " " << "**" << endl;
	cout << setfill('=') << setw(44) << "=" << endl;
	int num;
	cout << "请输入要产生的随机数的个数：";
	cin >> num;
	int command;
	bool mark = true;
	while (mark) {
		cout << "请选择排序算法:" ;
		cin >> command;
		if (command != 9)
			mySort(command,num);
		else
			break;
	}
}