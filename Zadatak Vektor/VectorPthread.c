#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>


/*
Uslovi koji moraju da se provere kada korisnik unosi podatke vezane za broj niti i broj clanova;
1.n>=0;
2.m>=0;
3.n/m ---> ostatak =0;
Inace izbacuje iz programa..
*/
void unos(int *vec, int n){
    int input;
    for(int i = 0;i<n;i++){
        printf("Clan %d: ", i);
        scanf("%d", &input);
        vec[i] = input;
    }
}

// funkcija koja ce da sabere dva vektora ali samo jedna nit radi
void sum(int n, int *v1, int *v2, int *res){
    for(int i = 0; i< n;i++){
        res[i] += v1[i] + v2[i];
    }
}
typedef struct 
{
    int start;
    int end;
    int *v1;
    int *v2;
    int *res;

}Podaci;

// a ovo je funckija koju ce da koriste m niti;
void* sumOfVectors(void* arg){

    // da bi sabrali dva vektora moramo da imamo inf koje cemo da 
    // prosledimo kada kreiramo niti u main-u
    // a da bi imali sve potrebne inf koristicemo strukuru podataka.
    Podaci *podaci = (Podaci*) arg; // pretvaram pokazivac koji je void u Podaci*
    for(int i = podaci->start;i<podaci->end;i++){
        podaci->res[i] = podaci->v1[i] + podaci->v2[i];
    }
    return NULL;

}

int main(){
    int n;
    int m;
    printf("Unesite dimenzije vektor:\n");
    scanf("%d",&n);

    if(n<=0){
        printf("Dimenzije vektora moraju biti vece od 0!");
        return 1;
    }

    printf("Unesite broj niti: \n");
    scanf("%d", &m);

    if(m<=0){
        printf("Broj niti mora biti veci od 0!");
        return 2;
    }

    if(n%m != 0){
        printf("Broj clanova vektora (n) mora biti deljiv brojem niti (m) !");
        return 1;
    }
    int *v1 = malloc(n*sizeof(int));
    int *v2 = malloc(n*sizeof(int));
    int *res = malloc(n*sizeof(int));
    printf("------------------------------------\n");
    // sada cemo da unesemo clanove vektora
    printf("Unesite clanove prvog vektora:\n");
    unos(v1,n);

    printf("\n");
    printf("Unesite clanove drugog vektora:\n");
    
    unos(v2,n);
    
    printf("------------------------------------\n");

    // ovde cemo da izmerimo vreme za delovanje jedne niti
    clock_t vreme_start = clock();
    sum(n, v1,v2, res);
    clock_t vreme_end = clock();
    double ukupno_vreme_jedna_nit = (double)(vreme_end- vreme_start)/CLOCKS_PER_SEC;
    printf("-------JEDNA NIT-------\n");
    printf("\n");
    printf("Zbir ova dva vektora: \n");
    printf("\n");
    for(int i=0; i< n; i++){
        printf("%d ", res[i]);
    }
    printf("\n");
    printf("\nUkupno potroseno vreme za jednu nit: %.7f sekundi\n",ukupno_vreme_jedna_nit);
    printf("\n");
    

    for(int i = 0; i< n;i++){
        res[i] = 0;
    }// resetovali smo rezultat , da li je to dobro da se radi ovako?



    // sada cemo da kreiramo m niti
    pthread_t threads[m];
    // kolilo niiti imamo toliko moramo da imamo posebnih podataka;
    Podaci podaci[m];

    clock_t start_multi = clock();
    int deo = n/m;

    // broj clanova delimo sa brojem niti??
    // a ne m/n ???
    for(int i = 0; i< m;i++){

        // sada je potrebno da se dodele podaci svakoj niti koju kreireami
        // da bi znala sta da sabira
        podaci[i].start = i*deo;
        podaci[i].end = (i+1)*deo;
        podaci[i].v1 = v1;
        podaci[i].v2 = v2;
        podaci[i].res = res;

        if(pthread_create(&threads[i],NULL,sumOfVectors,&podaci[i])!=0){
            perror("Greska..");
            return 3;
        }
    }

    // ovde cekamo niti da zavrse
    for(int i =0; i< m;i++){
        if(pthread_join(threads[i], NULL)!=0){
            perror("greska..");
            return 4;
        }
    }
    clock_t end_multi = clock();
    double ukupno_vreme = (double)(end_multi - start_multi)/CLOCKS_PER_SEC;
    
    // i na kraju stampamo rezultat i koliko je vreemena potroseno
    
    printf("-------VISE NITI-------\n");
    printf("Rezultat sabiranja sa vise niti: \n");
    printf("\n");
    for(int i = 0; i<n;i++){
        printf("%d ", res[i]);
    }
    printf("\n");
    printf("Ukupno vreme izvrsavanje sa vise niti je: %.7f sekundi", ukupno_vreme);
    printf("\n");
    printf("\n *****************Zakljucak***************\n");
    if(ukupno_vreme>ukupno_vreme_jedna_nit){
        printf("Izgleda da je sabiranje brze odradila jedna nit! Zadatak nije bio tezak pa je vise vremena potroseno na kreiranje niti..");
    }else{
        printf("Ipak se kreiranje vise niti isplatilo...");
    }
    free(v1);
    free(v2);
    free(res);
    return 0;

}