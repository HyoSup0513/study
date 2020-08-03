public class Client {

    public static void main(String[] args) {
        AtypePortBattery batteryA = new AtypePortBattery();
        CtypePortBattery batteryC = new CtypePortBattery();

        System.out.println("[USB Type-A Battery]");
        batteryA.connectCableA();
        batteryA.chargeBatteryA();
        System.out.println();

        System.out.println("[USB Type-C Battery]");
        batteryC.connectCableC();
        batteryC.chargeBatteryC();
        System.out.println();

        USBAtypeCable usbAdapter = new USBadpater(batteryC);

        System.out.println("[USB Type-C Battery] using Cable adapter");
        usbAdapter.connectCableA();
        usbAdapter.chargeBatteryA();

    }
}