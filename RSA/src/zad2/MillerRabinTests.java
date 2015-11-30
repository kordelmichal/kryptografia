package zad2;

import filesHandling.FilesHandler;


public class MillerRabinTests {

    public void test(int k, int d){
        FilesHandler fh = new FilesHandler(null, "resources\\performance\\data.txt", true);
        runTest(k, d, fh);
    }
    public void runTest(int k, int d, FilesHandler fh){

        long start = System.currentTimeMillis();
        FilesHandler threadFH = new FilesHandler(null, "resources\\performance\\primes"+d+".txt", true);
        TestThread[] testThreads = new TestThread[k];

        for(int i=0; i<k; i++){
            testThreads[i]=new TestThread(i, d, threadFH);
            testThreads[i].start();
        }
        while(stop(testThreads)){
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        long end = System.currentTimeMillis();
        String s = "Time for k: "+k +" and d: "+d+" is: "+(end-start)*0.001+" sec\n";
        fh.write(s.getBytes());
        System.out.println("\n"+s);
    }
    public static boolean stop(Thread[] threads){
        for(int i=0; i<threads.length; i++){
            if(threads[i].isAlive()){
                return true;
            }
        }
        return false;
    }
}
