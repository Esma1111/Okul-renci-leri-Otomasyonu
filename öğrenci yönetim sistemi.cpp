#include<iostream>
#include<fstream>
#include<conio.h>
#include<string.h>
#include<locale.h>
using namespace std;

struct Dogum_Tarihi
{
int gun;
int ay;
int yil;	
};
struct Ogrenci
{
	char ad[80];
	char soyad[80];
	char ogr_no[6];
	char cinsiyet;
	Dogum_Tarihi dogum_tarihi;
};
void OgrenciAra();
void OgrenciListele();
void OgrenciSil();
void OgrenciDuzenle();
void OgrenciEkle();
int main()
{
	setlocale(LC_ALL,"Turkish");
int secim;
cout<<"Ho�geldiniz l�tfen yapmak istedi�iniz i�lemin numaras�n� girin"<<endl;
cout<<"1- ��renci Ekleme"<<endl;
cout<<"2- ��renci Listeleme"<<endl;
cout<<"3- ��renci Arama"<<endl;
cout<<"4- ��renci Silme"<<endl;
cout<<"5- ��renci D�zenleme"<<endl;
cout<<"Se�im:";
cin>> secim;

switch(secim)
{
case 1:
{
OgrenciEkle();
break;	
	}	
	
case 2:
{
OgrenciListele();	
break;
	}	
		
case 3:
{
	OgrenciAra();
	break;
	}	
	
case 4:
{
	OgrenciSil();
	break;
	}	
		
case 5:
{
	OgrenciDuzenle();
	break;
	}	
	}	
	
}

Ogrenci ogr;
Dogum_Tarihi dogum_tarihi;
void OgrenciEkle()
{
	
ofstream yaz("veri.dat",ios::binary |ios::app);
int adet=0;
char ekleme;

do{

	cout<<"��renci No Girin\n";
	cin>> ogr.ogr_no;
	cout << "�grenci Ad Girin" << endl;
	cin>> ogr.ad;
	cout << "�grenci Soyad Girin" << endl;
	cin>> ogr.soyad;
	cout << "�grenci Cinsiyet Girin (E/K)" << endl;
	cin>>ogr.cinsiyet;
	cout<<"��renci Do�um Tarihi G�N Girin"<<endl;
	cin>>dogum_tarihi.gun;
	cout<<"��renci Do�um Tarihi AY Girin"<<endl;
	cin>>dogum_tarihi.ay;
	cout<<"��renci Do�um Tarihi YIL Girin"<<endl;
	cin>>dogum_tarihi.yil;

	ogr.dogum_tarihi = dogum_tarihi;
    yaz.write((char*)&ogr, sizeof(Ogrenci));
	
	
	
cout<<"Yeni ��renci eklemek ister misin?(E/H)"<<endl;
cin>>ekleme;	
}while(ekleme=='E'|| ekleme=='e');

yaz.close();	
}


void OgrenciListele()
{
ifstream oku("veri.dat",ios::binary);
if(!oku)
{
cout<<"Dosya A��lamad�"<<endl;
return;	
}

while(oku.read((char*)&ogr,sizeof(Ogrenci)))
{
		cout << "��renci No: " << ogr.ogr_no << endl;
        cout << "Ad: " << ogr.ad << endl;
        cout << "Soyad: " << ogr.soyad << endl;
        cout << "Cinsiyet: " << ogr.cinsiyet << endl;
        cout << "Do�um Tarihi: " << ogr.dogum_tarihi.gun << "/";
        cout << ogr.dogum_tarihi.ay << "/" << ogr.dogum_tarihi.yil << endl;
        cout << "---------------------------------" << endl;	
	

}
oku.close();	
	
}

void OgrenciAra()
{

ifstream oku("veri.dat",ios::binary);
if(!oku)
{
cout<<"Dosya A��lamad�"<<endl;
return;	
}

char aranan_no[6];
bool bulundu=false;	
cout<<"Arad���n�z ��rencinin numaras�n� girin"<<endl;
cin>>aranan_no;

while(oku.read((char*)&ogr,sizeof(Ogrenci)))
{
if(strcmp(ogr.ogr_no,aranan_no)==0)	
{
cout << "��renci Bulundu!" << endl;
cout << "��renci No: " << ogr.ogr_no << endl;
cout << "Ad: " << ogr.ad << endl;
cout << "Soyad: " << ogr.soyad << endl;
cout << "Cinsiyet: " << ogr.cinsiyet << endl;
cout << "Do�um Tarihi: " << ogr.dogum_tarihi.gun << "/";
cout<< ogr.dogum_tarihi.ay << "/" << ogr.dogum_tarihi.yil << endl;
bulundu = true;// ��rnecinin bulundu�unu belirliyor
break;

}


	
  }	
if(!bulundu)
{
cout<<"��renci Bulunamad�"<<endl;}
oku.close();
	
	
}

void OgrenciSil()
{
ifstream oku("veri.dat",ios::binary);

if(!oku)
{
cout<<"Dosya A��lamad�"<<endl;	
return;
}

ofstream gecici("gecici.dat",ios::binary );
 
if(!gecici) 
{
	cout<<"Ge�ici Dosya A��lamad�"<<endl;
	return;
}

char silinecek_no[6];
bool silindi=false;

cout<<"Silmek istedi�iniz ��rencinin numaras�n� girin"<<endl;
cin>> silinecek_no;





	
while(oku.read((char*)&ogr,sizeof(Ogrenci)))	
{
	if(strcmp(ogr.ogr_no,silinecek_no)!=0)//e�er silinecek noya e�it de�ilse ge�iciye g�nderece�iz
	{
		gecici.write((char*)&ogr,sizeof(Ogrenci));
		}	
	else//silmek iste�iz noya e�itse
	{
		silindi=true;
	}
}
	if(silindi)
	{
	cout<<"��renci ba�ar�yla silindi!"<<endl;
	}
	else
	{
		cout<<"��renci bulunamad�!"<<endl;
	}
	oku.close();
	gecici.close();
	
	remove("veri.dat");//orijinal dosyay� sildik
	rename("gecici.dat","veri.dat");// gecici dosyas�n� yeniden adland�rd�k
}
//----------------------------------------------------------------------------------------

void OgrenciDuzenle()
{
	
ifstream oku("veri.dat",ios::binary);
if(!oku)
{
	cout<<"Dosya A��lamad�"<<endl;
}

ofstream duzenlenen("duzenlenen.dat",ios::binary);
if(!duzenlenen)
{cout<<"Dosya A��lamad�"<<endl;
}

char duzenlenecek_no[6];
bool duzenle=false;

cout<<"D�zenlemek istedi�iniz ��rencinin ��renci nosunu girin"<<endl;
cin>>duzenlenecek_no;

while(oku.read((char*)&ogr,sizeof(Ogrenci)))
{
if(strcmp(ogr.ogr_no,duzenlenecek_no)==0)//do�ruysa 0 ��kar
{
cout << "��renci bulundu!" << endl;
cout << "��renci No: " << ogr.ogr_no << endl;
cout << "Ad: " << ogr.ad << endl;
cout << "Soyad: " << ogr.soyad << endl;
cout << "Cinsiyet: " << ogr.cinsiyet << endl;
cout << "Do�um Tarihi: " << ogr.dogum_tarihi.gun << "/";
cout<< ogr.dogum_tarihi.ay << "/" << ogr.dogum_tarihi.yil << endl;	
cout<<"----------------------------------------"<<endl;
cout << "Yeni Ad: ";
cin >> ogr.ad;
cout << "Yeni Soyad: ";
cin >> ogr.soyad;
cout << "Yeni No: ";
cin >> ogr.ogr_no;
cout << "Yeni Cinsiyet (E/K): ";
cin >> ogr.cinsiyet;
cout << "Yeni Do�um Tarihi (G�n): ";
cin >> ogr.dogum_tarihi.gun;
cout << "Yeni Do�um Tarihi (Ay): ";
cin >> ogr.dogum_tarihi.ay;           
cout << "Yeni Do�um Tarihi (Y�l): ";
cin >> ogr.dogum_tarihi.yil;

duzenlenen.write((char*)&ogr,sizeof(Ogrenci));
duzenle=true;
}

else
duzenlenen.write((char*)&ogr,sizeof(Ogrenci));//e�er d�zenlenecek olan ki�i de�ilse duzenlenen dosyas�na yaz�yoruz
}

if(duzenle)
{
cout<<"D�zenleme Ba�ar�l�"<<endl;
}	
else
cout<<"��renci Bulunamad�"<<endl;

oku.close();
duzenlenen.close();

remove("veri.dat");
rename("duzenlenen.dat","veri.dat");

	
}





