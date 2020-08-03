public class CtypePortBattery implements USBCtypeCable {
    @Override
    public void connectCableC() {
        System.out.println("Connected with USB Type-C cable.");
    }

    @Override
    public void chargeBatteryC() {
        System.out.println("USB Type-C battery is now charging.");
    }
}