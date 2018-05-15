import javax.swing.*;
import java.text.DateFormat;
import java.text.SimpleDateFormat;

/**
 * Created by zack on 15.05.2018.
 */
public class StudentFormView {
    private final JFrame frame;
    private JTextField studentNumberField;
    private JButton saveButton;
    private JPanel panel;
    private JTextField nameField;
    private JTextField surnameField;
    private JTextField phoneNumberField;
    private JTextField emailField;
    private JFormattedTextField birthDateField;
    private JTextField birthPlaceField;
    private JButton deleteButton;


    public StudentFormView(String title) {
        frame = new JFrame(title);
        frame.setContentPane(this.panel);
        frame.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
        frame.pack();
        frame.setLocationRelativeTo(null);
    }

    public JFrame getFrame() {
        return frame;
    }

    public JTextField getStudentNumberField() {
        return studentNumberField;
    }

    public void setStudentNumberField(JTextField studentNumberField) {
        this.studentNumberField = studentNumberField;
    }

    public JButton getSaveButton() {
        return saveButton;
    }

    public void setSaveButton(JButton saveButton) {
        this.saveButton = saveButton;
    }

    public JPanel getPanel() {
        return panel;
    }

    public void setPanel(JPanel panel) {
        this.panel = panel;
    }

    public JTextField getNameField() {
        return nameField;
    }

    public void setNameField(JTextField nameField) {
        this.nameField = nameField;
    }

    public JTextField getSurnameField() {
        return surnameField;
    }

    public void setSurnameField(JTextField surnameField) {
        this.surnameField = surnameField;
    }

    public JTextField getPhoneNumberField() {
        return phoneNumberField;
    }

    public void setPhoneNumberField(JTextField phoneNumberField) {
        this.phoneNumberField = phoneNumberField;
    }

    public JTextField getEmailField() {
        return emailField;
    }

    public void setEmailField(JTextField emailField) {
        this.emailField = emailField;
    }

    public JFormattedTextField getBirthDateField() {
        return birthDateField;
    }

    public void setBirthDateField(JFormattedTextField birthDateField) {
        this.birthDateField = birthDateField;
    }

    public JTextField getBirthPlaceField() {
        return birthPlaceField;
    }

    public void setBirthPlaceField(JTextField birthPlaceField) {
        this.birthPlaceField = birthPlaceField;
    }

    private void createUIComponents() {
        DateFormat df = new SimpleDateFormat("dd/MM/yyyy");
        this.birthDateField = new JFormattedTextField(df);
    }

    public JButton getDeleteButton() {
        return deleteButton;
    }

    public void setDeleteButton(JButton deleteButton) {
        this.deleteButton = deleteButton;
    }
}
