package karte;
import java.util.Collection;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

//Шпил карата представља колекцију карата са стандардним шпилом од 52 карте. Може се
//створити празан шпил или се може напунити стандардним картама. Може се из шпила
//извући карта, а такође може се и додати карта у шпил. У случају покушаја извлачења карте
//из празног шпила или додавања карте у пун шпил, нит извршиоца радње се привремено
//блокира. Такође, може се саставити текстуални опис шпила који садржи све карте
//тренутно у шпилу
public class Spil {

    // kolekcija karata od 52 karte (broj_karata = 52 to je fiksno)
    private List<Karta> karte; //!!! ako ne bude radilo napravicu podrazumevani konstruktor i ovde ucitati arrayList!!!
    private final int broj_karta = 52;
    // konstruktor za stvaranje praznog spila
    public Spil(){
        this.karte = new ArrayList<>();                            // ||||||
    }

    // kreiramo spil standardnim kartama:
    public synchronized void standard(){
        String[] znakovi  ={"Karo", "Srce", "Tref", "Pik"};
            // sad svkom broju dodajemo po znak
            for(String znak: znakovi){
                for(int i = 1; i< 14; i++){
                    karte.add(new Karta(i, znak));   // i-> vrednost, znak -> znak
                }
            }   // sada su u nekom normalnom redosledu. Kako da ih promesam?
        Collections.shuffle(karte); // ovde ce ih promesati funkcija iz javine biblioteke?
    }
    // moze da se desi greska pri dodavanju karte u spil:?
    public synchronized void dodajKartu(Karta karta) throws  InterruptedException{
        // ukoliko je spil pun moramo da cekamo!
        while(karte.size()>= broj_karta){
            wait();
        }
        // kada se oslobodi mesto dodajemo kartu
        karte.add(karta);
        // i nakon toga obavestimo sve da smo izvrsili update
        notifyAll();
    }
    // sada je potrebno implementirati metodu za uzimanje karte iz spila
    // moze da se desi greska
    public synchronized Karta uzmiKartu() throws InterruptedException{
        // ukoliko je spil prazan potrebno je privremeno bloirati nit
        while(karte.isEmpty()){
            wait();
        }
        // ako spil gledam kao niz uzecu kartu koja se nalazi na kraju niza
        // pristupam indexu tako sto izracunam velicinu niza i oduzmem 1;
        Karta uzetaKarta = karte.remove(karte.size()-1);

        // obavestimo sve da se desio updaate
        notifyAll();
        //uzmemo kartu
        return uzetaKarta;
    }

    // potrebno je dodati teks opis u kontekstu koje sve karte se nalaze u spilu:


    @Override
    public String toString() {
        StringBuilder s =new StringBuilder();
        // prolazimo kroz niz(SPIL):
        for(Karta karta: karte){
            s.append(karta).append("\n");

        }
        // stand vratimo s
        return s.toString();
    }
    public int brojKarata(){
        return karte.size();
    }
}
