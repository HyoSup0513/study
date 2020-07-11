// Lazy initialization (Thread-Safe)
public class SystemComponent1 {
    private static SystemComponent1 instance;

    private SystemComponent1() {
    }

    public static SystemComponent1 getInstance() {
        if (instance == null) {
            instance = new SystemComponent1();
        }
        return instance;
    }
}
