#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
int a[100][100], E[100][100];
int n, m;
int res;
int Arow, Acol;
typedef struct sinhvien{
	char ms[10];
	char hoten[35];
	char gioitinh[5];
	int hedaotao; 
	char khoahoc[10];
	char nganh[30];
	int tongtinchi=0;
	float dtbtl;
    int tonghocphan;
	int hpdat=0;
	int hpkdat=0;
	int tongtctl=0;
	typedef struct hocphan {
		char mhp[10];
		char tenhp[50];
		int sotc;
		int loaihp;
		int hk;
		float diemtongket;
	}HP;
	HP hp[100];
}SV;
void Nhapmatran(int x[100][100], int &n, int &m){
    do{
        printf("\nNhap vao so luong dong: ");
        scanf("%d", &n);
        printf("\nNhap vao so luong cot: ");
        scanf("%d", &m);
        if(n<0 || m<0){
            printf("\nSo luong dong va cot phai lon hon 0. Nhap lai!");
        }
    }while (n<0 || m<0);
    for (int i=0; i < n; i++){
        for(int j=0; j<m; j++){
            printf("\nx[%d][%d]= ", i, j);
            scanf("%d", &x[i][j]);
        }
    }
}
void Nhapmatranrandom(int x[100][100], int &n , int &m){
    do{
		printf("Nhap vao so dong: ");
		scanf("%d", &n);
		printf("\nNhap vao so cot: ");
		scanf("%d", &m);
	} while (m <= 0 || n <= 0);
	srand(time(NULL));
	for (int i = 0; i < m; i++){
		for (int j = 0; j < n; j++){
			x[i][j] = rand()%100;
		}
	}
}
void Nhapmangtufile(int x[100][100], int &n, int &m){
    FILE *fp;
    int i, j;
    fp = fopen("Matran.txt", "r"); 
    if(fp==NULL){
        printf("Loi mo file!");
        exit(1);
    }
    fscanf(fp, "%d", &n);
    fscanf(fp, "\n%d", &m);
    printf("So hang cua ma tran: %d\n", n);
    printf("So cot cua ma tran: %d\n", m);   
    i = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            fscanf(fp, "%d\n", &x[i][j]);
        }
   }
    printf("\nMa tran: \n");
    for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                printf(" %d ", x[i][j]);
                printf("\t");
            }
            printf("\n");
    }
    fclose(fp);
}
void Xuatmatran(int x[100][100], int n, int m){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            printf("%d", x[i][j]);
            printf("\t");
        }
        printf("\n");
    }
}
void Tbcbien(int x[100][100], int n, int m){
    int s=0, dem=0;
    for(int j=0; j<m; j++){
        s+=x[0][j];
        dem++;
    }
    for(int i=1; i<n; i++){
        s+=x[i][0];
        dem++;
    }
    for(int j=1; j<m; j++){
        s+=x[n-1][j];
        dem++;
    }
    for(int i=1; i<n-1; i++){
        s+=x[i][m-1];
        dem++;
    }
    float tb=(float)s/dem;
    printf("\nTrung binh cong duong bien la: %.2f", tb);
}
void Tbcheochinh(int x[100][100], int n, int m){
    int s=0;
    int dem=0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(i==j){
                s+=x[i][j];
                dem++;
            }
        }
    }
    float tb=(float)s/dem;
    printf("\nTrung binh cong duong cheo chinh la: %.2f", tb);
}
void Tbcheophu(int x[100][100], int n, int m){
    int s=0;
    int dem=0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(i+j==m-1){
                s+=x[i][j];
                dem++;
            }
        }
    }
    float tb=(float)s/dem;
    printf("\nTrung binh cong duong cheo phu la: %.2f", tb);
}
bool Checkthinhvuong(int a){
    int check=a;
    int s=0, c;
    while(check!=0){
        c=check%10;
        s+=c*c*c;
        check/=10;
    }
    if(s==a){
        return true;
    }else{
        return false;
    }
}
void Lietkethinhvuong(int x[100][100], int n, int m){
    for(int j=0; j<m; j++){
        printf("\nCot thu %d:", j);
        for(int i=0;i<n; i++){
            if(Checkthinhvuong(x[i][j])){
                printf(" %d  ", x[i][j]);
            }
        }
    }
}
int KiemTraSoNguyenTo(int n){
    if (n < 2)
        return 0;
    for (int i = 2; i <= sqrt(n); i++){
        if (n % i == 0){
            return 0;
        }
    }
    return 1;
}
double TrungBinhNhanNguyenToTungDong(int x[100][100], int n, int row){
    long tich = 1;
    int dem = 0;
    for (int i = 0; i < n; i++){
        if (KiemTraSoNguyenTo((x[row][i]))){
            tich *= x[row][i];
            dem++;
        }
    }
    return pow(tich, 1 / (float)dem);
}
void MaxTrungBinhNhanNguyenTo(int x[100][100], int n, int m){
    double max = TrungBinhNhanNguyenToTungDong(x, m, 0);
    int vitri;
    for (int i = 0; i < n; i++){
        if (TrungBinhNhanNguyenToTungDong(x, m, i) > max){
            max = TrungBinhNhanNguyenToTungDong(x, m, i);
            vitri = i;
        }
    }
    printf("\nDong co trung binh nhan cac so nguyen to lon nhat la %d", vitri);
}

void Doigiatrihaicot(int x[100][100], int n){
    int c1,c2;
    printf("\nNhap vao hai cot can hoan doi: "); scanf("%d%d", &c1, &c2);
    for(int i=0; i<n; i++){
        int temp=x[i][c1];
        x[i][c1]=x[i][c2];
        x[i][c2]=temp;
    }
}
void Swap(int &a, int &b){
    int temp;
    temp = a;
    a=b;
    b=temp;
}
/*
void Chanletang(int x[100][100], int y[2][100], int n, int m){
    int dem=0, dem1=0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(x[i][j]%2==0){
                y[0][dem]=x[i][j];
                dem++;
            }else{
                y[1][dem1]=x[i][j];
                dem1++;
            }
        }
    }
    for(int i=0; i<dem; i++){
		int vitrinhonhat = i;
		for(int j=i+1; j<dem; j++){
			if(y[0][j]<y[0][vitrinhonhat])
				vitrinhonhat = j;
		}
		Swap(y[0][i],y[0][vitrinhonhat] );
	}
    for(int i=0; i<dem1; i++){
		int vitrilonnhat = i;
		for(int j=i+1; j<dem1; j++){
			if(y[1][j]>y[1][vitrilonnhat])
				vitrilonnhat = j;
		}
		Swap(y[1][i],y[1][vitrilonnhat] );
	}
    for(int j=0; j<dem; j++){
        printf("%d", y[0][j]);
        printf("\t");
    }
    printf("\n");
    for(int j=0; j<dem1; j++){
        printf("%d", y[1][j]);
        printf("\t");
    }
}
*/
void Sapxepchantanglegiam(int a[100][100], int m, int n)
{
	int k = m * n;
	for (int i = 0; i < k - 1; i++)
	{
		for (int j = i + 1; j < k; j++)
		{
			if(a[i / n][i % n] % 2 == 0 && a[j / n][j % n] % 2 == 0 && a[i/n][i%n]>a[j/n][j%n]
				|| a[i / n][i % n] % 2 != 0 && a[j / n][j % n] % 2 != 0 && a[i/n][i%n]<a[j/n][j%n])
			{
				Swap(a[i / n][i % n], a[j / n][j % n]);
			}
		}
	}
}
void Xuathaimatran(int x[100][100], int n, int m){
    int c[100][100] = {0}, d[100][100] = {0 };
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(x[i][j]>0){
                c[i][j]=x[i][j];
            }else{
                d[i][j]=x[i][j];
            }
        }
    }
    printf("\nMa tran duong: \n");
    Xuatmatran(c,n,m);
    printf("\nMa tran am: \n");
    Xuatmatran(d,n,m);
}
/*
void Demsolanxuathien(int x[100][100], int n, int m){
    int e[100][100];
    int a, b;
    int dem=0;
    printf("\nNhap vao ma tran E(dong va cot phai nho hon ma tran A)");
    Nhapmatran(e,a,b);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            for(int l=0; l<a; l++){
                for(int k=0; k<b; k++){
                    if(e[l][k]==x[i][j]){
                        dem++;
                    }
                }
            }
        }
    }
    printf("\nSo lan xuat hien cua ma tran E trong ma tran A la: %d", dem);
}
*/
int AsubnetBmatrix(int A[][100], int B[][100], int aRow, int aCol, int bRow, int bCol)
{
	int iARow, iACol;
	int iBRow, iBCol;
	bool flg;
	int cnt = 0;

	for (iBRow = 0; iBRow <= bRow - aRow; iBRow++)
	{
		for (iBCol = 0; iBCol <= bCol - aCol; iBCol++)
		{
			flg = true;
			for (iARow = 0; iARow < aRow; iARow++)
			{
				for (iACol = 0; iACol < aCol; iACol++)
				{
					if (A[iARow][iACol] != B[iBRow + iARow][iBCol + iACol])
					{
						flg = false;
						break;
					}
				}
				if (flg == false)
				{
					break;
				}
			}
			if (flg == true)
			{
				cnt++;
			}
		}
	}
	return cnt;
}
void ImportData(int Matrix[][100], int nRow, int nCol){
	int iRow, iCol;
	for (iRow = 0; iRow < nRow; iRow++)
		for (iCol = 0; iCol < nCol; iCol++){
			printf("\nA[%d][%d] = ", iRow, iCol);
			scanf("%d", &Matrix[iRow][iCol]);
		}
}
void PrintMatrix(int Matrix[][100], int nRow, int nCol){
	int iRow, iCol;
	for (iRow = 0; iRow < nRow; iRow++){
		printf("\n");
		for (iCol = 0; iCol < nCol; iCol++){
			printf("\t%d\t", Matrix[iRow][iCol]);
		}
	}
}
void Giamdan(int x[100][100], int n, int m){
	int k = m*n;
	for(int i=0; i<k-1; i++){
		for(int j=i+1; j<k; j++){
			if(x[i/m][i%m]<x[j/m][j%m]){
				int temp  = x[i/m][i%m];
				x[i/m][i%m] = x[j/m][j%m];
				x[j/m][j%m] = temp;
			}
		}
	}
}
void Chuyenmatranthanhmang1chieu(int x[100][100], int n, int m, int y[10000]){
	int index = 0;
    int k=m*n;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			y[index]=x[i][j];
			index++;
		}
	}
    for(int i=0; i<k; i++){
        printf("%d  ",y[i]);
    }
}
void Xoanoc(int x[100][100], int n, int m){
    int z[100][100], p[1000];
    int t=0;
    int h1=0, h2=n-1, c1=0, c2=m-1;
    Giamdan(x,n,m);
    Chuyenmatranthanhmang1chieu(x,n,m,p);
    while(h1<=h2 && c1<=c2){
        for(int i=c2; i>=c1; i--){
            z[h1][i]=p[t];
            printf("\n %d    \n", z[h1][i]);
            t++;
        }
        h1++;
        for(int i=h1; i<=h2; i++){
            z[i][c1]=p[t];
            t++;
        }
        c1++;
        if(c1<=c2 && h1<=h2){
            for(int i=c1; i<=c2; i++){
                z[h2][i]=p[t];
                t++;
            }
            h2--;
        }
        if(h1<=h2 && c1<=c2){
            for(int i=h2; i>=h1; i--){
                z[i][c2]=p[t];
                t++; 
            }
        c2--;
        }
    }
    Xuatmatran(z,n,m);
}
void Dichxoayvong(int x[100][100], int n, int m){
    int k;
    printf("\nNhap vao so lan xoay: "); scanf("%d", &k);
    int temp[100];
    for(int e=1; e<=k; e++){
        for(int i=0; i<n; i++){
            temp[i]=x[i][m-1];
        }
        for(int j=m-1; j>=0; j--){
            for(int i=0; i<n; i++){
                x[i][j]=x[i][j-1];
            }
        }
        for(int i=0; i<n; i++){
            x[i][0]=temp[i];
        }
    }
    Xuatmatran(x,n,m);
}
void Docfile(sinhvien a[100], int &slsv){
    FILE *f;
    f=fopen("DSSV.txt", "rt");
    if(f==NULL){
        printf("Loi mo file!");
        exit(1);
    }
    fscanf(f, "%d", &slsv);
    for(int i=0; i<slsv; i++){
        fscanf(f, "\n%15s %30[^\n] %10s %7d %15s %35[^\n]", 
        &a[i].ms, &a[i].hoten, &a[i].gioitinh, &a[i].hedaotao, &a[i].khoahoc, &a[i].nganh);
        fscanf(f, "\n%d", &a[i].tonghocphan);
        for(int j=0; j<a[i].tonghocphan; j++){
            fscanf(f, "\n%15s %30[^\n] %17d %10d %17d %10f", 
            &a[i].hp[j].mhp, &a[i].hp[j].tenhp, &a[i].hp[j].sotc, &a[i].hp[j].loaihp, &a[i].hp[j].hk, &a[i].hp[j].diemtongket);
        }
    }
    fclose(f);
}
void Tstc(sinhvien sv[100], int slsv){
	for (int i=0;i<slsv;i++){
		for (int j=0;j<sv[i].tonghocphan;j++){
			if (sv[i].hp[j].diemtongket>=4){
				sv[i].tongtctl=sv[i].tongtctl+sv[i].hp[j].sotc;
				sv[i].hpdat+=1;
			}
		}
		printf("Tong so tin chi tich luy cua sinh vien thu %d la %d\n", i+1, sv[i].tongtctl);
	}
	for (int i=0;i<slsv;i++)
	{
		for (int j=0;j<sv[i].tonghocphan;j++)
		{
			sv[i].dtbtl=sv[i].hp[j].diemtongket+sv[i].dtbtl;
		}
		sv[i].dtbtl=(float)(sv[i].dtbtl)/sv[i].tonghocphan;
		printf("Diem trung binh tich luy cua sv thu %d la %f\n",i+1,sv[i].dtbtl);
	}
}
void Xuatthongtin(sinhvien a[100], int slsv){
    printf("\n--------------------------------------------------------------THONG TIN SINH VIEN-------------------------------------------------------------------------------\n");
    for(int i=0; i<slsv; i++){
        printf("\n%-10s %-15s %-30s %-10s %-10s %-15s %-30s %-17s %-17s",
        "STT", "MSSV", "Ho ten", "Gioi tinh", "He DT", "Khoa hoc", "Nganh",  "STC tich luy", "DTB tich luy");
        printf("\n%-10d %-15s %-30s %-10s %-10d %-15s %-30s %-17d %-17f",
        i+1, a[i].ms, a[i].hoten, a[i].gioitinh, a[i].hedaotao, a[i].khoahoc, a[i].nganh, a[i].tongtctl, a[i].dtbtl);
        printf("\n");
        printf("\n>>----- Danh Sach Hoc Phan: -----<< ");
        printf("\n");
        printf("\n\t%-10s %-15s %-30s %-17s %-10s %-17s %-10s", 
        "STT", "Ma HP", "Ten HP", "So TC", "Loai HP", "Hoc ky", "DTK");
        for(int j=0; j<a[i].tonghocphan; j++){
            printf("\n\t%-10d %-15s %-30s %-17d %-10d %-17d %-10f",
            j+1, a[i].hp[j].mhp, a[i].hp[j].tenhp, a[i].hp[j].sotc, a[i].hp[j].loaihp, a[i].hp[j].hk, a[i].hp[j].diemtongket);
        }
        printf("\n---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }
}
void Checkmssv(sinhvien sv[100], int slsv){
	char check[10];
	printf("Nhap ma so can tim: ");
    getchar();
	fgets(check, sizeof(check), stdin);
	for (int i=0;i<slsv;i++){
		sv[i].hpkdat=sv[i].tonghocphan-sv[i].hpdat;
        if (strncmp(sv[i].ms, check, strlen(sv[i].ms)) == 0){
			printf("%-10s %-15s %-30s %-15s %-30s %-15s %-15s %-15s %-15s ","STT", "MSSV", "HoTen", "Khoa Hoc", "Nganh Hoc", "SHP dat", "SHP k dat", "Tong STC", "DTBTL");
			for(int j=0; j<sv[i].tonghocphan; j++){
				sv[i].tongtinchi=sv[i].hp[j].sotc+sv[i].tongtinchi;
			}
            printf("\n%-10d %-15s %-30s %-15s %-30s %-15d %-15d %-15d %-15f", i+1, sv[i].ms, sv[i].hoten, sv[i].khoahoc, sv[i].nganh, sv[i].hpdat, sv[i].hpkdat, sv[i].tongtinchi, sv[i].dtbtl);
		}
	}
}
void Tbtlmaxmin(sinhvien sv[100], int slsv){
	float max=0;
	float min=999;
	for (int i=0; i<slsv; i++){
        if(max<sv[i].dtbtl){
            max=sv[i].dtbtl;
        }
        if(min>sv[i].dtbtl){
            min=sv[i].dtbtl;
        }
	}
	for (int i=0; i<slsv; i++){
		if(sv[i].dtbtl==max){
			printf("Sinh vien co so diem cao nhat \n");
			printf("Ma so %s\n",sv[i].ms);
			printf("Ten %s\n",sv[i].hoten);
			printf("Khoa hoc %s\n",sv[i].khoahoc);
			printf("Nganh %s\n",sv[i].nganh);
		}
		if (sv[i].dtbtl==min){
			printf("Sinh vien co so diem thap nhat \n");
			printf("Ma so %s\n",sv[i].ms);
			printf("Ten %s\n",sv[i].hoten);
			printf("Khoa hoc %s\n",sv[i].khoahoc);
			printf("Nganh %s\n",sv[i].nganh);
		}
	}
}
void Xoaxuongdong(char x[]){
	size_t len = strlen(x);
	if(x[len-1]=='\n'){
		x[len-1]='\0';
	}
}
void ThemSV(sinhvien sv[100], int &slsv){
	int pos=slsv;
	slsv=slsv+1;
    for(int i = pos; i < slsv; i++){
		printf("Nhap ms: ");
        fflush(stdin);
        fgets(sv[i].ms, sizeof(sv[i].ms), stdin);
		Xoaxuongdong(sv[i].ms);
        printf("\nNhap ho ten: ");
        fflush(stdin);
		fgets(sv[i].hoten, sizeof(sv[i].hoten), stdin);
        Xoaxuongdong(sv[i].hoten);
		printf("\nNhap gioi tinh: ");
		fflush(stdin);
        fgets(sv[i].gioitinh, sizeof(sv[i].gioitinh), stdin);
        Xoaxuongdong(sv[i].gioitinh);
		printf("\nNhap he dao tao: ");
		scanf("%d",&sv[i].hedaotao);
		printf("\nNhap khoa hoc: ");
        fflush(stdin);
		fgets(sv[i].khoahoc, sizeof(sv[i].khoahoc), stdin);
        Xoaxuongdong(sv[i].khoahoc);
		printf("\nNhap nganh hoc: ");
		fflush(stdin);
        fgets(sv[i].nganh, sizeof(sv[i].nganh), stdin);
        Xoaxuongdong(sv[i].nganh);
		printf("\nNhap vao so hoc phan cua sv thu %d da hoc:",i+1);
		scanf("%d",&sv[i].tonghocphan);
		for (int j=0;j<sv[i].tonghocphan;j++){
            printf("\nNhap ma hoc phan: ");
            fflush(stdin);
			fgets(sv[i].hp[j].mhp, sizeof(sv[i].hp[j].mhp), stdin);
            Xoaxuongdong(sv[i].hp[j].mhp);
            printf("\nNhap vao ten hoc phan: ");
            fflush(stdin);
			fgets(sv[i].hp[j].tenhp, sizeof(sv[i].hp[j].tenhp), stdin);
			Xoaxuongdong(sv[i].hp[j].tenhp);
            do{
				printf("\nNhap so tin chi ");
				scanf("%d",&sv[i].hp[j].sotc);
			}while (sv[i].hp[j].sotc>12 || sv[i].hp[j].sotc<1);
			printf("\nLoai hoc phan: ");
            scanf("%d",&sv[i].hp[j].loaihp);
			do{
				printf("\nNhap so hoc ki cua 1 hp: ");
				scanf("%d",&sv[i].hp[j].hk);
			}while (sv[i].hp[j].hk>12 || sv[i].hp[j].hk<1);
			do{
				printf("\nNhap diem tong ket cua hp: ");
				scanf("%f",&sv[i].hp[j].diemtongket);
			}while (sv[i].hp[j].diemtongket>10 || sv[i].hp[j].diemtongket<0);
		}
    }
}
void ThemHP(sinhvien sv[100], int slsv){
	char ma[10];
	char ten[35];
	int stc, loai, hk;
	float dtb;
    FILE *f;
    f=fopen("Hocphan.txt", "rt");
    if(f==NULL){
        printf("Loi mo file!");
        exit(1);
    }
    fscanf(f, "\n%15s\n%30[^\n]\n%17d\n%10d\n%17d\n%10f", 
    &ma, &ten, &stc, &loai, &hk, &dtb);
    fclose(f);
    for (int l=0; l<slsv; l++){	
	int pos=sv[l].tonghocphan;
	sv[l].tonghocphan=sv[l].tonghocphan+1;
        for (int k=pos; k<sv[l].tonghocphan; k++){
            strcpy(sv[l].hp[k].mhp, ma);
            strcpy(sv[l].hp[k].tenhp, ten);
            sv[l].hp[k].sotc=stc;
            sv[l].hp[k].loaihp=loai;
            sv[l].hp[k].hk=hk;
            sv[l].hp[k].diemtongket=dtb;
        }
    }
}
void xoaHP(sinhvien sv[100], int slsv){
    FILE *f;
    f=fopen("Maso.txt", "rt");
    if(f==NULL){
        printf("Loi mo file!");
        exit(1);
    }
	char check[10];
	fscanf(f, "%s", check);
    fclose(f);
	for (int i=0; i<slsv; i++){
		if (strncmp(sv[i].ms,check, strlen(sv[i].ms)) == 0){
     		for (int j=0; j<sv[i].tonghocphan; j++){
				if(sv[i].hp[j].diemtongket<4){
					for(int k = j; k < sv[i].tonghocphan - 1; k++){
						strcpy(sv[i].hp[j].mhp, sv[i].hp[j+1].mhp);
						strcpy(sv[i].hp[j].tenhp, sv[i].hp[j+1].tenhp);
						sv[i].hp[j].sotc = sv[i].hp[j+1].sotc;
						sv[i].hp[j].loaihp = sv[i].hp[j+1].loaihp;
						sv[i].hp[j].hk = sv[i].hp[j+1].hk;
						sv[i].hp[j].diemtongket = sv[i].hp[j+1].diemtongket;
					}
					--sv[i].tonghocphan;
				}
			}
		}
	}
}
void xoaSVHProng(sinhvien sv[100], int &slsv){
	for (int i=0; i<slsv; i++){
		if(sv[i].tonghocphan==0){
			for(int k = i; k < slsv - 1; k++){
				strcpy(sv[i].ms, sv[i+1].ms);
				strcpy(sv[i].hoten, sv[i+1].hoten);
				strcpy(sv[i].gioitinh, sv[i+1].gioitinh);
				sv[i].hedaotao = sv[i+1].hedaotao;
				strcpy(sv[i].khoahoc, sv[i+1].khoahoc);
				strcpy(sv[i].nganh, sv[i+1].nganh);
				sv[i].tongtinchi = sv[i+1].tongtinchi;
				sv[i].dtbtl = sv[i+1].dtbtl;
				sv[i].tonghocphan = sv[i+1].tonghocphan;
				sv[i].hpdat = sv[i+1].hpdat;
				sv[i].hpkdat = sv[i+1].hpkdat;
				sv[i].tongtctl = sv[i+1].tongtctl;
				for (int j=0;j<sv[i].tonghocphan;j++){
					strcpy(sv[i].hp[j].mhp, sv[i].hp[j+1].mhp);
					strcpy(sv[i].hp[j].tenhp, sv[i].hp[j+1].tenhp);
					sv[i].hp[j].sotc = sv[i+1].hp[j].sotc;
					sv[i].hp[j].loaihp = sv[i+1].hp[j].loaihp;
					sv[i].hp[j].hk = sv[i+1].hp[j].hk;
					sv[i].hp[j].diemtongket = sv[i+1].hp[j].diemtongket;
				}
			}
			--slsv;
		}
	}
}
void Tongtctonghp(sinhvien sv[100], int tongsv){
	int tonghocphan=0;
	int tongtinchi=0;
	for(int i=0;i < tongsv;i++){
		for(int j=0;j<sv[i].tonghocphan;j++){			
			sv[i].tongtinchi=sv[i].hp[j].sotc+sv[i].tongtinchi;
		}
		tongtinchi=sv[i].tongtinchi+tongtinchi;
        printf("\nTong tin chi cua sinh vien thu %d la: %d", i+1, sv[i].tongtinchi);
	    printf("\nTong hoc phan da hoc cua sinh vien thu %d la: %d", i+1, sv[i].tonghocphan);
		tonghocphan=0;
		tongtinchi=0;
    }
}
void Demsohs(sinhvien sv[100], int tongsv){
	int check=0;
	for (int i=0;i<tongsv;i++){
		for (int j=0;j<sv[i].tonghocphan;j++){
			if ((strncmp(sv[i].hp[j].tenhp,"nhap mon lap trinh", strlen("nhap mon lap trinh")) == 0 || strncmp(sv[i].hp[j].tenhp,"Nhap mon lap trinh", strlen("Nhap mon lap trinh")) == 0) && sv[i].hp[j].diemtongket>4){
				check++;
			}
		}
	}
	printf("Co tong cong %d sv dau\n",check);
	if(check>0){
		printf("\n%-10s %-15s %-30s %-10s %-10s %-17s %-17s",
        "STT", "MSSV", "Ho ten", "Gioi tinh", "He DT", "STC tich luy", "DTB tich luy");
        for (int i=0;i<tongsv;i++){
            for (int j=0;j<sv[i].tonghocphan;j++){
                if ((strncmp(sv[i].hp[j].tenhp,"nhap mon lap trinh", strlen("nhap mon lap trinh")) == 0 || strncmp(sv[i].hp[j].tenhp,"Nhap mon lap trinh", strlen("Nhap mon lap trinh")) == 0) && sv[i].hp[j].diemtongket>4){
                    printf("\n%-10d %-15s %-30s %-10s %-10d %-17d %-17f",
                    i+1, sv[i].ms, sv[i].hoten, sv[i].gioitinh, sv[i].hedaotao, sv[i].tongtctl, sv[i].dtbtl);
                }
            }
        }
    }
}
void Maxnmlt(sinhvien sv[100], int tongsv){
	float max=0;
	for (int i=0;i < tongsv;i++){
		for (int j=0;j<sv[i].tonghocphan;j++){
			if (strncmp(sv[i].hp[j].tenhp,"nhap mon lap trinh", strlen("nhap mon lap trinh")) == 0 || strncmp(sv[i].hp[j].tenhp,"Nhap mon lap trinh", strlen("Nhap mon lap trinh")) ==  0){
				if(max<sv[i].hp[j].diemtongket){
                    max = sv[i].hp[j].diemtongket;
                }
			}
		}
	}
    printf("\nDiem cao nhat la: %.2f", max);
    printf("\n%-10s %-15s %-30s %-10s %-10s %-17s %-17s",
    "STT", "MSSV", "Ho ten", "Gioi tinh", "He DT", "STC tich luy", "DTB tich luy");
	for (int i=0;i < tongsv;i++){
		for (int j=0;j<sv[i].tonghocphan;j++){
			if (strncmp(sv[i].hp[j].tenhp,"nhap mon lap trinh", strlen("nhap mon lap trinh")) == 0 || strncmp(sv[i].hp[j].tenhp,"Nhap mon lap trinh", strlen("Nhap mon lap trinh")) ==  0){
				if (sv[i].hp[j].diemtongket==max){
					printf("\n%-10d %-15s %-30s %-10s %-10d %-17d %-17f",
                    i+1, sv[i].ms, sv[i].hoten, sv[i].gioitinh, sv[i].hedaotao, sv[i].tongtctl, sv[i].dtbtl);
				}
			}
		}
	}
}
void sapXep(SV sv[100], int slsv){
	int i, j;
	for(i = 0; i < slsv - 1; ++i){
		for(j = i + 1; j < slsv; ++j){
			if(strcmp(sv[i].hoten, sv[j].hoten) > 0){
				SV s = sv[i];
				sv[i] = sv[j];
				sv[j] = s;
			}
			else if(strcmp(sv[i].hoten, sv[j].hoten) == 0){
				if(sv[i].dtbtl < sv[j].dtbtl){
					SV s = sv[i];
					sv[i] = sv[j];
					sv[j] = s;
				}
			}
		}
	}
}
void capNhat(SV sv[100], int slsv){
	int i, j;
	for(i = 0; i < slsv; ++i){
		if(strncmp(sv[i].khoahoc, "11DHTH", strlen("11DHTH")) == 0){
			for(j = 0; j < sv[i].tonghocphan; ++j){
				if(strncmp(sv[i].hp[j].tenhp, "co so du lieu", strlen("co so du lieu")) == 0 || strncmp(sv[i].hp[j].tenhp, "Co so du lieu", strlen("Co so du lieu")) == 0){
					sv[i].hp[j].sotc = 3;
				}
			}
		}
	}
}
void Menu(){
    printf("\n===================MENU===================\n");
    printf("\n1/ Nhap xuat ma tran A, chon nhap tu phim/random/filetext ");
    printf("\n2/ Tinh trung binh bien, cheo chinh, cheo phu cua ma tran A");
    printf("\n3/ Liet ke danh sach cua tung cot chua so thinh vuong cua ma tran A");
    printf("\n4/ Tim dong co trung binh nhan cac so nguyen to lon nhat cua ma tran A");
    printf("\n5/ Hoan vi hai cot bat ki cu ma tran A");
    printf("\n6/ Tu A xuat ra B thanh hai dong sao cho moi dong la chan tang dan le giam dan");
    printf("\n7/ Tao hai ma tran moi tu A voi C duong D am");
    printf("\n8/ Tao ma tran E co x dong y cot, dem so lan xuat hien cua E trong A");
    printf("\n9/ Tu A tao ma tran F dich phai xoay vong tu trai sang phai");
    printf("\n10/ Tu A tao ma tran I xoan oc giam dan nguoc chieu kim dong ho");
    printf("\n11/ Tinh so tin chi tich luy va diem trung binh tich luy cua sinh vien");
    printf("\n12/ Xuat thong tin cua cac sinh vien ra man hinh");
    printf("\n13/ Xuat thong tin ket qua hoc tap cua sinh vien khi biet ma so");
    printf("\n14/ Xuat thong tin sinh vien co diem trung binh tich luy cao nhat va thap nhat");
    printf("\n15/ Them thong tin cua 1 sinh vien vao danh sach");
    printf("\n16/ Them thong tin hoc phan da cho truoc vao danh sach hoc phan cua tat ca sinh vien");
    printf("\n17/ Xoa danh sach cac hoc phan co diem tich luy nho hon 4 cua sinh vien co ma so cho truoc");
    printf("\n18/ Xoa cac sinh vien chua co hoc phan nao");
    printf("\n19/ Tinh tong so tin chi va tong so hoc phan da hoc cua sinh vien");
    printf("\n20/ Dem so sinh vien da dau hoc phan co ten 'Nhap mon lap trinh' va xuat thong tin cua cac sinh vien nay");
    printf("\n21/ Cho biet diem tong ket cao nhat cua hoc phan 'Nhap mon lap trinh' va thong tin sinh vien co diem cao nhat");
    printf("\n22/ Sap xep danh sach sinh vien tang dan theo ten, cung ten thi xep theo trung binh tich luy giam dan roi xuat ra man hinh");
    printf("\n23/ Cap nhat so tinh chi 'Co so du lieu' cua sinh vien khoa '11DHTH' tu 2 thanh 3 tin chi");
    printf("\n=========================================");
} 
int main(){
    int chon;
    struct sinhvien sv[100];
    int slsv;
    Docfile(sv,slsv);
    do{
        Menu();
        printf("\nChon bai (chon 0 de thoat): "); scanf("%d", &chon);
        switch(chon){
            case 1:
                int bai;
                printf("\n1/ Nhap tu ban phim");
                printf("\n2/ Nhap random");
                printf("\n3/ Nhap tu file text");
                printf("\nChon yeu cau: "); scanf("%d", &bai);
                switch(bai){
                    case 1:
                        Nhapmatran(a,n,m);
                        Xuatmatran(a,n,m);
                        break;
                    case 2:
                        Nhapmatranrandom(a,n,m);
                        printf("\n");
                        Xuatmatran(a,n,m);
                        break;
                    case 3:
                        Nhapmangtufile(a,n,m);
                        break;
                }
                break;
            case 2:
                Tbcbien(a,n,m);
                Tbcheochinh(a,n,m);
                Tbcheophu(a,n,m);
                break;
            case 3:
                Lietkethinhvuong(a,n,m);
                break;
            case 4:
                MaxTrungBinhNhanNguyenTo(a,n,m);
                break;
            case 5:
                Doigiatrihaicot(a,n);
                Xuatmatran(a,n,m);
                break;
            case 6:
                Sapxepchantanglegiam(a,n,m);
                Xuatmatran(a,n,m);
                break;
            case 7:
                Xuathaimatran(a,n,m);
                break;
            case 8:
                fflush(stdin);
                printf("\nNhap vao so dong cua ma tran E: ");
                scanf("%d", &Arow);
                printf("\nNhap vao so cot cua ma tran E: ");
                scanf("%d", &Acol);
                ImportData(E, Arow, Acol);
                PrintMatrix(E, Arow, Acol);
                res = AsubnetBmatrix(E, a, Arow, Acol,n,m);
                if (res)
                printf("\nMa tran con da nhap xuat hien %d lan trong ma tran da nhap", res);
                else
                    printf("\nMa tran con da nhap khong phai la ma tran con");
                break;
            case 9:
                Dichxoayvong(a,n,m);
                break;
            case 10:
                Xoanoc(a,n,m);
                break;
            case 11:
                Tstc(sv, slsv);
                break;
            case 12:
                Xuatthongtin(sv, slsv);
                break;
            case 13: 
                Checkmssv(sv, slsv);
                break;
            case 14:
                Tbtlmaxmin(sv, slsv);
                break;
            case 15:
                ThemSV(sv, slsv);
                break;
            case 16:
                ThemHP(sv,slsv);
                break;
            case 17:
                xoaHP(sv, slsv);
                break;
            case 18:
                xoaSVHProng(sv, slsv);
                break;
            case 19:
                Tongtctonghp(sv, slsv);
                break;
            case 20:
                Demsohs(sv, slsv);
                break;
            case 21:
                Maxnmlt(sv, slsv);
                break;
            case 22:
                sapXep(sv, slsv);
                break;
            case 23:
                capNhat(sv, slsv);
                break;

        }
    }while (chon!=0);
}