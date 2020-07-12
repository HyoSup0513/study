/**
 * GeforceStore
 */
public class GeforceStore extends PCshop {
    @Override
    PC assemblePC(String name) {
        if (name.equals("GamingPC")) {
            return new GeforceGamingPC();

        } else if (name.equals("OfficePC")) {

            return new GeforceOfficePC();

        } else if (name.equals("KidPC")) {

            return new GeforceKidPC();

        } else {

            return null;
        }
    }

}