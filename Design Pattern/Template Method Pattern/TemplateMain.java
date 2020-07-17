/**
 * TemplateMain
 */
public class TemplateMain {
    public static void main(String[] args) {

        Tank user01 = new Tank();
        user01.readyToBattle();
        System.out.println();

        DPS user02 = new DPS();
        user02.readyToBattle();
        System.out.println();

        Healer user03 = new Healer();
        user03.readyToBattle();
    }
}