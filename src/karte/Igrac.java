package karte;

import java.util.ArrayList;
import java.util.List;

//Играч има име и листу карата које има у руци. Може се створити играч без карата у руци
//или који држи одређене карте. Играч може узети карту из шпила и додати је у своју руку,
//или може одиграти одређену карту из руке. Такође, може се саставити текстуални опис
//играча који наводи име играча и све карте у његовој руци.
public class Igrac {

    // ime
    private final String ime;
    private final List<Karta> ruka;

    // konstruktor bez karata u ruci

    // treba mi jedan geter za ime:
    public String getIme(){
        return ime;
    }
    public Igrac(String ime){
        this.ime=ime;
        this.ruka = new ArrayList<>();
    }
    // konstruktor sa prosledjenim argumentimaL
    public Igrac(String ime, List<Karta> ruka) {
        this.ime = ime;
        this.ruka = ruka;
    }

    // igrac uzima iz spila kartu i stavlja je u svoju ruku;
    public synchronized void uzimaizSpila(Spil spil) throws InterruptedException{
        ruka.add(spil.uzmiKartu());
    }

    public  synchronized void odigraj(Spil spil) throws InterruptedException{
        // ukoliko je ruka prazna on ne moze da igra
        if(!ruka.isEmpty()){
            Karta karta = ruka.remove(ruka.size()-1);
            spil.dodajKartu(karta);
        }
    }

    // ostao je tekstualni opis: Ime igraca: sve karte u njegovoj ruci
    @Override
    public String toString(){
        StringBuilder s = new StringBuilder(ime).append(" ima u ruci: \n");             // Miljan ima u ruci:
                                                                                        // 7 karo
        for(Karta karta: ruka){
            s.append(karta).append("\n");
        }
        return s.toString();

    }

    // metoda vrednost:
    public int vrednost(){

        int sum = 0;
        for(Karta karte: ruka){
            sum+=karte.procitajVrednost();
        }
        return sum;
    }

}
