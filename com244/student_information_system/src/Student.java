import javax.swing.table.DefaultTableModel;

@SuppressWarnings("serial")

public class Student extends DefaultTableModel {

    public static final Object[] TABLE_HEADER = {"ID", "Student Number", "Name", "Surname", "Phone Number", "Email", "Birth Date", "Birth Place"};
    public static final Object[][] DATA = {};

    Student() {
        super(DATA, TABLE_HEADER);
    }

    public boolean isCellEditable(int row, int column) {
        return false;
    }

    public void updateRow(int index, Object[] values) {
        for (int i = 0; i < values.length; i++) {
            setValueAt(values[i], index, i);
        }
    }
}
