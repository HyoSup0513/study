public class Client {
    public static void main(String[] args) {
        PC pc = new PC();

        pc.pushPower();
        pc.setPowerState(new OnState());
        pc.pushPower();
        pc.setPowerState(new SleepState());
        pc.pushPower();
        pc.setPowerState(new OffState());
        pc.pushPower();
    }
}