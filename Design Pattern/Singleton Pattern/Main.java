public class Main {
    public static void main(String[] args) {
        // Use Initialization on demand holder idiom
        SystemComponent3 speaker1 = SystemComponent3.getInstance();
        SystemComponent3 speaker2 = SystemComponent3.getInstance();

        System.out.println(speaker1.getVolume());
        System.out.println(speaker2.getVolume());

        // Set Volumn to 10
        speaker2.setVolume(10);

        System.out.println(speaker1.getVolume());
        System.out.println(speaker2.getVolume());
    }
}