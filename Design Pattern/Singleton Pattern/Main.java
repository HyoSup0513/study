public class Main {
    public static void main(String[] args) {
        // Use Initialization on demand holder idiom
        SystemComponent3 speaker1 = SystemComponent3.getInstance();
        SystemComponent3 speaker2 = SystemComponent3.getInstance();

        System.out.println("Volumn of Speaker1 = " + speaker1.getVolume());
        System.out.println("Volumn of Speaker2 = " + speaker2.getVolume());
        System.out.println();

        System.out.println("Change the Volumn of Speaker2 to 10.");
        // Set Volumn to 10
        speaker2.setVolume(10);

        System.out.println("Volumn of Speaker1 = " + speaker1.getVolume());
        System.out.println("Volumn of Speaker2 = " + speaker2.getVolume());
    }
}