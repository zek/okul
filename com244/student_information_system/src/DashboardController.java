import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;

/**
 * Created by zack on 15.05.2018.
 */
public class DashboardController {

    private Database database;
    private User user;
    private DashboardView view;
    private Student student;
    private StudentController studentController;

    public DashboardController(Database database, User user, DashboardView view) {
        this.database = database;
        this.user = user;
        this.view = view;
        this.student = new Student();
        this.studentController = new StudentController(database, new StudentFormView("Student Form"), student);

        loadStudents("");
        initView();
        initController();
    }


    private void initView() {
        view.getEmailField().setText(user.getMail());
        view.getNameField().setText(user.getName());
        view.getStudents().setModel(student);
    }

    private void initController() {
        view.getSearch().addActionListener(e -> performSearch());
        view.getSearchField().addActionListener(e -> performSearch());
        view.getCreateStudentButton().addActionListener(e -> showStudentForm(-1));
        view.getStudents().addMouseListener(new MouseAdapter() {
            public void mousePressed(MouseEvent mouseEvent) {
                JTable table = (JTable) mouseEvent.getSource();
                Point point = mouseEvent.getPoint();
                int row = table.rowAtPoint(point);
                if (mouseEvent.getClickCount() == 2) {
                    showStudentForm(row);
                }
            }
        });
    }

    private void showStudentForm(int row) {
        int id = -1;
        if (row != -1) {
            id = (Integer) student.getValueAt(row, 0);
        }
        studentController.initView(row, id);
    }

    private void performSearch() {
        loadStudents(view.getSearchField().getText());
    }


    private void loadStudents(String query) {
        try {
            PreparedStatement stmt = database.getConnection().prepareStatement("SELECT * from students where student_number like ?");
            stmt.setString(1, "%" + query + "%");
            while (student.getRowCount() > 0) {
                student.removeRow(0);
            }
            ResultSet rs = stmt.executeQuery();
            if (!rs.next()) {
                JOptionPane.showMessageDialog(null, "No Student Found");
                return;
            }

            do {
                student.addRow(new Object[]{
                        rs.getInt("id"),
                        rs.getString("student_number"),
                        rs.getString("name"),
                        rs.getString("surname"),
                        rs.getString("phone_number"),
                        rs.getString("email"),
                        rs.getDate("birth_date"),
                        rs.getString("birth_place"),
                });
            } while (rs.next());
        } catch (Exception ex) {
            System.err.println(ex);
        }
    }


}
