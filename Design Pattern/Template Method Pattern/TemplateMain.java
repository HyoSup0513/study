/**
 * TemplateMain
 */
public class TemplateMain {
    public static void main(String[] args) {

        System.out.println("[Tank]");
        Tank class01 = new Tank();
        class01.readyToBattle();
        System.out.println();

        System.out.println("[DPS]");
        DPS class02 = new DPS();
        class02.readyToBattle();
        System.out.println();

        System.out.println("[Healer]");
        Healer class03 = new Healer();
        class03.readyToBattle();
    }
}