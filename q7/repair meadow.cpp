#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
bool cmp(int  a, int  b) {
	
	return a > b;
}
class HuffmanTree {
	int sum;
public:
		HuffmanTree(vector<int> data, int n);
		int getSum() { return sum; }

 };
HuffmanTree::HuffmanTree(vector<int> data, int n)
{
	make_heap(data.begin(), (data.end()), cmp);
	int temp1 = 0;
	int temp2 = 0;
	int temp3 = 0;
	sum = 0;
	for (int i = 0; i < n - 1; i++) {
		pop_heap((data.begin()), (data.end()), cmp);
		temp1 = *(data.end() - 1);
		data.pop_back();
		pop_heap(data.begin(), (data.end()), cmp);
		temp2 = *(data.end()-1);
		data.pop_back();
		temp3 = temp1 + temp2;
		sum += temp1 + temp2;
		data.push_back(temp3);
		push_heap(data.begin(), (data.end()), cmp);
	}
 }
int main() {
	cout << "�����һ�и���������N��N��104������ʾҪ��ľͷ���N�顣" << endl;
	cout << "�ڶ��и���N������������ʾÿ��ľͷ�ĳ��ȡ�" << endl;
	int totalNum;
	cout << "������N=";
	cin >> totalNum;
	
	int tempLength;
	vector<int> length;
	
	for (int i = 0; i < totalNum; i++) {
		cin >> tempLength;
		length.push_back(tempLength);
	}
	if (totalNum == 1) {
		cout << length[0] << endl;
		system("pause");
	}
	HuffmanTree * hTree = new HuffmanTree(length, totalNum);
	cout << hTree->getSum() << endl;
	system("pause");
}
