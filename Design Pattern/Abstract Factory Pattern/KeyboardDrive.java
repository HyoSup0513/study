public class KeyboardDrive {
    public static void main(String[] args) {

        CherryKeyboardStore cherryStore = new CherryKeyboardStore();
        cherryStore.orderKeyboards("Red");

        System.out.println();
        cherryStore.orderKeyboards("Blue");
    }
}