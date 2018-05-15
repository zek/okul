import javax.swing.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.sql.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class StudentController {

    private Database database;
    private StudentFormView view;
    private Student student;
    private int id;
    private int rowid;

    public StudentController(Database database, StudentFormView view, Student student) {
        this.database = database;
        this.view = view;
        this.student = student;

        initController();
    }


    public void initView(int rowid, int id) {
        this.rowid = rowid;
        this.id = id;
        if (this.id != -1) {
            this.view.getDeleteButton().setVisible(true);
            try {
                PreparedStatement stmt = database.getConnection().prepareStatement("SELECT * from students where id = ?");
                stmt.setInt(1, id);
                ResultSet rs = stmt.executeQuery();
                if (!rs.first()) {
                    JOptionPane.showMessageDialog(null, "No Student Found");
                    return;
                }
                view.getStudentNumberField().setText(rs.getString("student_number"));
                view.getNameField().setText(rs.getString("name"));
                view.getSurnameField().setText(rs.getString("surname"));
                view.getBirthDateField().setValue(rs.getDate("birth_date"));
                view.getBirthPlaceField().setText(rs.getString("birth_place"));
                view.getEmailField().setText(rs.getString("email"));
                view.getPhoneNumberField().setText(rs.getString("phone_number"));
            } catch (SQLException e) {
                e.printStackTrace();
            }
        } else {
            this.view.getDeleteButton().setVisible(false);
            view.getStudentNumberField().setText("");
            view.getNameField().setText("");
            view.getSurnameField().setText("");
            view.getBirthDateField().setText("01/01/1990");
            view.getBirthPlaceField().setText("");
            view.getEmailField().setText("");
            view.getPhoneNumberField().setText("");
        }
        view.getFrame().setVisible(true);

        //view.getEmailField().setText(user.getMail());
        //view.getNameField().setText(user.getName());
    }

    private void initController() {
        view.getSaveButton().addActionListener(e -> performSave());
        view.getDeleteButton().addActionListener(e -> performDelete());
        view.getBirthDateField().addKeyListener(new KeyAdapter() {
            public void keyTyped(KeyEvent e) {
                char c = e.getKeyChar();
                if (!((c >= '0') && (c <= '9') ||
                        (c == KeyEvent.VK_BACK_SPACE) ||
                        (c == KeyEvent.VK_DELETE) || (c == KeyEvent.VK_SLASH))) {
                    JOptionPane.showMessageDialog(null, "Please Enter Valid");
                    e.consume();
                }
            }
        });
    }

    private void performDelete() {
        try {
            PreparedStatement preparedStmt;
            preparedStmt = database.getConnection().prepareStatement("Delete from students where id = ?");
            preparedStmt.setInt(1, id);
            JOptionPane.showMessageDialog(null, "Delete Success!");
            preparedStmt.execute();
            this.view.getFrame().setVisible(false);
            student.removeRow(rowid);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private void performSave() {
        try {
            PreparedStatement preparedStmt;
            if (id == -1) {
                preparedStmt = database.getConnection().prepareStatement("insert into students (student_number, name, surname, birth_date, birth_place, email, phone_number) values(?, ?, ?, ?, ?, ?, ?)");
            } else {
                preparedStmt = database.getConnection().prepareStatement("UPDATE students set student_number = ?, name = ?, surname = ?, birth_date = ?, birth_place = ? , email = ?, phone_number= ? where id = ?");
                preparedStmt.setInt(8, id);
            }
            java.util.Date date1 = (java.util.Date) view.getBirthDateField().getValue();
            java.sql.Date date = new java.sql.Date(date1.getTime());
            Object[] obj = new Object[]{
                    id,
                    view.getStudentNumberField().getText(),
                    view.getNameField().getText(),
                    view.getSurnameField().getText(),
                    view.getPhoneNumberField().getText(),
                    view.getEmailField().getText(),
                    date,
                    view.getBirthPlaceField().getText(),
            };
            preparedStmt.setString(1, (String) obj[1]);
            preparedStmt.setString(2, (String) obj[2]);
            preparedStmt.setString(3, (String) obj[3]);
            preparedStmt.setDate(4, (Date) obj[6]);
            preparedStmt.setString(5, (String) obj[7]);
            preparedStmt.setString(6, (String) obj[5]);
            preparedStmt.setString(7, (String) obj[4]);
            preparedStmt.execute();
            if (id == -1) {
                student.addRow(obj);
            } else {
                student.updateRow(rowid, obj);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        JOptionPane.showMessageDialog(null, "Success!");
        this.view.getFrame().setVisible(false);
    }


}
