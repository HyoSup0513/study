public class CherryComponentsFactory implements KeyboardsComponentsFactory {
    @Override
    public Body makeBody() {
        return new AluminumBody();
    }

    @Override
    public Plate makePlate() {
        return new AluminumPlate();

    }

    @Override
    public Switchtype makeSwitch() {
        return new RedSwitch();
    }
}