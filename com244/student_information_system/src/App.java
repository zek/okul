import javax.swing.*;

import static java.lang.System.exit;

/**
 * Created by zack on 15.05.2018.
 */
public class App {

    public static void main(String[] args) {
        Database database = new Database("localhost", "root", "", "javaodev");
        try {
            database.connect();
        } catch (Exception e) {
            JOptionPane.showMessageDialog(null, e.getMessage(), "MySQL Connection Error", JOptionPane.INFORMATION_MESSAGE);
            exit(-1);
        }
        new LoginController(database, new LoginView());
    }
}
