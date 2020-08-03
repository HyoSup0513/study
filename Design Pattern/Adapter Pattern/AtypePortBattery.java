public class AtypePortBattery implements USBAtypeCable {
    @Override
    public void connectCableA() {
        System.out.println("Connected with USB Type-A cable.");
    }

    @Override
    public void chargeBatteryA() {
        System.out.println("USB Type-A battery is now charging.");
    }
}