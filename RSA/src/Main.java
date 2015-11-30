


import java.io.File;

import zad2.MillerRabinTests;

public class Main {

    public static void main(String[] args) {

        new File("resources\\keys\\").mkdirs();
        new File("resources\\performance\\").mkdirs();
        if(args.length>=2){
            if(args.length==3){
                if(args[0].equals("gen_keys")) {
                    new RunRSA().generateKeys(Integer.parseInt(args[1]), Integer.parseInt(args[2]));
                } else if(args[0].equals("gen_primes")){
                    new MillerRabinTests().test(Integer.parseInt(args[1]), Integer.parseInt(args[2]));
                }
            }
            else if(args[0].equals("encode")){
                new RunRSA().encode(args[1]);
            } else if(args[0].equals("decode")){
                new RunRSA().decode(args[1]);
            }
        } else{
            System.out.println("wrong args");
        }
    }



}
