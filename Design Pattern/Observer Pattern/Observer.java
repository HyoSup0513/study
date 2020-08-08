public class Observer {
    public String serverTitle;

    public void receive(String message) {
        System.out.println("[" + this.serverTitle + "] " + "has received message : " + message);
    }
}