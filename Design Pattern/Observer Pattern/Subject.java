import java.util.ArrayList;
import java.util.List;

public class Subject {
    private List<Observer> observers = new ArrayList<Observer>();

    // Add to Observer
    public void attach(Observer observer) {
        observers.add(observer);
    }

    // Remove from Observer
    public void detach(Observer observer) {
        observers.remove(observer);
    }

    // Notify the Observer
    public void notifyObservers(String message) {
        for (Observer o : observers) {
            o.receive(message);
        }
    }
}