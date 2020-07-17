public class Tank extends Role {
    @Override
    void prepareWeapon() {
        System.out.println("Equip a sword and shield.");
    }

    @Override
    void prepareArmor() {
        System.out.println("Wear metal armor.");
    }

}