#include<iostream>
#include<cmath>
#include<string>
#include<fstream>
using namespace std;
struct Node  //đây là phần tử của danh sách liên kết
{
	int data;
	Node* pNext;
};
struct DSLK  //đây là danh sách liên kết
{
	Node* pDau;
	Node* pCuoi;
};
void Khoitao(DSLK& a);  //khởi tạo danh sách liên kết
Node* taonode(int x);  //tạo 1 phần tử mới
void themcuoi(DSLK& a, int x);  //thêm node mới vào cuối danh sách liên kết
void chiasonguyen(DSLK& a, string x, int k); //chia số nguyên lớn thành từng phần gồm k số
void add(DSLK a, DSLK b, DSLK& sum, int k);//tính tổng 2 số nguyên lớn, trả kết quả qua DSLK sum
int compare(DSLK a, DSLK b);  //hàm này để so sánh 2 số nguyên lớn dương
void tru(DSLK a, DSLK b, DSLK& hieu, int dieukien, int k);// hàm này ta sẽ lấy số a-b
void subtract(DSLK a, DSLK b, DSLK& hieu, int k);
void swap(DSLK& a, DSLK& b); //hàm này là đổi giá trị của 2 dslk cho nhau
int partition(DSLK* bigNum, int dau, int cuoi); //hàm này sẽ trả cho chỉ số của số đã sắp xếp đúng
void quicksort(DSLK* bigNum, int dau, int cuoi);
void merge(DSLK* bignum, int dau, int cuoi, int mid);
void mergesort(DSLK* bignum, int dau, int cuoi);
void inso(DSLK a, Node* p, int k, fstream& ghi);
void tinhbieuthuc(int k, char* input, char* output);
void sapxep(int k, char* input, char* output, int lenh);