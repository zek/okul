import javax.swing.*;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import static jdk.nashorn.internal.objects.NativeString.trim;

public class LoginController {
    private Database database;
    private User user;
    private LoginView loginView;

    public LoginController(Database database, LoginView loginView) {
        this.database = database;
        this.user = new User();
        this.loginView = loginView;
        initView();
        initController();
    }

    private void initView() {

    }

    private void initController() {
        loginView.getLoginButton().addActionListener(e -> performLogin());
    }

    private boolean _performLogin(String username, String password) {
        ResultSet rs = null;
        PreparedStatement stmt = null;
        try {
            stmt = database.getConnection().prepareStatement("SELECT * FROM javaodev.users WHERE username = ? AND password = ?");
            stmt.setString(1, trim(username));
            stmt.setString(2, trim(password));
            rs = stmt.executeQuery();
            if (rs.first()) {
                user.setId(rs.getInt("id"));
                user.setUsername(rs.getString("username"));
                user.setPassword(rs.getString("password"));
                user.setMail(rs.getString("email"));
                user.setName(rs.getString("name"));
                return true;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (stmt != null) stmt.close();
                if (rs != null) rs.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return false;
    }

    private void performLogin() {
        if (_performLogin(loginView.getUsernameField().getText(), String.valueOf(loginView.getPasswordField().getPassword()))) {
            JOptionPane.showMessageDialog(null, "Login Success!");
            new DashboardController(database, user, new DashboardView());
        } else {
            JOptionPane.showMessageDialog(null, "Invalid Credentials");
        }
    }
}
