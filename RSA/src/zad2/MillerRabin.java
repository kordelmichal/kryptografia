package zad2;
import java.math.BigInteger;
import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.List;

public class MillerRabin {

    private static SecureRandom secureRandom;
    private List<BigInteger> tested;

    public MillerRabin() {
        this.tested = new ArrayList<>();
        this.secureRandom = new SecureRandom();
    }
    public BigInteger randomPrimeNumber(int n){

        BigInteger prime;
        do {
            prime = randomOddNumber(n);
        } while (!testPrime(prime));
        System.out.println("Tested different prime numbers: " + tested.size());
        return prime;
    }

    private BigInteger randomOddNumber(int n) {
        BigInteger prime = new BigInteger(n - 2, secureRandom).add((new BigInteger("2").pow(n-2))).shiftLeft(1).add(new BigInteger("1"));
        return prime;
    }

    private Boolean testPrime(BigInteger number) {

        if(wasTested(number)){
            return false;
        } else {
            tested.add(number);
            return MillerRabin(number);
        }
    }

    private Boolean MillerRabin(BigInteger number) {
        BigInteger d = number.subtract(BigInteger.ONE);

        int s = d.getLowestSetBit();
        d = d.shiftRight(s);

        BigInteger a;
        for (int j = 0; j < 50; j++) {
            do {
                a = new BigInteger(number.bitLength(), secureRandom);
            } while (a.equals(BigInteger.ZERO));
            BigInteger v = a.modPow(d, number);
            if (v.equals(BigInteger.ONE) || v.equals(number.subtract(BigInteger.ONE))) {
                continue;
            }
            int i;
            for (i = 0; i < s; i++) {
                v = v.modPow(new BigInteger("2"), number);
                if (v.equals(number.subtract(BigInteger.ONE))) {
                    break;
                }
            }
            if (i == s) {
                return false;
            }
        }
        return true;
    }

    private Boolean wasTested(BigInteger liczba){
        for(BigInteger l: tested){
            if(l.equals(liczba)){
                return true;
            }
        }
        return false;
    }
}
