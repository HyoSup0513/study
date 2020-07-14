public abstract class Keyboards {
    String name;
    Body body;
    Plate plate;
    Switchtype switchtype;

    abstract void assembling();

    void prepare() {

        System.out.println("Preparing the assembled keyboard..");
    }

    void packing() {

        System.out.println("Packing the keyboard..");
    }

    public String getName() {

        return name;
    }

    public void setName(String name) {

        this.name = name;
    }
}