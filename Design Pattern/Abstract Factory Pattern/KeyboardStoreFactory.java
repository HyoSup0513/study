public abstract class KeyboardStoreFactory {
    public Keyboards orderKeyboards(VendorID venderID) {
        Keyboards keyboard;

        keyboard = makeKeyboards(venderID);
        keyboard.assembling();
        keyboard.prepare();
        keyboard.packing();

        return keyboard;
    }

    abstract Keyboards makeKeyboards(VendorID venderID);
}