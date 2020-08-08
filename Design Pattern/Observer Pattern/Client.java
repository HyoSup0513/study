public class Client {
    public static void main(String[] args) {
        User user = new User();
        ServerA discuss = new ServerA("Discuss server");
        ServerB game = new ServerB("Game server");
        ServerC dev = new ServerC("Development server");
        user.attach(discuss);
        user.attach(game);
        user.attach(dev);

        String message = "Please follow the chatting rules !";
        user.notifyObservers(message);

        user.detach(discuss);
        user.detach(dev);
        message = "Manner maketh the man !";
        user.notifyObservers(message);
    }
}