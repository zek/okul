import javax.swing.*;

/**
 * Created by zack on 15.05.2018.
 */
public class DashboardView {
    private final JFrame frame;
    private JTable students;
    private JPanel panel;
    private JLabel profilePicture;
    private JLabel nameField;
    private JLabel emailField;
    private JTextField searchField;
    private JButton search;
    private JButton createStudentButton;

    private void createUIComponents() {
        profilePicture = new JLabel(new ImageIcon("./profile.png"));
        students = new JTable();
    }


    public DashboardView() {
        frame = new JFrame("App");
        frame.setContentPane(this.panel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }

    public JLabel getProfilePicture() {
        return profilePicture;
    }

    public JLabel getNameField() {
        return nameField;
    }

    public void setNameField(JLabel nameField) {
        this.nameField = nameField;
    }

    public JLabel getEmailField() {
        return emailField;
    }

    public void setEmailField(JLabel emailField) {
        this.emailField = emailField;
    }

    public JTable getStudents() {
        return students;
    }

    public void setStudents(JTable students) {
        this.students = students;
    }

    public JTextField getSearchField() {
        return searchField;
    }

    public void setSearchField(JTextField searchField) {
        this.searchField = searchField;
    }

    public JButton getSearch() {
        return search;
    }

    public void setSearch(JButton search) {
        this.search = search;
    }

    public JButton getCreateStudentButton() {
        return createStudentButton;
    }

    public void setCreateStudentButton(JButton createStudentButton) {
        this.createStudentButton = createStudentButton;
    }
}
