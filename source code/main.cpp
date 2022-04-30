#include"bignum.h"
int main(int argc, char* argv[])
{
	if (argc != 5 )
	{
		cout << "Nhap so luong tham so dong lenh sai" << endl;
	}
	else
	{
		int k = atoi(argv[2]);
		if (k < 0)
		{
			cout << "Gia tri k khong hop le:";
			return 0;
		}
		if (strcmp(argv[1], "-comp") == 0 )
		{
			tinhbieuthuc(k, argv[3], argv[4]);
		}
		else if (strcmp(argv[1], "-qsort") == 0)
		{
			sapxep(k, argv[3], argv[4], 1);
		}
		else if (strcmp(argv[1], "-msort") == 0)
		{
			sapxep(k, argv[3], argv[4], 0);
		}
		else
		{
			cout << "Nhap sai tham so dong lenh";
		}
	}
	return 0;
}