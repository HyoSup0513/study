public class CherryKeyboardStore extends KeyboardsStore {
    @Override
    public Keyboards makeKeyboards(String name) {

        Keyboards keyboard = null;
        if (name.equals("Red")) {
            keyboard = new RedSwitchKeyboards(new CherryComponentsFactory());
            keyboard.setName("Red Cherry Keyboard");
        } else if (name.equals("Blue")) {
            keyboard = new BlueSwitchKeyboards(new GateronComponentsFactory());
            keyboard.setName("Blue Gateron Keyboard");
        }
        return keyboard;
    }
}