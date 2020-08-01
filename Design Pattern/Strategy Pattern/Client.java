public class Client {
    public static void main(String args[]) {
        Champion ryze = new Ryze();
        Champion darius = new Darius();

        ryze.setRuneStrategy(new DominationStrategy());
        ryze.setRune();

        darius.setRuneStrategy(new PrecisionStrategy());
        darius.setRune();

        ryze.setRuneStrategy(new SorceryStrategy());
        ryze.setRune();

        ryze.setRuneStrategy(new DominationStrategy());
    }
}