import java.util.Arrays;

public class PCshopTest {
    public static void main(String[] args) {
        PCshop gGaming = new GeforceStore();
        PCshop rKid = new RadeonStore();

        PC pc1 = gGaming.orderPC("GamingPC");
        System.out.println("The computer you bought at the GeForce store --> " + Arrays.toString(pc1.getInfo()));
        System.out.println();

        PC pc2 = rKid.orderPC("KidPC");
        System.out.println("The computer you bought at the Radeon store --> " + Arrays.toString(pc2.getInfo()));
    }
}