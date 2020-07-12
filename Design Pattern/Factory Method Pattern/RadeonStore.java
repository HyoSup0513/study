public class RadeonStore extends PCshop {
    @Override
    PC assemblePC(String name) {
        if (name.equals("GamingPC")) {
            return new RadeonGamingPC();

        } else if (name.equals("KidPC")) {

            return new RadeonKidPC();

        } else {

            return null;
        }
    }
}