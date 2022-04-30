#include"bignum.h"
void Khoitao(DSLK& a)  //khởi tạo danh sách liên kết
{
	a.pDau = NULL;
	a.pCuoi = NULL;
}
Node* taonode(int x)  //tạo 1 phần tử mới
{
	Node* p = new Node;
	p->data = x;
	p->pNext = NULL;
	return p;
}
void themcuoi(DSLK& a, int x)  //thêm node mới vào cuối danh sách liên kết
{
	Node* p = taonode(x);
	if (a.pDau == NULL && a.pCuoi == NULL)
	{
		a.pDau = a.pCuoi = p;
	}
	else
	{
		a.pCuoi->pNext = p;
		a.pCuoi = p;
	}
}
void chiasonguyen(DSLK& a, string x, int k) //chia số nguyên lớn thành từng phần gồm k số
{
	Khoitao(a);  //Khởi tạo DSLK để lưu số nguyên lớn
	int i = 0;   //chỉ số của string để chia số nguyên lớn làm các phần, mỗi phần có k chữ số
	int size = x.size();
	for (int j = 0; j < size; j++) //vòng lặp này để cho trường hợp người dùng nhập nhiều số 0 trước 1 số.VD: 0000001 thì sẽ biến chuỗi về thành 1
	{
		if (x[0] == '0') //nếu phần tử đầu là số 0 thì xóa nó
			x = x.substr(1, x.size() - 1); //x = phần còn lại của x trừ chỉ số đầu
		else
			break; //nếu không phải thì break vòng lặp
	}
	size = x.size(); //xác định lại độ dài của x nếu xảy ra trường hợp như vòng lặp trên
	for (i = size - k; i >= 0; i = i - k)  //cho chạy vòng lặp từ cuối string đến đầu
	{
		string so = x.substr(i, k);  //lấy chuỗi bắt đầu từ vị trí i, lấy k số
		int m = atoi(so.c_str());  //hàm chuyển từ chuỗi sang số.
		themcuoi(a, m);       // sau khi lấy được số này thì thêm nó vào cuối danh sách liên kết
	}
	if (i >= -k + 1)  //sẽ có trường hợp số chữ số của số nguyên lớn sẽ không chia hết cho k, vì vậy phần cuối cùng sẽ có ít hơn k chữ số
	{			//nên nó sẽ không được chia ở vòng lặp trên( do i<0) nên ta sẽ chia nó ở đây
		string so = x.substr(0, i + k);
		int m = atoi(so.c_str());
		themcuoi(a, m);
	}
}
void add(DSLK a, DSLK b, DSLK& sum, int k) //tính tổng 2 số nguyên lớn, trả kết quả qua DSLK sum
{
	Khoitao(sum);
	Node* p = a.pDau;  //Tính tổng là phải tính từ phải qua trái(cuối lên đầu). Mà chúng ta lưu DSLK dưới dạng các số cuối ở node đầu và các số đầu ở node cuối
	Node* q = b.pDau; //nên ta sẽ truy xuất từ các node đầu đến node cuối, rồi cộng lần lượt đến hết DSLK
	int nho = 0;	//Khi cộng sẽ có trường hợp khi vượt quá số biểu diễn nên cần biến nhớ để cộng cho đúng
	while (p != NULL && q != NULL)
	{
		int sum1 = p->data + q->data; //cộng 2 giá trị này lại
		if (nho == 1) //nếu biến nhớ bằng 1 thì cộng thêm vào sum 1 đơn vị
		{
			sum1++;
		}
		if (sum1 >= pow(10, k))//trường hợp sum có số chữ số lớn hơn số có thể biểu diễn được (gồm có k chữ số), ta sẽ nhớ 1 và lấy đúng k chữ số cuối
		{
			nho = 1;
			sum1 -= pow(10, k);
		}
		else
		{
			nho = 0; //nếu không thì không cần nhớ
		}
		themcuoi(sum, sum1);     //thêm k chữ số của sum vào cuối DSLK
		q = q->pNext;//truy xuất đến node tiếp theo
		p = p->pNext;
	}
	while (p != NULL) //sẽ có trường hợp 2 số nguyên lớn có số chữ số khác nhau nên số node có thể khác nhau và sẽ có 1 DSLK hết node trước
	{				//nên ta cần lưu các node còn lại của DSLK kia vào sum
		int sum1 = p->data;
		if (nho == 1)// nếu nhớ 1 thì cộng thêm vào như ở trên
		{
			sum1++;
		}
		if (sum1 >= pow(10, k))
		{
			nho = 1;
			sum1 -= pow(10, k);
		}
		else
		{
			nho = 0;
		}
		themcuoi(sum, sum1);
		p = p->pNext;
	}
	while (q != NULL)
	{
		int sum1 = q->data;
		if (nho == 1)
		{
			sum1++;
		}
		if (sum1 >= pow(10, k))
		{
			nho = 1;
			sum1 -= pow(10, k);
		}
		else
		{
			nho = 0;
		}
		themcuoi(sum, sum1);
		q = q->pNext;
	}
}
int compare(DSLK a, DSLK b)  //hàm này để so sánh 2 số nguyên lớn dương
{
	Node* p = a.pDau;
	Node* q = b.pDau;
	int dem1 = 1; //cái này là số node của số nguyên lớn a, ban đầu bằng 1 là tính node đầu tiên
	int dem2 = 1;////cái này là số node của số nguyên lớn b
	while (p->pNext != NULL)
	{
		p = p->pNext; //đếm số node của số nguyên lớn
		dem1++;
	}
	while (q->pNext != NULL)
	{
		q = q->pNext;
		dem2++;
	}
	if (dem1 > dem2)
		return 1; //nếu số nào có số node nhiều hơn thì số đó lớn hơn .return 1 nếu a lớn hơn
	else if (dem2 > dem1)
		return 2;  //return 2 nếu b lớn hơn
	else
	{
		if (p->data > q->data)  // so sánh 2 giá trị đầu của 2 số nguyên, cái nào lớn hơn thì số nguyên đó lớn hơn.
			return 1;
		if (q->data > p->data)
			return 2;
		else
			return 0;   //nếu bằng nhau thì sẽ return 0
	}
}
void tru(DSLK a, DSLK b, DSLK& hieu, int dieukien, int k)// hàm này ta sẽ lấy số a-b
{
	Node* p = a.pDau; //tương tự như hàm cộng, hàm trừ này ta cũng sẽ trừ từ phải qua trái của số. Mà phần bên phải nằm ở đầu danh sách
	Node* q = b.pDau; // nên ta sẽ trừ từ đầu dslk cho đến cuối
	int nho = 0;    //tương tự cộng, ta cũng sẽ có biến nhớ cho trừ
	while (p != NULL && q != NULL)
	{
		int tru = p->data - q->data;  //lấy node của a- b
		if (nho == 1)
		{
			tru--;      //nếu biến nhớ bằng 1 thì phải trừ đi 1 cho hiệu
		}
		if (tru < 0)
		{
			nho = 1;
			tru += pow(10, k); //nếu bé hơn 0 thì ta + 10^k (để lấy phần biểu diễn) và nhớ 1
		}
		else
		{
			nho = 0;
		}
		if (p == a.pCuoi)  //nếu như 2 số có số node bằng nhau và dslk a đã đến node cuối, ta phải xét điều kiện đã đưa vào,nếu
		{				// điều kiện =1 thì ta phải đổi dấu của hiệu, bằng 0 thì không đổi dấu
			if (dieukien == 1)
				tru = -tru; //đổi dấu
		}
		themcuoi(hieu, tru);// thêm phần node của hiệu vào sau dslk (lưu từ phải sang trái)
		q = q->pNext;
		p = p->pNext;
	}
	while (p != NULL)// vì a>b nên chắc chắn b không thể nhiều node hơn a được, vì vậy nên chỉ có trường hợp b đã hết node còn a thì chưa
	{
		int tru = p->data;
		if (nho == 1)
		{
			tru--;
		}
		if (tru < 0)
		{
			nho = 1;
			tru += pow(10, k);
		}
		else
		{
			nho = 0;
		}
		if (p == a.pCuoi)
		{
			if (dieukien == 1)
				tru = -tru;
		}
		themcuoi(hieu, tru);
		p = p->pNext;
	}
}
void subtract(DSLK a, DSLK b, DSLK& hieu, int k)
{
	Khoitao(hieu);
	int hieu1 = 0;    //đây là biến hiệu của 2 số
	int dieukien = 0;  //biến này là để xem số nào lớn hơn trong a,b.Vì nguyên tắc trừ là phải lấy số có giá trị lớn hơn trừ số nhỏ hơn
	if (compare(a, b) == 0) // và sau đó sẽ tùy theo điều kiện mà lấy dấu
	{
		themcuoi(hieu, hieu1); //nếu 2 số bằng nhau thì hiệu sẽ bằng 0.Ta thêm nó vào DSLK
		return;
	}
	else if (compare(a, b) == 2)  //nếu số b>số a thì hiệu 2 số sẽ có dấu âm. Ta lấy b-a rồi đổi dấu của hiệu
	{
		dieukien = 1; // điều kiện sẽ bằng 1 để chúng ta biết rằng phải đổi dấu của hiệu
	}
	if (dieukien == 1)
	{
		tru(b, a, hieu, dieukien, k); //hàm này sẽ lấy b-a rồi đổi dấu
	}
	else
	{
		tru(a, b, hieu, dieukien, k); //nếu a>b thì đk sẽ bằng 0.Hàm này lấy a-b và không đổi dấu
	}
}
void swap(DSLK& a, DSLK& b) //hàm này là đổi giá trị của 2 dslk cho nhau
{
	DSLK c = a;
	a = b;
	b = c;
}
int partition(DSLK* bigNum, int dau, int cuoi) //hàm này sẽ trả cho chỉ số của số đã sắp xếp đúng
{
	DSLK pivot = bigNum[cuoi]; //đặt pivot là phần tử cuối
	int i = dau;  //chỉ số i là chỉ số của số ta sẽ đổi chỗ nếu nó bé hơn pivot( tức là nằm bên trái của pivot, số lớn hơn pivot sẽ nằm bên phải)
	for (int j = dau; j < cuoi; j++)
	{
		if (compare(bigNum[j], pivot) == 2) //nếu pivot> số bignum j ,ta sẽ đổi chỗ nó với phần tử thứ i
		{
			swap(bigNum[j], bigNum[i]);
			i++;//tăng biến i lên vì lúc này ở bên trái nó đã là số lớn hơn pivot
		}
	}
	swap(bigNum[i], bigNum[cuoi]); //sau khi chạy xong vòng lặp, ta sẽ được 1 mảng gồm phần bên trái sẽ bé hơn pivot và phần bên phải sẽ lớn hơn pivot. Lúc này ta sẽ đổi chỗ pivot vào đúng vị trí i,là vị trí ở giữa 2 phần
	return i; //trả về chỉ số của phần tử đã đứng chính xác vị trí của nó trong mảng tăng dần.
}
void quicksort(DSLK* bigNum, int dau, int cuoi)
{
	if (dau < cuoi)//nếu chỉ số đầu lớn hơn chỉ số cuối thì ta sẽ sắp xếp cho mảng.
	{
		int pi = partition(bigNum, dau, cuoi);  //pi là chỉ số mà số đó đã ở đúng vị trí trong mảng
		quicksort(bigNum, dau, pi - 1);		//lúc này ta đã có 1 số có chỉ số pi ở đúng vị trí, nên ta phải sắp xếp 2 mảng gồm đầu mảng đến pi-1 và từ pi+1 đến cuối mảng
		quicksort(bigNum, pi + 1, cuoi);
	}
}
void merge(DSLK* bignum, int dau, int cuoi, int mid)
{
	int nL = mid - dau + 1;   //số phần tử của mảng trái
	int nR = cuoi - mid;      //số phần tử của mảng phải
	DSLK* bignumL = new DSLK[nL];  //tạo ra mảng trái
	DSLK* bignumR = new DSLK[nR];  //tạo ra mảng phải
	for (int i = 0; i < nL; i++)
	{
		bignumL[i] = bignum[dau + i];   //copy giá trị của phần bên trái mảng vào mảng trái
	}
	for (int i = 0; i < nR; i++)
	{
		bignumR[i] = bignum[mid + 1 + i]; //copy giá trị của phần bên phải mảng vào mảng phải
	}
	int iR = 0, iL = 0;
	int ibignum = dau;
	while (iR < nR && iL < nL)
	{
		if (compare(bignumR[iR], bignumL[iL]) == 2)  //so sánh các số của mảng trái và phải, cái nào bé hơn sẽ được thêm vào mảng trước
		{
			bignum[ibignum++] = bignumR[iR++];  //tăng chỉ số của iR để lấy số tiếp theo của mảng phải so sánh với số hiện tại của mảng trái
		}
		else
		{
			bignum[ibignum++] = bignumL[iL++];
		}
	}
	while (iR < nR) //sẽ có 1 trong 2 mảng hết phần tử trước nên ta phải đưa các phần tử của mảng còn lại vào mảng chính
	{
		bignum[ibignum++] = bignumR[iR++];
	}
	while (iL < nL)
	{
		bignum[ibignum++] = bignumL[iL++];
	}
}
void mergesort(DSLK* bignum, int dau, int cuoi)
{
	if (dau < cuoi)
	{
		int mid = (cuoi + dau) / 2;  // ta chia mảng ra làm 2 phần
		mergesort(bignum, dau, mid);  //sắp xếp mảng bên trái
		mergesort(bignum, mid + 1, cuoi); // sắp xếp mảng bên phải
		merge(bignum, dau, cuoi, mid);  //gộp 2 mảng với nhau
	}
}
void inso(DSLK a, Node* p, int k, fstream& ghi)
{
	if (p == a.pCuoi)  //vì chúng ta lưu các số cuối ở đầu dslk và các số đầu ở cuối dslk nên ta phải xuất ngược từ cuối danh sách liên kết lên đầu
	{
		ghi << p->data;
	}
	else
	{
		inso(a, p->pNext, k, ghi); //in số ở các node sau
		int x = p->data;
		while (x < pow(10, k - 1) && k>1)  //trường hợp giá trị của node đó không đủ k số.VD k=3 nhưng node đó có giá trị bằng 23 thì phải thêm số 0 đằng trước cho thành 023
		{										//với trường hợp k bằng 1 thì ko cần vì giá trị nó chỉ có thể nằm từ 0 đến 9
			ghi << 0;
			x = x * 10;
		}
		ghi << p->data;
	}
}
void tinhbieuthuc(int k, char* input, char* output)
{
	fstream doc, ghi;
	doc.open(input, ios::in);
	ghi.open(output, ios::out);
	if (!doc.is_open())
	{
		cout << "Khong mo duoc";
		return;
	}
	if (!ghi.is_open())
	{
		cout << "Khong mo duoc";
		return;
	}
	int n = 0;  //đọc vào số biểu thức
	doc >> n;
	ghi << n; //ghi số biểu thức vào biến output
	ghi << endl;
	doc.ignore();
	for (int i = 0; i < n; i++) //cho chạy từng biểu thức một
	{
		string s;
		getline(doc, s);//ta dùng biến s để lưu một biểu thức của một dòng (có khoảng trắng)
		int m = 0; //chỉ số đầu trong việc tách các số và dấu
		int khoangtrang = 0; //số khoảng trắng trong biểu thức
		for (int j = 0; j < s.size(); j++) //đếm số khoảng trắng
		{
			if (s[j] == ' ')
				khoangtrang++;
		}
		string* sovadau = new string[khoangtrang * 2 + 1];  // mảng này để lưu các số và dấu có trong biểu thức.Số phần tử của nó sẽ bằng số kh
		DSLK* bigNum = new DSLK[(khoangtrang / 2) + 1];  // dslk lưu các số có trong biểu thức.Số phần tử của nó là khoảng trắng/2+1
		int h = 0;
		for (int j = 0; j < s.size(); j++)
		{
			if (s[j] == ' ') //nếu s[j] bằng khoảng trắng, tức là kết thúc một số/dấu
			{
				sovadau[h++] = s.substr(m, j - m); //ta sẽ lưu nó vào mảng
				m = j + 1;
			}
		}
		sovadau[h++] = s.substr(m, s.size() - m);//vì số cuối cùng sau nó sẽ không có khoảng trắng nên ta phải lưu nó sau khi hết vòng for
		for (int j = 0; j < ((khoangtrang / 2) + 1); j++) // cho chạy từ đầu đến cuối mảng bignum
		{
			chiasonguyen(bigNum[j], sovadau[2 * j], k);  //vì ở mảng sovadau, các số sẽ nằm ở vị trí chẵn còn dấu ở vị trí lẻ.Nên ta nhân 2 vào chỉ số j ở mảng đó
		}
		DSLK ketqua;//biến này lưu kết quả của biểu thức
		DSLK ketqua1 = bigNum[0]; //biến này lưu kết quả tạm của biểu thức, giá trị này lúc đầu sẽ bằng số nguyên đầu
		int l = 1;
		for (int j = 1; j < h; j += 2) //trong mảng sovadau,dấu sẽ nằm các vị trí lẻ,nên sẽ bắt đầu từ 1 và bước chạy là 2  
		{
			if (sovadau[j] == "+")//nếu là dấu cộng
			{
				if (ketqua1.pCuoi->data < 0)
				{
					ketqua1.pCuoi->data = -ketqua1.pCuoi->data; //nếu ketqua1 âm, ta sẽ được một số âm + số dương,biểu thức này tương đương số dương trừ đi trị tuyệt đối
					subtract(bigNum[l++], ketqua1,ketqua,k);   //tức là ta sẽ đổi dấu của số âm để nó thành số dương rồi làm phép trừ đi nó
					ketqua1 = ketqua;
				}
				else
				{
					add(ketqua1, bigNum[l++], ketqua, k); //cộng kết quả tạm và số tiếp theo, trả kết quả vào biến ketqua
					ketqua1 = ketqua;  //lưu kết quả tạm vào để tính tiếp
				}
				
			}
			if (sovadau[j] == "-")
			{
				if (ketqua1.pCuoi->data < 0)
				{
					ketqua1.pCuoi->data = -ketqua1.pCuoi->data;//nếu ketqua1 âm thì sẽ thành số âm trừ số dương,tương đương biểu thức 2 số âm cộng nhau và cũng tương đương 2 trị tuyệt đối của 2 số âm cộng lại rồi lấy dấu trừ
					add(ketqua1, bigNum[l++], ketqua, k);  //vậy nên ta đổi dấu của ketqua1 để nó thành số dương rồi cộng với số đang xét trong mảng
					ketqua.pCuoi->data = -ketqua.pCuoi->data; //rồi lấy dấu trừ cho kết quả
					ketqua1 = ketqua;
				}
				else
				{
					subtract(ketqua1, bigNum[l++], ketqua, k);
					ketqua1 = ketqua;
				}
			}
		}
		Node* q = ketqua.pCuoi;
		if (q->data < 0)
		{
			ghi << "NaN" << endl;  //nếu kết quả biểu thức <0 thì ghi NaN
		}
		else
		{
			inso(ketqua, ketqua.pDau, k, ghi);
			ghi << endl;
		}
		delete[] sovadau;
		delete[] bigNum;
	}
	doc.close();
	ghi.close();
	cout << "Ghi thanh cong" << endl;
}
void sapxep(int k, char* input, char* output, int lenh)
{
	fstream doc, ghi;
	doc.open(input, ios::in);
	ghi.open(output, ios::out);
	if (!doc.is_open())
	{
		cout << "Khong mo duoc";
		return;
	}
	if (!ghi.is_open())
	{
		cout << "Khong mo duoc";
		return;
	}
	int n;
	doc >> n;
	ghi << n;
	ghi << endl;
	DSLK* bigNum = new DSLK[n];// cấp phát mảng BigNum n phần tử
	for (int i = 0; i < n; i++)
	{
		string s;  
		doc >> s;  //đọc số bignum theo kiểu string
		chiasonguyen(bigNum[i], s, k);   //chuyển BigNum sang dạng dslk
	}
	if (lenh == 1)  //nếu lệnh=1, ta sẽ dùng quick sort để sắp xếp mảng
	{
		quicksort(bigNum, 0, n - 1);
	}
	else //còn không sẽ dùng merge sort
	{
		mergesort(bigNum, 0, n - 1);
	}
	for (int i = 0; i < n; i++)// ghi số vào file
	{
		inso(bigNum[i], bigNum[i].pDau, k, ghi);
		ghi << endl;
	}
	delete[] bigNum;
	cout << "sap xep thanh cong" << endl;
	doc.close();
	ghi.close();
}
