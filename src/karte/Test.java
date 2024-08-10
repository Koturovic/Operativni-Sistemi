package karte;

import karte.Igrac;
import karte.Spil;
import karte.Tura;

import java.util.*;

//Напишите Јава програм који ствара шпил карата, додељује по три карте двојици играча,
//затим симулира неколико тура игре у којима играчи узимају карте из шпила, и неколико
//тура игре у којима насумично враћају по једну карту у шпил, а на крају исписати стање игре
//(које карте су у рукама играча а које у шпилу). Победник је онај играч чије карте у руци
//имају укупну мању вредност. При писању програма користите константне параметре (не
//треба ништа учитавати). Овај задатак треба да користи механизме попут notify, wait,
//synchronized како би се синхронизовали приступи шпилу карата.

public class Test {
    public static void main(String[] args) throws InterruptedException{
        // prvo da bi pokrenuli igru morammo da stvorimo spil i da ga napunimo sa standardnim kartama
        Spil spil = new Spil();
        spil.standard(); // ovde sam napunio
        System.out.println("Trenutni spil: \n" + spil);
        System.out.println("Broj karata u spilu je: "+ spil.brojKarata());

        // potrebna su nam dva igraca
        Igrac igrac1 = new Igrac("Marko");
        Igrac igrac2 = new Igrac("Milos");

        // moramo da im dodelimo po tri karte:
        for(int i = 0;i< 3;i++){
            // svaki igrac mora da uzmi u svokoj iteraciji po jednu kartu
            igrac1.uzimaizSpila(spil);
            igrac2.uzimaizSpila(spil);
        }
        // sada cemo da simuliramo igru tako sto cemo da napravimo dve niti(za svakog igraca i one bi trebale da budu
        // sinhronizvane..)
        for(int i = 0; i< 3; i++){

            // OVo su bile igre gde su igraci uzimali karte iz spila
            Thread game1 = new Thread(new Tura(igrac1,spil,true));
            Thread game2 = new Thread(new Tura(igrac2, spil, true));
            // sada kada smo inicijalizovali ove niti potrebno je da ih pokrenemo
            // na da ih sacekamo da zavrse:
            game1.start();
            game2.start();
            game1.join();
            game2.join();


            // sada moramo da napravimo igre gde ce igraci vracati karte u spil odnosno igrati sa kartama
            // koje su uzeli:
            game1 = new Thread(new Tura(igrac1,spil,false));
            game2 = new Thread(new Tura(igrac2, spil, false));
            // sada kada smo inicijalizovali ove niti potrebno je da ih pokrenemo
            // na da ih sacekamo da zavrse:
            game1.start();
            game2.start();
            game1.join();
            game2.join();

        }

        // na samom kraju vrsimo ispis stanja
        // koje karte su u rukama igraca a koje u
        // spilu:
        System.out.println("*********************************");
        System.out.println("\nTrenutno stanje: ");
        System.out.println(igrac1);
        System.out.println(igrac2);
        System.out.println("U spilu su ostale karte : \n" + spil);
        System.out.println("*********************************");

        // Ostalo je da odradimo pobednika ove igre
        // Pobednik je je onaj koji ima manju vrednost u rukama:
        // moram da napravim metodu u klasi Igrac koja ce da racuna ukupnnu vrednost koju igrac drzi u ruci:
        int vr1 = igrac1.vrednost();
        int vr2 = igrac2.vrednost();
        if(vr1>vr2){
            System.out.println("Pobedio je " + igrac2.getIme());
            System.out.println("*********************************");
        } else if (vr2>vr1) {
            System.out.println("Podebio je" + igrac1.getIme());
            System.out.println("*********************************");

        }else{
            System.out.println("niko nije pobedio!");
        }



    }
}
