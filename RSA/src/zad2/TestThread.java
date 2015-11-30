package zad2;

import java.math.BigInteger;

import filesHandling.FilesHandler;

public class TestThread extends Thread {

    int id;
    int d;
    FilesHandler fh;
    public TestThread(int id, int d, FilesHandler fh){
        this.id = id;
        this.d = d;
        this.fh = fh;
    }

    @Override
    public void run() {
        MillerRabin millerRabin = new MillerRabin();
        BigInteger prime =  millerRabin.randomPrimeNumber(d);
        System.out.println(prime);

        fh.write((prime.toString()+"\n").getBytes());
        try {
            sleep(10);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
