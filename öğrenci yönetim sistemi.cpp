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
cout<<"Hoþgeldiniz lütfen yapmak istediðiniz iþlemin numarasýný girin"<<endl;
cout<<"1- Öðrenci Ekleme"<<endl;
cout<<"2- Öðrenci Listeleme"<<endl;
cout<<"3- Öðrenci Arama"<<endl;
cout<<"4- Öðrenci Silme"<<endl;
cout<<"5- Öðrenci Düzenleme"<<endl;
cout<<"Seçim:";
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

	cout<<"Öðrenci No Girin\n";
	cin>> ogr.ogr_no;
	cout << "Ögrenci Ad Girin" << endl;
	cin>> ogr.ad;
	cout << "Ögrenci Soyad Girin" << endl;
	cin>> ogr.soyad;
	cout << "Ögrenci Cinsiyet Girin (E/K)" << endl;
	cin>>ogr.cinsiyet;
	cout<<"Öðrenci Doðum Tarihi GÜN Girin"<<endl;
	cin>>dogum_tarihi.gun;
	cout<<"Öðrenci Doðum Tarihi AY Girin"<<endl;
	cin>>dogum_tarihi.ay;
	cout<<"Öðrenci Doðum Tarihi YIL Girin"<<endl;
	cin>>dogum_tarihi.yil;

	ogr.dogum_tarihi = dogum_tarihi;
    yaz.write((char*)&ogr, sizeof(Ogrenci));
	
	
	
cout<<"Yeni öðrenci eklemek ister misin?(E/H)"<<endl;
cin>>ekleme;	
}while(ekleme=='E'|| ekleme=='e');

yaz.close();	
}


void OgrenciListele()
{
ifstream oku("veri.dat",ios::binary);
if(!oku)
{
cout<<"Dosya Açýlamadý"<<endl;
return;	
}

while(oku.read((char*)&ogr,sizeof(Ogrenci)))
{
		cout << "Öðrenci No: " << ogr.ogr_no << endl;
        cout << "Ad: " << ogr.ad << endl;
        cout << "Soyad: " << ogr.soyad << endl;
        cout << "Cinsiyet: " << ogr.cinsiyet << endl;
        cout << "Doðum Tarihi: " << ogr.dogum_tarihi.gun << "/";
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
cout<<"Dosya Açýlamadý"<<endl;
return;	
}

char aranan_no[6];
bool bulundu=false;	
cout<<"Aradýðýnýz Öðrencinin numarasýný girin"<<endl;
cin>>aranan_no;

while(oku.read((char*)&ogr,sizeof(Ogrenci)))
{
if(strcmp(ogr.ogr_no,aranan_no)==0)	
{
cout << "Öðrenci Bulundu!" << endl;
cout << "Öðrenci No: " << ogr.ogr_no << endl;
cout << "Ad: " << ogr.ad << endl;
cout << "Soyad: " << ogr.soyad << endl;
cout << "Cinsiyet: " << ogr.cinsiyet << endl;
cout << "Doðum Tarihi: " << ogr.dogum_tarihi.gun << "/";
cout<< ogr.dogum_tarihi.ay << "/" << ogr.dogum_tarihi.yil << endl;
bulundu = true;// Öðrnecinin bulunduðunu belirliyor
break;

}


	
  }	
if(!bulundu)
{
cout<<"Öðrenci Bulunamadý"<<endl;}
oku.close();
	
	
}

void OgrenciSil()
{
ifstream oku("veri.dat",ios::binary);

if(!oku)
{
cout<<"Dosya Açýlamadý"<<endl;	
return;
}

ofstream gecici("gecici.dat",ios::binary );
 
if(!gecici) 
{
	cout<<"Geçici Dosya Açýlamadý"<<endl;
	return;
}

char silinecek_no[6];
bool silindi=false;

cout<<"Silmek istediðiniz öðrencinin numarasýný girin"<<endl;
cin>> silinecek_no;





	
while(oku.read((char*)&ogr,sizeof(Ogrenci)))	
{
	if(strcmp(ogr.ogr_no,silinecek_no)!=0)//eðer silinecek noya eþit deðilse geçiciye göndereceðiz
	{
		gecici.write((char*)&ogr,sizeof(Ogrenci));
		}	
	else//silmek isteðiz noya eþitse
	{
		silindi=true;
	}
}
	if(silindi)
	{
	cout<<"Öðrenci baþarýyla silindi!"<<endl;
	}
	else
	{
		cout<<"Öðrenci bulunamadý!"<<endl;
	}
	oku.close();
	gecici.close();
	
	remove("veri.dat");//orijinal dosyayý sildik
	rename("gecici.dat","veri.dat");// gecici dosyasýný yeniden adlandýrdýk
}
//----------------------------------------------------------------------------------------

void OgrenciDuzenle()
{
	
ifstream oku("veri.dat",ios::binary);
if(!oku)
{
	cout<<"Dosya Açýlamadý"<<endl;
}

ofstream duzenlenen("duzenlenen.dat",ios::binary);
if(!duzenlenen)
{cout<<"Dosya Açýlamadý"<<endl;
}

char duzenlenecek_no[6];
bool duzenle=false;

cout<<"Düzenlemek istediðiniz öðrencinin öðrenci nosunu girin"<<endl;
cin>>duzenlenecek_no;

while(oku.read((char*)&ogr,sizeof(Ogrenci)))
{
if(strcmp(ogr.ogr_no,duzenlenecek_no)==0)//doðruysa 0 çýkar
{
cout << "Öðrenci bulundu!" << endl;
cout << "Öðrenci No: " << ogr.ogr_no << endl;
cout << "Ad: " << ogr.ad << endl;
cout << "Soyad: " << ogr.soyad << endl;
cout << "Cinsiyet: " << ogr.cinsiyet << endl;
cout << "Doðum Tarihi: " << ogr.dogum_tarihi.gun << "/";
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
cout << "Yeni Doðum Tarihi (Gün): ";
cin >> ogr.dogum_tarihi.gun;
cout << "Yeni Doðum Tarihi (Ay): ";
cin >> ogr.dogum_tarihi.ay;           
cout << "Yeni Doðum Tarihi (Yýl): ";
cin >> ogr.dogum_tarihi.yil;

duzenlenen.write((char*)&ogr,sizeof(Ogrenci));
duzenle=true;
}

else
duzenlenen.write((char*)&ogr,sizeof(Ogrenci));//eðer düzenlenecek olan kiþi deðilse duzenlenen dosyasýna yazýyoruz
}

if(duzenle)
{
cout<<"Düzenleme Baþarýlý"<<endl;
}	
else
cout<<"Öðrenci Bulunamadý"<<endl;

oku.close();
duzenlenen.close();

remove("veri.dat");
rename("duzenlenen.dat","veri.dat");

	
}





