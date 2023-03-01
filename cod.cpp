#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef struct {
	int musteri_no=-1;
	char ad[20],soyad[20];
}Musteri;

Musteri veri_liste[10];

int hash_tablo[10];

float total_steps=0,how_word=0;

FILE *file;

//###############################################################################################

int hash_fonk( Musteri temp){
	int indis=(3*temp.musteri_no+2)%10;
	total_steps++;
	int i=0;
	while(hash_tablo[indis]!=-1){
		total_steps++;
		i++;
		indis=((3*temp.musteri_no+2)+i*(7*temp.musteri_no+2))%10;
	}
	//hash tablo int dizisinin hesaplanmýþ indisine müþteri no atýlýr
	hash_tablo[indis]=temp.musteri_no;
	
	return indis;
}

//###############################################################################################

preparation(){
	
	for(int i=0; i<10; i++){
		hash_tablo[i]=-1;
	}
	
	if((file=fopen("veri.txt","r+a"))==NULL) printf("dosya acilamadi");
	Musteri temp;
	
	while(!feof(file)){
		fscanf(file,"%d %s %s",&temp.musteri_no,temp.ad,temp.soyad);
		
		if(how_word==10) {
			printf("Toplam kayit sayisi 10. Liste dolu");
			return 0;
		}
		
		int indis=hash_fonk(temp);
		
		//veri liste Musteri listesinin hesaplanmýþ indisine müþteri bilgileri atýlýr
		veri_liste[indis].musteri_no=temp.musteri_no;
		strcpy(veri_liste[indis].ad,temp.ad);
		strcpy(veri_liste[indis].soyad,temp.soyad);
		how_word++;
		
	}
	
}

//#############################################################################################

search(){
	int numara=0;
	printf("Aramak istediginiz numarayý giriniz\n");
	scanf("%d",&numara);
	
	int kontrol[10];
	int i=0,kon=0;
	int indis=((3*numara+2)+i*(7*numara+2))%10;
	
	while(hash_tablo[indis]!=numara){
		i++;
		indis=((3*numara+2)+i*(7*numara+2))%10;
		//printf("%d",indis);
		if(indis>=0){
			kontrol[indis]=1;
		}
		kon=0;
		for(int a=0; a<=9; a++){
			if(kontrol[a]==1) kon++;
		}
		if(kon>=10 || i>=total_steps){
			printf("\naradiginiz numara bulunamadi..\n");
			return 0;
		}
	}
	
	printf("\nnumara bulundu..\n%d-%s %s\n %d adimda bulundu\n\n",indis,veri_liste[indis].ad,veri_liste[indis].soyad,i+1);
}

//###########################################################################################

printlist(){
	
	for(int i=0;i<10; i++){
		if(hash_tablo[i]!=-1){
			printf("%d. %d %s %s\n",i,veri_liste[i].musteri_no,veri_liste[i].ad,veri_liste[i].soyad);
		}
		else{
			printf("%d.  (BOS)\n",i);
		}
	}
}

//#############################################################################################

addperson(){
	if(how_word>=10) {
		printf("\n!!!\nToplam kayit sayisi 10. Liste dolu\n!!!\n");
		return 0;
	}
	else{
		Musteri temp;
		printf("\neklenecek numarayi giriniz: \n"); scanf("%d",&temp.musteri_no);
		printf("ismi giriniz: \n"); scanf("%s",temp.ad);
		printf("soyadi giriniz: \n"); scanf("%s",temp.soyad);
		
		int indis=hash_fonk(temp);
		
		//veri liste Musteri listesinin hesaplanmýþ indisine müþteri bilgileri atýlýr
		veri_liste[indis].musteri_no=temp.musteri_no;
		strcpy(veri_liste[indis].ad,temp.ad);
		strcpy(veri_liste[indis].soyad,temp.soyad);
		how_word++;
		
	}
	
	
}


int main() {
	
	for(int i=0; i<10; i++){
		hash_tablo[i]=-1;
	}
	
	preparation();
	int i=0,exitt=0;
	while(1){
		if(exitt==1){
			system("cls");
			printf("\nSistemden basariyla cikis yapildi...\niyi gunler...");
			return 0;
		}
		printf( "\n######################\n"   
		"Listeyi goruntulemek icin: (1), Yeni kayid icin: (2), Arama yapmak icin: (3), Ortalama adim icin: (4), Cikis icin(5)\n\n");
    	scanf("%d",&i);
		switch (i){
			case 1:
				system("cls");
				printlist();
				break;
			case 2:
				addperson();
				system("cls");
				if(how_word>10) {
					printf("\n!!!\nToplam kayit sayisi 10. Liste dolu\n!!!\n");
					break;
				}
				printlist();
				break;
			case 3:
				search();
				break;
			case 4:
				system("cls");
				printf("Ortalama adim: %0.2f\n",total_steps/how_word);
				break;
			case 5:
				exitt=1;
				break;
			default:
				printf("Lutfen gecerli bir sayi giriniz!!!");
				break;				
		}
	}		
	
	
	
	
	return 0;
}





