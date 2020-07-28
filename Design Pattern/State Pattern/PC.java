public class PC {
    private PowerState powerState;

    public PC() {
        this.powerState = new OffState();
    }

    public void setPowerState(PowerState powerState) {
        this.powerState = powerState;
    }

    public void pushPower() {
        powerState.pushPower();
    }
}