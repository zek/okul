
import java.awt.event.KeyEvent;
import java.util.ArrayList;
import java.util.List;

public class Chicken extends Sprite {

    private int dx;
    private List<Egg> eggs;
    private boolean direction;

    public Chicken(int x, int y) {
        super(x, y);

        initCraft();
    }

    private void initCraft() {

        eggs = new ArrayList<>();
        loadImage("src/images/chick.png");
        getImageDimensions();
    }

    public void move() {

        x += dx;

        if (x < 1) {
            x = 1;
        }

        if (x > 380) {
            x = 380;
        }

    }

    public List<Egg> getEggs() {
        return eggs;
    }

    public void keyPressed(KeyEvent e) {

        int key = e.getKeyCode();

        if (key == KeyEvent.VK_SPACE) {
            fire();
        }

        if (key == KeyEvent.VK_LEFT) {
            dx = -2;
            direction = false;
        }

        if (key == KeyEvent.VK_RIGHT) {
            dx = 2;
            direction = true;
        }
    }

    public void fire() {
        int dx = direction ? width : -width;
        eggs.add(new Egg(x + dx, y, direction));
    }

    public void keyReleased(KeyEvent e) {

        int key = e.getKeyCode();

        if (key == KeyEvent.VK_LEFT) {
            dx = 0;
        }

        if (key == KeyEvent.VK_RIGHT) {
            dx = 0;
        }
    }
}