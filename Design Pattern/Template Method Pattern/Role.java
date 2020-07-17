public abstract class Role {

    void readyToBattle() {
        startBodyTraining();
        prepareWeapon();
        prepareArmor();
        if (isUsingPrepareOther()) {
            prepareOther();
        }
    }

    final void startBodyTraining() {
        System.out.println("Increase stamina.");
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