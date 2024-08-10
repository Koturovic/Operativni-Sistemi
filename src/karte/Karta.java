package karte;
//Карта има јединствени аутоматски генерисани идентификатор и вредност (број од 1 до 13)
//и знак (срце, каро, треф, пик). Може се прочитати вредност и знак карте, као и креирати
//копија карте. Такође, може се саставити текстуални опис у облику "Вредност Знак" (нпр. "7
//Срце").
public class Karta {
    private static int statID = 0;
    private final int id = ++statID;
    private final int vrednost; //(1-13)
    private final String znak; // srce karo tref pik
    // seter:
    public Karta(int vrednost, String znak){
        this.vrednost = vrednost;
        this.znak = znak;
    }
    public int procitajVrednost(){
        return vrednost;
    }
    public String procitajZnak(){
        return znak;
    }
    public Karta kopija(){
        return new Karta(this.vrednost, this.znak);
    }
    public String toString(){
        return vrednost+ " " + znak;
    }
}
