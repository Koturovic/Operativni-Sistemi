#include<stdio.h>
#include<stdlib.h>
// funkcija koja ce da sabere vektore
void sum(int n, int *v1, int *v2, int *res){
    for(int i = 0; i< n;i++){
        res[i] += v1[i] + v2[i];
    }
}



int main(){


     int n;
     // prvo moramo da pitamo korisnika koje nam je dimenzije vektor
     printf("Koje je su dimenzije vektori?\n ");
     scanf("%d" , &n);

     //printf("Dimenzije vektora su: %d ",n);

    // moramo da alociramo niz koji ce da predstavlja vektor i resultat koje je iste velicine
    // kao i vektor
    int *v1 =malloc(n*sizeof(int));
    int *v2 = malloc(n*sizeof(int));
    int *res = malloc(n*sizeof(int));


    //ucitavamo jedan pa drugi;
    printf("Unesite clanove prvog vektora:\n");
    for(int i = 0; i<n;i++){
        scanf("%d", &v1[i]);
    }


    printf("Unesite clanove drugog vektora:\n");
    for(int i = 0; i<n;i++){
        scanf("%d", &v2[i]);
    }
    sum(n, v1, v2, res);

    printf("Zbir ova dva vektora: \n");
    for(int i=0; i< n; i++){
        printf("%d ", res[i]);
    }

    free(v1);
    free(v2);
    free(res);
    return 0;
}