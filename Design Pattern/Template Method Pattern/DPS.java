public class DPS extends Classes {
    @Override
    void prepareWeapon() {
        System.out.println("Equip a bow and a quiver.");
    }

    @Override
    void prepareArmor() {
        System.out.println("Wear leather armor.");
    }

    @Override
    boolean isUsingPrepareOther() {
        return true;
    }

    @Override
    void prepareOther() {
        System.out.println("Put arrows into the quiver.");
    }
}