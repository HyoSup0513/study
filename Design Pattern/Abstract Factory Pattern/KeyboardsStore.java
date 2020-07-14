public abstract class KeyboardsStore {
    public Keyboards orderKeyboards(String name) {
        Keyboards keyboard;

        keyboard = makeKeyboards(name);
        keyboard.assembling();
        keyboard.prepare();
        keyboard.packing();

        return keyboard;
    }

    abstract Keyboards makeKeyboards(String name);
}