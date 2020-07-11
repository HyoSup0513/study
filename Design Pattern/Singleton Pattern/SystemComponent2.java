// Thread safe lazy initialization + Double-checked locking
public class SystemComponent2 {
    private volatile static SystemComponent2 instance;

    private SystemComponent2() {
    }

    public static SystemComponent2 getInstance() {
        if (instance == null) {
            synchronized (SystemComponent2.class) {
                instance = new SystemComponent2();
            }
        }
        return instance;
    }
}