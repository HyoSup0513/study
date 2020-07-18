public abstract class Classes {

    void readyToBattle() {
        repairWeapons();
        prepareWeapon();
        prepareArmor();
        if (isUsingPrepareOther()) {
            prepareOther();
        }
    }

    final void repairWeapons() {
        System.out.println("Repair weapons..");
    }

    abstract void prepareWeapon();

    abstract void prepareArmor();

    // If you want to prepare something else, you have to change it to 'true'.
    boolean isUsingPrepareOther() {
        return false;
    }

    // Override 'isUsingPrepareOther' value to use.
    void prepareOther() {
    };
}