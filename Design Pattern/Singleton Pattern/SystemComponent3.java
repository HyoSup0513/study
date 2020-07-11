
// Initialization on demand holder idiom
public class SystemComponent3 {
    private int volume;

    private SystemComponent3() {
        volume = 5;
    }

    private static class Holder {
        public static final SystemComponent3 INSTANCE = new SystemComponent3();
    }

    public static SystemComponent3 getInstance() {
        return Holder.INSTANCE;
    }

    public int getVolume() {
        return volume;
    }

    public void setVolume(int volume) {
        this.volume = volume;
    }
}