public class GateronComponentsFactory implements KeyboardsComponentsFactory {
    @Override
    public Body makeBody() {
        return new PlasticBody();
    }

    @Override
    public Plate makePlate() {
        return new PlasticPlate();

    }

    @Override
    public Switchtype makeSwitch() {
        return new BlueSwitch();
    }
}