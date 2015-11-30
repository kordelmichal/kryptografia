
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;

import filesHandling.FilesHandler;
import zad2.MillerRabin;

public class RSA {

    public void generateKeys(int k, int dBits){

        List<BigInteger> primesList = generatePrimes(dBits, k);

        BigInteger n = module(primesList); 
        BigInteger euler = fi(primesList);      
        BigInteger e = coprime(euler);
        BigInteger d = e.modInverse(euler);
        

        FilesHandler fh = new FilesHandler(null, "resources\\keys\\keys.txt", true);
        fh.write(("e: "+e.toString()+"\n").getBytes());
        fh.write(("d: "+d.toString()+"\n").getBytes());
        fh.write(("n: "+n.toString()+"\n").getBytes());
        fh.write(("\n\n").getBytes());
        System.out.println("e: "+e+"\nd: "+d+"\nn: "+n);
    }


    public BigInteger encode(BigInteger text, BigInteger e, BigInteger n)
    {	
    	System.out.println("Encoded: " + text.modPow(e, n));
        return text.modPow(e, n);
    }
    public BigInteger decode(BigInteger text, BigInteger d, BigInteger n){
    	System.out.println("Decoded: " + text.modPow(d, n));
        return text.modPow(d, n);
    }
    private List<BigInteger> generatePrimes( int k, int dBits){
        List<BigInteger> primes = new ArrayList<>();
        MillerRabin millerRabin = new MillerRabin();

        for(int i=0; i<k; i++){
            primes.add(millerRabin.randomPrimeNumber(dBits));
        }

        return primes;
    }
    private BigInteger module(List<BigInteger> primesList){
        BigInteger result = BigInteger.ONE;
        for(BigInteger b: primesList){
            result = result.multiply(b);
        }
        return result;
    }
    private BigInteger fi(List<BigInteger> primesList){
        BigInteger result = BigInteger.ONE;
        for(BigInteger b:primesList){
            result = result.multiply(b.subtract(BigInteger.ONE));
        }
        return result;
    }

    private BigInteger coprime(BigInteger number){
        BigInteger candidate = number.subtract(BigInteger.ONE);
        do{
        	candidate = candidate.subtract(BigInteger.ONE);
        } while(!(candidate.gcd(number)).equals(BigInteger.ONE));
        return candidate;
    }
}
