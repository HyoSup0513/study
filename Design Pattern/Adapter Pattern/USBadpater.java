public class USBadpater implements USBAtypeCable {
    USBCtypeCable usbCtypeCable;

    public USBadpater(USBCtypeCable usbCtypeCable) {
        this.usbCtypeCable = usbCtypeCable;
    }

    @Override
    public void connectCableA() {
        usbCtypeCable.connectCableC();
    }

    @Override
    public void chargeBatteryA() {
        usbCtypeCable.chargeBatteryC();
    }

}