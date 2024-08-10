package ExecutorService;

import javax.swing.text.StyledEditorKit;
import java.util.concurrent.*;

public class MainTask {
    public static void main(String[] args) {

        BlockingQueue<Future<Boolean>> redZadataka = new LinkedBlockingQueue<>(10);
        ExecutorService taskovi = Executors.newFixedThreadPool(5);
        // napravili smo thread pool koji ima 5 niti, a gore jedan red koji moze da primi 10 zadataka.
        // a future je interface koji pokazuje rezultat izracunavanja koristi se nakon sto se preda zadatak Executor
        // servisu..
        boolean stop = false;

        while(!stop){
            try{
                // na svakih 0.5 sec
                Thread.sleep(500);
                if(!stop) {
                    Future<Boolean> task = taskovi.submit(new Matrix("Nit: " + (redZadataka.size()+1)));
                    redZadataka.put(task);
                }

               if(redZadataka.size()>0){
                   Future<Boolean> zavrseniZadaci = redZadataka.poll(500, TimeUnit.MILLISECONDS);
                   if(zavrseniZadaci!=null && zavrseniZadaci.get()){
                       stop = true;
                       taskovi.shutdownNow();
                       System.out.println("Obustavljam program dosli smo do zbira dijagonale koja prelazi vrednost 300.");
                   }
               }

            }catch (InterruptedException | ExecutionException e){
                e.printStackTrace();
            }
        }
        taskovi.shutdown();
    }
}
