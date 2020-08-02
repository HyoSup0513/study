public class Client {
    public static void main(String args[]) {
        Champion ryze = new Ryze();
        Champion darius = new Darius();

        System.out.println("[Ryze]");
        ryze.setRuneStrategy(new DominationStrategy());
        ryze.setRune();

        System.out.println();
        System.out.println("[Darius]");
        darius.setRuneStrategy(new PrecisionStrategy());
        darius.setRune();

        System.out.println();
        System.out.println("[Ryze]");
        ryze.setRuneStrategy(new SorceryStrategy());
        ryze.setRune();
    }
}