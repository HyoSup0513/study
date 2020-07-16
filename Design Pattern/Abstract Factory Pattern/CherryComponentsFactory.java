public class CherryComponentsFactory implements KeyboardsComponentsFactory {
    @Override
    public Body makeBody() {
        return new CherryBody();
    }

    @Override
    public Plate makePlate() {
        return new CherryPlate();

    }

    @Override
    public Switchtype makeSwitch() {
        return new CherrySwitch();
    }
}