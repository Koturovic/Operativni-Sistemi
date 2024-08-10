package karte;
//Тура игре представља један круг игре у којем учествују играчи. Играчи играју један за
//другим, узимајући карте из шпила или одигравајући карту из своје руке.
public class Tura implements Runnable {
    // objekat igraca
    // objekat spila
    // i moramo da znamo da li igrac uzima iz spila ili igra sa svojim kartama
    private final Igrac igrac;
    private final Spil spil;
    private final boolean uzima;

    public Tura(Igrac igrac, Spil spil, boolean uzima) {
        this.igrac = igrac;
        this.spil = spil;
        this.uzima = uzima;
    }

    @Override
    public void run() {

        // ovde se odvoja nit koja ce da pokrece igru
        // dakle igrac ili igra sa svojim kartama ili izvlaci iz spila nove karte
        try {
            if(uzima) {
                igrac.uzimaizSpila(spil);
            }else{
                igrac.odigraj(spil);
            }
        }catch (InterruptedException e){
            Thread.currentThread().interrupt();
        }

    }
}
