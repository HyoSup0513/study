public class CherryKeyboards extends Keyboards {
    KeyboardsComponentsFactory keyboardsComponentsFactory;

    public CherryKeyboards(KeyboardsComponentsFactory keyboardsComponentsFactory) {
        this.keyboardsComponentsFactory = keyboardsComponentsFactory;
    }

    @Override
    void assembling() {

        System.out.println("Making keyboard.. [" + name + "]");
        body = keyboardsComponentsFactory.makeBody();
        plate = keyboardsComponentsFactory.makePlate();
        switchtype = keyboardsComponentsFactory.makeSwitch();
        System.out.println("Keyboard Info : Body = [" + body.getName() + "], Plate = [" + plate.getName()
                + "], Switch Type = [" + switchtype.getName() + "].");
    }
}