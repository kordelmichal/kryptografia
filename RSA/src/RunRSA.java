import java.math.BigInteger;

public class RunRSA {
    RSA rsa;
    public RunRSA(){
        rsa = new RSA();
    }

    public void generateKeys(int k, int d){

        rsa.generateKeys(k, d);
        System.out.println("keys saved.");
    }

    public void encode(String number){
        BigInteger e = new BigInteger("27535779821683974469467919701058553153");
        BigInteger n = new BigInteger("45802681293869255473225777285933559761");
        rsa.encode(BigInteger.valueOf(42), e,n);
    }
    public void decode(String number){
        BigInteger d = new BigInteger("12689698062779370052261845729319258817");
        BigInteger n = new BigInteger("45802681293869255473225777285933559761");
        rsa.decode(new BigInteger("3960877242537775304150321175462699694"), d, n);
    }
}
