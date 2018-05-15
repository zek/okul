import java.awt.*;
import java.util.Random;

public class Target {
    private static Random rand = new Random();
    private int x, y, point;
    protected boolean visible;

    private Font font;

    public Target() {
        this.point = 3 + rand.nextInt(5);
        this.visible = true;
        this.x = rand.nextBoolean() ? 0 : 400 - point * 4;
        this.y = 1500 - rand.nextInt(1200);;
        this.font = new Font("Monospaced", Font.BOLD
                | Font.ITALIC, point * 2);
    }

    public Rectangle getBounds() {
        return new Rectangle(x, y, point * 4, point * 4);
    }

    public int getPoint(){
        return point;
    }

    public void move(int level) {
        if (y < 0) {
            setVisible(false);
        }

        y -= 0.5 + level * 0.5;
    }

    public void draw(Graphics g) {
        g.setColor(Color.magenta);
        g.fillOval(x, y, point * 4, point * 4);

        g.setColor(Color.WHITE);
        g.setFont(font);
        FontMetrics fm = g.getFontMetrics();
        int w = fm.stringWidth(Integer.toString(point));
        int h = fm.getAscent();
        g.drawString(Integer.toString(point), this.x + point * 2 - (w / 2), this.y + point * 2 + (h / 4));

    }

    public boolean isVisible() {
        return visible;
    }

    public void setVisible(Boolean visible) {
        this.visible = visible;
    }

}
