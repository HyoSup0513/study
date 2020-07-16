public class GateronComponentsFactory implements KeyboardsComponentsFactory {
    @Override
    public Body makeBody() {
        return new GateronBody();
    }

    @Override
    public Plate makePlate() {
        return new GateronPlate();

    }

    @Override
    public Switchtype makeSwitch() {
        return new GateronSwitch();
    }
}