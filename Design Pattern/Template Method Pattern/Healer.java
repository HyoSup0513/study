public class Healer extends Role {
    @Override
    void prepareWeapon() {
        System.out.println("Equip a Wand");
    }

    @Override
    void prepareArmor() {
        System.out.println("Wear a robe.");
    }

    @Override
    boolean isUsingPrepareOther() {
        return true;
    }

    @Override
    void prepareOther() {
        System.out.println("Put the potions in the bag.");
    }
}