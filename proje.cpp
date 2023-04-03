#include <fstream>//dosya sınıfı için.
#include <iostream>//cout ve cin için.
#include <string.h>//strcmp için.
#include <iomanip>//setw için.
using namespace std;//her cout ve cin yazdığımızda std:: koymamak için.
struct Ucus {//ucus.dat dosyasından alınan verileri tutmak ve kolayca okuyabilmek için.
	int ucusNo;
	char kalkisYeri[21];
	char varisYeri[21];
	int kalkisSaati;
	int kalkisDakikasi;
	int koltukKapasite;
	int bosKoltuk;
	int biletFiyat;
};
struct Biletler {//biletler.txt dosyasından alınan verileri tutmak için.
	int ucusNo;
	char TC[12];
	float fiyat;
};

//prototipler.
int loop();
int BirNumara();
int IkiNumara();
int UcNumara();
int DortNumara();
int BesNumara();
int AltiNumara();
int YediNumara();
int SekizNumara();
int DokuzNumara();

int main() {
	while(true)//kolayca programı tekrar çalıştırabilmek için böyle bir yöntem izledik.
		loop();
}
int loop() {//esas main fonksiyonumuz burada.
	int islem;

	//islem seçilmesi için tanıtım kısmı.
	cout<<"*** havayolunun admin paneline hosgeldiniz"<<endl;
	cout<<"islemler: "<<endl;
	cout<<"1- Ucus Numarasi girerek sorgulayin."<<endl;
	cout<<"2- Ucus Numarasi girerek ayrintili bilgi sorgulayin."<<endl;
	cout<<"3- Kalkis yeri girilerek ucus sorgulayin."<<endl;
	cout<<"4- Koltuk doluluk oraninin %50'nin altinda oldugu ucuslara bakin."<<endl;
	cout<<"5- TC kimlik numaranizi girerek biletlerinizi listeleyin."<<endl;
	cout<<"6- Yeni bir ucus ekleyin."<<endl;
	cout<<"7- Bir ucusun kaydini silin."<<endl;
	cout<<"8- Bir ucusun kalkis zamanini degistirin."<<endl;
	cout<<"9- Bir ucusa iliskin bilet satin."<<endl;
	cout<<"(-1)- Cikin."<<endl;
	do {
		cout<<"\nisleminizi seciniz: ";
		cin>>islem;

		switch(islem) {//secilen islemi islemek için switch case kullandık.
			case 1:
				BirNumara();
				break;
			case 2:
				IkiNumara();
				break;
			case 3:
				UcNumara();
				break;
			case 4:
				DortNumara();
				break;
			case 5:
				BesNumara();
				break;
			case 6:
				AltiNumara();
				break;
			case 7:
				YediNumara();
				break;
			case 8:
				SekizNumara();
				break;
			case 9:
				DokuzNumara();
				break;
			case -1:
				exit(1);
				break;
			default:
				cout<<"Yanlis islem sectiniz. Tekrar Deneyiniz.";
				break;
		}
	} while((islem<1)||(islem>9));
}

int BirNumara() { //1- Ucus Numarasi girerek sorgulama
	FILE *dosya=fopen("ucus.dat","rb+");//dosya okuma
	int ucusNoSorgu;
	Ucus ucus;

	if(!dosya) {//eğer dosya okunmazsa hata ver.
		cout<<"dosya acilamadi!!";
		exit(1);
	}

	cout<< "1 ile 1000 arasindaki ucus numaranizi giriniz: ";
	cin>>ucusNoSorgu;
	while((ucusNoSorgu<1)||(ucusNoSorgu>1000)) {
		cout<<"Lutfen 1 ile 1000 arasinda deger giriniz: ";//ucus numarasının doğru girildiğini sorgulama.
		cin>>ucusNoSorgu;
	}
	fseek(dosya,(ucusNoSorgu-1)*sizeof(struct Ucus),SEEK_SET);//direk adresleme yöntemi için uçuş numarasıyla anahtarlama yapıldı.
	fread(&ucus,sizeof(ucus),1,dosya);//dosyadan alınan veri doğrudan ucus yapısına okundu.
	if(ucus.ucusNo==0) {//ucus numarası var mı yok mu kontrol edildi.
		cout<<"Ucus bulunamadi!!"<<endl;
		int donusKarari;
		cout<<"Ana menuye donmek icin lutfen 1'e uygulamadan cikmak icin baska bir tusa basiniz...: ";
		cin>>donusKarari;
		if(donusKarari==1) {
			cout<<"Ana menuye donuyorsunuz...\n"<<endl;
			return 1;
		} else {
			cout<<"Uygulamadan cikiyorsunuz...";
			exit(1);
		}
	} else {//varsa formatlı şekilde yazıldı.
		cout << "Ucus No \t Kalkis Yeri \t Varis Yeri \t Zamani \t Kapasite \t Bos Koltuk \t Doluluk" << endl;
		cout << "------- \t ----------- \t ---------- \t ------ \t -------- \t ---------- \t -------" << endl;
		cout << ucus.ucusNo << setw(20) << ucus.kalkisYeri << setw(18) << ucus.varisYeri << setw(11);
		if(ucus.kalkisDakikasi<10) {
			cout <<ucus.kalkisSaati << ":0" << ucus.kalkisDakikasi << setw(14) << ucus.koltukKapasite << setw(21);
		} else {
			cout << ucus.kalkisSaati << ":" << ucus.kalkisDakikasi << setw(14) << ucus.koltukKapasite << setw(21);
		}
		cout << ucus.bosKoltuk << setw(12)<< ((ucus.koltukKapasite - ucus.bosKoltuk) / (float)ucus.koltukKapasite) * 100 << "%" << endl;
	}
	fclose(dosya);
	int donusKarari;
	cout<<"Ana menuye donmek icin lutfen 1'e uygulamadan cikmak icin baska bir tusa basiniz...: ";
	cin>>donusKarari;
	if(donusKarari==1) {
		cout<<"Ana menuye donuyorsunuz...\n"<<endl;
		return 1;
	} else {
		cout<<"Uygulamadan cikiyorsunuz...";
		exit(1);
	}
}

int IkiNumara() { //2- Ucus Numarasi girerek ayrintili bilgi sorgulama
	FILE *dosya=fopen("ucus.dat","rb+");//dosyaları açtık
	FILE *biletDosya=fopen("bilet.txt","rb+");
	int ucusNoSorgu, biletSayisi=0;
	float toplamKazanc=0, ortalamaFiyat;//gerekli değişkenler tanımlandı
	Ucus ucus;
	Biletler bilet;
	if(!dosya) {
		cout<<"dosya acilamadi!!";
		exit(1);
	}

	cout<< "1 ile 1000 arasindaki ucus numaranizi giriniz: ";
	cin>>ucusNoSorgu;
	while((ucusNoSorgu<1)||(ucusNoSorgu>1000)) {
		cout<<"Lutfen 1 ile 1000 arasinda deger giriniz: ";
		cin>>ucusNoSorgu;
	}

	fseek(dosya,(ucusNoSorgu-1)*sizeof(ucus),SEEK_SET);
	fread(&ucus,sizeof(ucus),1,dosya);
	if(ucus.ucusNo==0) {
		cout<<"Ucus bulunamadi!!"<<endl;
		int donusKarari;
		cout<<"Ana menuye donmek icin lutfen 1'e uygulamadan cikmak icin baska bir tusa basiniz...: ";
		cin>>donusKarari;
		if(donusKarari==1) {
			cout<<"Ana menuye donuyorsunuz...\n"<<endl;
			return 1;
		} else {
			cout<<"Uygulamadan cikiyorsunuz...";
			exit(1);
		}
	} else {
		cout << "Ucus No \t Kalkis Yeri \t Varis Yeri \t Zamani \t Kapasite \t Bos Koltuk \t Doluluk" << endl;
		cout << "------- \t ----------- \t ---------- \t ------ \t -------- \t ---------- \t -------" << endl;
		cout << ucus.ucusNo << setw(20) << ucus.kalkisYeri << setw(18) << ucus.varisYeri << setw(11);
		if(ucus.kalkisDakikasi<10) {
			cout <<ucus.kalkisSaati << ":0" << ucus.kalkisDakikasi << setw(14) << ucus.koltukKapasite << setw(21);
		} else {
			cout << ucus.kalkisSaati << ":" << ucus.kalkisDakikasi << setw(14) << ucus.koltukKapasite << setw(21);
		}
		cout << ucus.bosKoltuk << setw(12)<< ((ucus.koltukKapasite - ucus.bosKoltuk) / (float)ucus.koltukKapasite) * 100 << "%" << endl;
	}

	cout << "--------------------------------------" << endl;
	cout << "SATILAN BILETLER" << endl;
	cout << "TC Kimlik No\t\tFiyati" << endl;
	cout << "-------------\t\t------" << endl;
//satılan biletler formatlı olarak yazıldı.
	fseek(biletDosya, 0, SEEK_SET);
	while(!feof(biletDosya)) {
		fscanf(biletDosya, "%d %s %f", &bilet.ucusNo, &bilet.TC, &bilet.fiyat);
		if(bilet.ucusNo == ucusNoSorgu) {
			cout <<bilet.TC << "\t\t" << bilet.fiyat << endl;
			biletSayisi++;
			toplamKazanc += bilet.fiyat;
		}
	}

	if(biletSayisi > 0) {
		ortalamaFiyat = toplamKazanc / biletSayisi;
		cout << "--------------------------------------" << endl;
		cout << "TOPLAM SATILAN BILET SAYISI: " << biletSayisi << endl;
		cout << "TOPLAM KAZANC: " << toplamKazanc << endl;
		cout << "ORTALAMA BILET FIYATI: " << ortalamaFiyat << endl;
	} else {
		cout << "Bu ucusa iliskin satilan bilet bulunmamaktadir!" << endl;
	}

	fclose(dosya);
	fclose(biletDosya);
	int donusKarari;
	cout<<"Ana menuye donmek icin lutfen 1'e uygulamadan cikmak icin baska bir tusa basiniz...: ";
	cin>>donusKarari;
	if(donusKarari==1) {
		cout<<"Ana menuye donuyorsunuz...\n"<<endl;
		return 1;
	} else {
		cout<<"Uygulamadan cikiyorsunuz...";
		exit(1);
	}
}

int UcNumara() { //3- Kalkis yeri girilerek ucus sorgulama
	FILE *dosya = fopen("ucus.dat", "rb+");
	Ucus ucus;
	bool ucusBulundu = false;
	char kontrolKalkisYeri[21];

	if (!dosya) {
		cout << "Dosya acilamadi!!" << endl;//dosya açılabilmiş mi açılamamış mı kontrol edildi.
		exit(1);
	}

	cout << "Kalkis yeri giriniz: ";
	cin >> kontrolKalkisYeri;
	int n=0;
	while(fread(&ucus,sizeof(Ucus),1,dosya)==1) {
		if (strcmp(strlwr(ucus.kalkisYeri),strlwr(kontrolKalkisYeri)) == 0) {//karşılaştırmadan önce strlwr kullandık böylece kullanıcı küçük harf de kullansa büyük harf de kullansa fark etmeyecekti.
			if(n==0) {
				cout << "Ucus No \t Kalkis Yeri \t Varis Yeri \t Zamani \t Kapasite \t Bos Koltuk \t Doluluk" << endl;
				cout << "------- \t ----------- \t ---------- \t ------ \t -------- \t ---------- \t -------" << endl;
				n++;
			}
			cout << ucus.ucusNo << setw(20) << ucus.kalkisYeri << setw(18) << ucus.varisYeri << setw(11);
			if(ucus.kalkisDakikasi<10) {
				cout <<ucus.kalkisSaati << ":0" << ucus.kalkisDakikasi << setw(14) << ucus.koltukKapasite << setw(21);
			} else {
				cout << ucus.kalkisSaati << ":" << ucus.kalkisDakikasi << setw(14) << ucus.koltukKapasite << setw(21);
			}
			cout << ucus.bosKoltuk << setw(12)<< ((ucus.koltukKapasite - ucus.bosKoltuk) / (float)ucus.koltukKapasite) * 100 << "%" << endl;
			ucusBulundu = true;

		}
	}
	if (!ucusBulundu) {
		cout << "Aradiginiz kalkis yerine sahip ucus bulunamadi." << endl;
	}
	fclose(dosya);

	int donusKarari;
	cout<<"Ana menuye donmek icin lutfen 1'e uygulamadan cikmak icin baska bir tusa basiniz...: ";
	cin>>donusKarari;
	if(donusKarari==1) {
		cout<<"Ana menuye donuyorsunuz...\n"<<endl;
		return 1;
	} else {
		cout<<"Uygulamadan cikiyorsunuz...";
		exit(1);
	}


}

int DortNumara() { //4- Koltuk doluluk oraninin %50den fazla oldugu ucuslar
	Ucus ucuslar[1000];
	int n = 0;

	FILE* dosya = fopen("ucus.dat", "rb");
	if (dosya == NULL) {
		cerr << "Dosya acilamadi!" << endl;
		exit(1);
	}
	Ucus ucus;
	while (fread(&ucus, sizeof(Ucus), 1, dosya) == 1) {
		if (ucus.ucusNo != 0 && ((ucus.koltukKapasite - ucus.bosKoltuk) / (float)ucus.koltukKapasite) * 100 < 50) {//doluluk hesaplandı ve uçuşun olduğuna emin olundu.
			ucuslar[n++] = ucus;//dosyadan okunanlar diziye kaydedildi.
		}
	}
	fclose(dosya);//burada onceden okutup diziye akatardıgımız icin dosyayı kapattık.

	for (int i = 0; i < n - 1; i++) {//bubble sort yapıldı. böylece sıralı bir dizi elde ettik.
		for (int j = 0; j < n - i - 1; j++) {
			float doluluk1 = (ucuslar[j].koltukKapasite - ucuslar[j].bosKoltuk) / (float)ucuslar[j].koltukKapasite;
			float doluluk2 = (ucuslar[j+1].koltukKapasite - ucuslar[j+1].bosKoltuk) / (float)ucuslar[j+1].koltukKapasite;
			if (doluluk1 > doluluk2) {
				Ucus sonuc = ucuslar[j];
				ucuslar[j] = ucuslar[j+1];
				ucuslar[j+1] = sonuc;
			} else if (doluluk1 == doluluk2 && ucuslar[j].bosKoltuk < ucuslar[j+1].bosKoltuk) {
				Ucus sonuc = ucuslar[j];
				ucuslar[j] = ucuslar[j+1];
				ucuslar[j+1] = sonuc;
			}
		}
	}
//formatlı bir şekilde yazdırdık.
	cout << "Ucus No \t Kalkis Yeri \t Varis Yeri \t Zamani \t Kapasite \t Bos Koltuk \t Doluluk" << endl;
	cout << "------- \t ----------- \t ---------- \t ------ \t -------- \t ---------- \t -------" << endl;
	for (int i = 0; i < n; i++) {
		Ucus ucus = ucuslar[i];
		cout << ucus.ucusNo << setw(20) << ucus.kalkisYeri << setw(18) << ucus.varisYeri << setw(11);
		if(ucus.kalkisDakikasi<10) {
			cout <<ucus.kalkisSaati << ":0" << ucus.kalkisDakikasi << setw(14) << ucus.koltukKapasite << setw(21);
		} else {
			cout << ucus.kalkisSaati << ":" << ucus.kalkisDakikasi << setw(14) << ucus.koltukKapasite << setw(21);
		}
		cout << ucus.bosKoltuk << setw(12)<<fixed<<setprecision(2)<< ((ucus.koltukKapasite - ucus.bosKoltuk) / (float)ucus.koltukKapasite) * 100 << "%" << endl;
	}
	int donusKarari;
	cout<<"Ana menuye donmek icin lutfen 1'e uygulamadan cikmak icin baska bir tusa basiniz...: ";
	cin>>donusKarari;
	if(donusKarari==1) {
		cout<<"Ana menuye donuyorsunuz...\n"<<endl;
		return 1;
	} else {
		cout<<"Uygulamadan cikiyorsunuz...";
		exit(1);
	}
}
int BesNumara() {
	FILE *biletDosya=fopen("bilet.txt","r");
	char kullaniciTCKN[20];
	Biletler bilet;

	if(biletDosya==NULL) {
		cout<<"Bilet dosyasinde problem var!!!";
		exit(1);
	}
	cout << "Lutfen TC Kimlik Numaranizi Giriniz: ";
	cin >> kullaniciTCKN;

	cout << "SATIN ALDIGI BILETLER" << endl;
	cout << "Ucus No \t Kalkis Yeri \t Varis Yeri \t Zamani \t Kapasite \t Bos Koltuk \t Doluluk" << endl;
	cout << "------- \t ----------- \t ---------- \t ------ \t -------- \t ---------- \t -------" << endl;

	while(!feof(biletDosya)) {
		fscanf(biletDosya, "%d %s %f", &bilet.ucusNo, &bilet.TC, &bilet.fiyat);
		if(strcmp(bilet.TC, kullaniciTCKN) == 0) {

			FILE *dosya=fopen("ucus.dat","rb+");
			Ucus ucus;

			fseek(dosya, (bilet.ucusNo-1)*sizeof(Ucus), SEEK_SET);
			fread(&ucus, sizeof(Ucus), 1, dosya);

			cout << ucus.ucusNo << setw(20) << ucus.kalkisYeri << setw(18) << ucus.varisYeri << setw(11);
			if(ucus.kalkisDakikasi<10) {
				cout <<ucus.kalkisSaati << ":0" << ucus.kalkisDakikasi << setw(14) << ucus.koltukKapasite << setw(21);
			} else {
				cout << ucus.kalkisSaati << ":" << ucus.kalkisDakikasi << setw(14) << ucus.koltukKapasite << setw(21);
			}
			cout << ucus.bosKoltuk << setw(12)<< ((ucus.koltukKapasite - ucus.bosKoltuk) / (float)ucus.koltukKapasite) * 100 << "%" << endl;

			fclose(dosya);
		}
	}
	fclose(biletDosya);
	int donusKarari;
	cout<<"Ana menuye donmek icin lutfen 1'e uygulamadan cikmak icin baska bir tusa basiniz...: ";
	cin>>donusKarari;
	if(donusKarari==1) {
		cout<<"Ana menuye donuyorsunuz...\n"<<endl;
		return 1;
	} else {
		cout<<"Uygulamadan cikiyorsunuz...";
		exit(1);
	}
}

int AltiNumara() { //6- Yeni bir ucus ekleyin
	FILE *dosya=fopen("ucus.dat","rb+");
	int ucusNoSorgulama;
	Ucus ucus;

	if(!dosya) {
		cout<<"Dosya acilamadi!!";
		exit(1);
	}

	cout<< "Lutfen bir ucus numarasi giriniz : ";
	cin>>ucusNoSorgulama;
	fseek(dosya,(ucusNoSorgulama-1)*sizeof(struct Ucus),SEEK_SET);//uçuş numarasını anahtar olarak kullanarak adrese gittik.
	fread(&ucus,sizeof(ucus),1,dosya);

	if(ucus.ucusNo != 0) {
		cout<<"Bu numarali ucus zaten kayitli!"<<endl;//eğer böyle bir kayıt varsa uyarı verdik.
		fclose(dosya);
		int donusKarari;
		cout<<"Ana menuye donmek icin lutfen 1'e uygulamadan cikmak icin baska bir tusa basiniz...: ";
		cin>>donusKarari;
		if(donusKarari==1) {
			cout<<"Ana menuye donuyorsunuz...\n"<<endl;
			return 1;
		} else {
			cout<<"Uygulamadan cikiyorsunuz...";
			exit(1);
		}
	} else {
		ucus.ucusNo = ucusNoSorgulama;
//değerleri aldık.
		cout<< "Kalkis Yeri: ";
		cin>>ucus.kalkisYeri;

		cout<< "Varis Yeri: ";
		cin>>ucus.varisYeri;

		cout<< "Kalkis Saati: ";
		cin>>ucus.kalkisSaati;

		cout<< "Kalkis Dakikasi: ";
		cin>>ucus.kalkisDakikasi;

		cout<< "Koltuk Kapasitesi: ";
		cin>>ucus.koltukKapasite;

		cout<< "Bilet Fiyat: ";
		cin>>ucus.biletFiyat;

		ucus.bosKoltuk = ucus.koltukKapasite;

		fseek(dosya,(ucusNoSorgulama-1)*sizeof(struct Ucus),SEEK_SET);
		fwrite(&ucus,sizeof(ucus),1,dosya);

		cout<<"Yeni ucus kaydi basariyla eklendi."<<endl;
	}
	fclose(dosya);
	int donusKarari;
	cout<<"Ana menuye donmek icin lutfen 1'e uygulamadan cikmak icin baska bir tusa basiniz...: ";
	cin>>donusKarari;
	if(donusKarari==1) {
		cout<<"Ana menuye donuyorsunuz...\n"<<endl;
		return 1;
	} else {
		cout<<"Uygulamadan cikiyorsunuz...";
		exit(1);
	}
}

int YediNumara() { //7- Bir ucusun kaydini silin
	FILE *dosya=fopen("ucus.dat","rb+");
	int ucusNoSorgulama;
	char karar;
	Ucus ucus;
	Biletler bilet;

	if(!dosya) {
		cout<<"dosya acilamadi!!";
		int donusKarari;
		cout<<"Ana menuye donmek icin lutfen 1'e uygulamadan cikmak icin baska bir tusa basiniz...: ";
		cin>>donusKarari;
		if(donusKarari==1) {
			cout<<"Ana menuye donuyorsunuz...\n"<<endl;
			fclose(dosya);
			return 1;

		} else {
			cout<<"Uygulamadan cikiyorsunuz...";
			fclose(dosya);
			exit(1);
		}
		fclose(dosya);
	}

	cout<< "1 ile 1000 arasindaki ucus numaranizi giriniz: ";
	do {
		cout<<"Lutfen 1 ile 1000 arasinda deger giriniz: ";
		cin>>ucusNoSorgulama;
	} while((ucusNoSorgulama<1)||(ucusNoSorgulama>1000));

	fseek(dosya,(ucusNoSorgulama-1)*sizeof(struct Ucus),SEEK_SET);
	fread(&ucus,sizeof(ucus),1,dosya);
	if(ucus.ucusNo==0) {
		cout<<"Boyle bir ucus yok!!"<<endl;//silinecek uçuş var mı yok mu kontrol ettik.
		fclose(dosya);
		int donusKarari;
		cout<<"Ana menuye donmek icin lutfen 1'e uygulamadan cikmak icin baska bir tusa basiniz...: ";
		cin>>donusKarari;
		if(donusKarari==1) {
			cout<<"Ana menuye donuyorsunuz...\n"<<endl;
			return 1;
		} else {
			cout<<"Uygulamadan cikiyorsunuz...";
			exit(1);
		}
		
	}
	cout<<"Silmek istediginiz ucus:"<<endl;
	cout << "Ucus No \t Kalkis Yeri \t Varis Yeri \t Zamani \t Kapasite \t Bos Koltuk \t Doluluk" << endl;
	cout << "------- \t ----------- \t ---------- \t ------ \t -------- \t ---------- \t -------" << endl;
	cout << ucus.ucusNo << setw(20) << ucus.kalkisYeri << setw(18) << ucus.varisYeri << setw(11);
	if(ucus.kalkisDakikasi<10) {
		cout <<ucus.kalkisSaati << ":0" << ucus.kalkisDakikasi << setw(14) << ucus.koltukKapasite << setw(21);
	} else {
		cout << ucus.kalkisSaati << ":" << ucus.kalkisDakikasi << setw(14) << ucus.koltukKapasite << setw(21);
	}
	cout << ucus.bosKoltuk << setw(12)<< ((ucus.koltukKapasite - ucus.bosKoltuk) / (float)ucus.koltukKapasite) * 100 << "%" << endl;
	cout<< "Dogru ise 1'e basin. Degilse baska bir sey tuslayin.";//silinecek uçuşdan emin olduk.
	cin>>karar;
	if(karar=='1') {
		FILE *dosya2=fopen("bilet.txt","a+");

		if(dosya2==NULL) {
			cout<<"Biletler dosyasında problem var."<<endl;
			exit(1);
		}
		int gecisiucus;
		char gecisitc[12];
		float gecisifiyat;
		while(!feof(dosya2)) {

			fscanf(dosya2,"%d",&gecisiucus);//ucus.dat tan sildiğimiz ucusa ait bilet.xt dosyasında kayıt varsa sildik.
			if(gecisiucus==ucusNoSorgulama) {
				cout<<"bayrak 1.."<<endl;
				fprintf(dosya2,"00000000000");
				fprintf(dosya2,"00.00");
			}
			fscanf(dosya2,"%s",&gecisitc);
			fscanf(dosya2,"%f",&gecisifiyat);
		}
		fclose(dosya2);
		Ucus ucus = {0,"","",0,0,0,0,0};//boş koyıt yaptı.
		fseek(dosya,(ucusNoSorgulama-1)*sizeof(struct Ucus),SEEK_SET);
		fwrite(&ucus,sizeof(ucus),1,dosya);
		fread(&ucus,sizeof(ucus),1,dosya);//kayıt başarılı mı kontrol ettik.
		if(ucus.ucusNo==0) {
			cout<<"Basariyla silindi..."<<endl;
			int donusKarari;
			cout<<"Ana menuye donmek icin lutfen 1'e uygulamadan cikmak icin baska bir tusa basiniz...: ";
			cin>>donusKarari;
			if(donusKarari==1) {
				cout<<"Ana menuye donuyorsunuz...\n"<<endl;
				fclose(dosya);
				return 1;
			} else {
				cout<<"Uygulamadan cikiyorsunuz...";
				fclose(dosya);
				exit(1);
			}
		}
	} else {
		int donusKarari;
		cout<<"Ana menuye donmek icin lutfen 1'e uygulamadan cikmak icin baska bir tusa basiniz...: ";
		cin>>donusKarari;
		if(donusKarari==1) {
			cout<<"Ana menuye donuyorsunuz...\n"<<endl;
			return 1;
		} else {
			cout<<"Uygulamadan cikiyorsunuz...";
			exit(1);
		}
		fclose(dosya);

	}
	fclose(dosya);
}

int SekizNumara() { //8- bir ucusun kalkis zamanini degistirin
	FILE *dosya = fopen("ucus.dat","rb+");
	int ucusNoSorgu;
	Ucus ucus;

	if(!dosya) {
		cout<<"dosya acilamadi!!";
		exit(1);
	}

	cout << "1 ile 1000 arasindaki ucus numaranizi giriniz: ";
	cin >> ucusNoSorgu;

	while(ucusNoSorgu < 1 || ucusNoSorgu > 1000) {
		cout << "Lutfen 1 ile 1000 arasinda deger giriniz: ";
		cin >> ucusNoSorgu;
	}

	fseek(dosya, (ucusNoSorgu - 1) * sizeof(struct Ucus), SEEK_SET);
	fread(&ucus, sizeof(ucus), 1, dosya);

	if(ucus.ucusNo == 0) {
		cout << "Ucus bulunamadi!!" << endl;
	} else {
		cout << "Ucus No \t Kalkis Yeri \t Varis Yeri \t Zamani \t Kapasite \t Bos Koltuk \t Doluluk" << endl;
		cout << "------- \t ----------- \t ---------- \t ------ \t -------- \t ---------- \t -------" << endl;
		cout << ucus.ucusNo << setw(20) << ucus.kalkisYeri << setw(18) << ucus.varisYeri << setw(11);
		if(ucus.kalkisDakikasi<10) {
			cout <<ucus.kalkisSaati << ":0" << ucus.kalkisDakikasi << setw(14) << ucus.koltukKapasite << setw(21);
		} else {
			cout << ucus.kalkisSaati << ":" << ucus.kalkisDakikasi << setw(14) << ucus.koltukKapasite << setw(21);
		}
		cout << ucus.bosKoltuk << setw(12)<< ((ucus.koltukKapasite - ucus.bosKoltuk) / (float)ucus.koltukKapasite) * 100 << "%" << endl;

		cout << "Yeni saat ve dakikayi lutfen giriniz : ";
		cin >> ucus.kalkisSaati >> ucus.kalkisDakikasi;

		fseek(dosya, (ucusNoSorgu - 1) * sizeof(struct Ucus), SEEK_SET);
		fwrite(&ucus, sizeof(ucus), 1, dosya);
		cout << "Ucus bilgileri guncellendi!" << endl;
	}

	fclose(dosya);
}

int DokuzNumara() { //9- bir ucusa iliskin bilet satin
	int ucusNoSorgu;
	char TC[12];
	char karar;
	int karar2;
	FILE *dosya=fopen("bilet.txt","a+");
	FILE *dosya2= fopen("ucus.dat","rb+");
	Ucus ucus;
	int tekrar;

	cout<< "1 ile 1000 arasindaki ucus numaranizi giriniz: ";
	cin>>ucusNoSorgu;
	while((ucusNoSorgu<1)||(ucusNoSorgu>1000)) {
		cout<<"Lutfen 1 ile 1000 arasinda deger giriniz: ";
		cin>>ucusNoSorgu;
	}
	fseek(dosya2,(ucusNoSorgu-1)*sizeof(Ucus),SEEK_SET);
	fread(&ucus,sizeof(ucus),1,dosya2);
	if(ucus.ucusNo==0) {
		cout<<"Ucus bulunamadi..."<<endl;
		do {

			cout<<"tekrar denemek icin 1'e ana menuye donmek icin 0'a basiniz... : ";
			cin>>karar2;
			if(karar2==1)
				DokuzNumara();
			else if(karar2==0) {
				cout<<"Ana menuye yonlendiriliyorsunuz... "<<endl;
				return 1;
			} else
				cout<<"Hatali secim yaptiniz... tekrar deneyiniz.";
		} while((karar2!=1)||(karar2!=0));

	} else {
		float doluluk=((ucus.koltukKapasite - ucus.bosKoltuk) / (float)ucus.koltukKapasite) * 100;
		if(doluluk==100) {
			cout<<"Uzgunum. bu ucusta yer yok..."<<endl;
			cout<<"Ana menuye yonlendiriliyorsunuz... "<<endl;
			return 1;
			fclose(dosya);
			fclose(dosya2);
		}
		cout<<"Yolcunun TC kimlik numarasini giriniz: ";
		do {
			cout<<"Lutfen 11 haneli deger giriniz: ";
			cin>>TC;
		} while(strlen(TC) != 11) ;

		float fiyat;
		doluluk=100-doluluk;
		for(int i=0; i<10; i++) {
			if((doluluk<=(i+1)*10)&&(doluluk>(i)*10)) {//
				fiyat=(float)70*(float)((float)1+((10-i)/10));
				break;
			}
		}
		cout<<"Fiyat = "<<fixed << setprecision(2) <<fiyat<<" . Onayliyor musunuz? ";
		char karar;
		tekrar=1;
		do {
			cout<<"(e/h): ";
			cin>>karar;
			if((karar=='e')||(karar=='E')) {

				fprintf(dosya, "%d %s %.2f\n", ucusNoSorgu, TC, fiyat);

				ucus.bosKoltuk--;
				fwrite(&ucus,sizeof(ucus),1,dosya2);
				cout<<"kaydedildi. ana menuye yonlendiriliyorsunuz..."<<endl;
				return 1;

			} else if((karar=='h')||(karar=='H')) {
				cout<<"Ana menuye yonlendiriliyorsunuz..."<<endl;
				return 1;
				tekrar=0;
				fclose(dosya);
				fclose(dosya2);
			} else
				cout<<"yanlis girdiniz. tekrar deneyiniz."<<endl;
		} while(tekrar==1);

		fclose(dosya);
		fclose(dosya2);
	}
}
