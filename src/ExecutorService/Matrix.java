package ExecutorService;

import java.util.Random;
import java.util.concurrent.Callable;

public class Matrix implements Callable<Boolean> {
    private static final int SIZE = 10;
    private final int[][] matrix;
    private final String tName;
    public Matrix(String tName){
        this.tName = tName;
        this.matrix = new int[SIZE][SIZE]; // pravimo matrixu dimenzije 10x10;


    }

    // ovo je overajdovana metoda call koja ce da vrati true ukoliko se desi da u zbiru dijagonale matrice bude vrednost
    // > od 300
    @Override
    public Boolean call() {
        // prvo se stvara mattrica
        // pa racunamo zbir dijagonale
        // i na kraju ispisujemo ime niti , matricu i zbir dijagonale
        // ukoliko se desi da je zbir dijagonale >300 automacki se obustavlja dalji rad!

        ucitajMatricu();
        int zbir = izracunajDijagonalu();
        System.out.println("Nit: " + Thread.currentThread().getName());// hocu da znam pool i broj niti
        //System.out.println("Nit: " + tName);
        stampajMatricu();
        System.out.println("Zbir dijagonale: " + zbir);

        return zbir>300;
    }

    private int izracunajDijagonalu(){
        int n = matrix.length;
        int sum = 0;
        for(int i = 0; i< n; i++){
            sum+=matrix[i][i];

        }
        return sum;
    }

    private void ucitajMatricu(){
        Random random = new Random();
        for(int i = 0; i< SIZE;i++){
            for(int j = 0; j< SIZE;j++){
                matrix[i][j] = random.nextInt(101);
            }
            // stand ucitavanje matrice sa random brojevima od 0 do 100
        }
    }
    private void stampajMatricu(){
        for(int i = 0;i<SIZE; i++){
            for(int j = 0; j<SIZE;j++){
                System.out.print(matrix[i][j] + " ");
            }
            System.out.println();
        }
    }
}
