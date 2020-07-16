public class KeyboardStore extends KeyboardStoreFactory {
    @Override
    public Keyboards makeKeyboards(VendorID vendorID) {

        Keyboards keyboard = null;
        switch (vendorID) {
            case CHERRY:
                keyboard = new CherryKeyboards(new CherryComponentsFactory());
                keyboard.setName("Red Cherry Keyboard");
                break;

            case GATERON:
                keyboard = new GateronKeyboards(new GateronComponentsFactory());
                keyboard.setName("Blue Gateron Keyboard");
                break;
        }
        return keyboard;
    }
}