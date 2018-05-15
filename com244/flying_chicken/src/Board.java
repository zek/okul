import javax.swing.JPanel;


import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.ArrayList;
import java.util.List;
import javax.swing.Timer;

public class Board extends JPanel implements ActionListener {

    private Timer timer;
    private Chicken chicken;
    private List<Target> targets;
    private List<Cat> cats;
    private List<Heart> hearts;
    private boolean ingame;
    private int hearts_left;
    private int points;
    private int level = 1;
    private final int ICHICKEN_X = 40;
    private final int ICHICKEN_Y = 60;
    private final int B_WIDTH = 400;
    private final int B_HEIGHT = 300;
    private final int DELAY = 15;
    private static Font monoFont = new Font("Monospaced", Font.PLAIN, 12);

    private Cloud cloud;

    public Board() {

        initBoard();
    }

    private void initBoard() {

        addKeyListener(new TAdapter());
        setFocusable(true);
        setBackground(new Color(130, 170, 231));
        setDoubleBuffered(true);
        ingame = true;
        hearts_left = 3;
        points = 0;
        setPreferredSize(new Dimension(B_WIDTH, B_HEIGHT));

        chicken = new Chicken(ICHICKEN_X, ICHICKEN_Y);

        initCats();
        initTargets();
        initHearts();
        initCloud();

        timer = new Timer(DELAY, this);
        timer.start();
    }

    public void nextLevel() {
        level++;
        if (level > 3) {
            ingame = false;
        } else {
            targets = new ArrayList<>();

            for (int i = targets.size(); i < level * 10 + 20; i++) {
                targets.add(new Target());
            }

            cats = new ArrayList<>();

            for (int i = cats.size(); i < level * 10; i++) {
                cats.add(new Cat());
            }
        }
    }

    public void initCats() {

        cats = new ArrayList<>();

        for (int i = cats.size(); i < 10; i++) {
            cats.add(new Cat());
        }
    }

    public void initTargets() {

        targets = new ArrayList<>();

        for (int i = targets.size(); i < 30; i++) {
            targets.add(new Target());
        }
    }

    public void initHearts() {

        hearts = new ArrayList<>();
        int x = B_WIDTH - 17 * 3;

        for (int i = 0; i < 3; i++) {
            hearts.add(new Heart(x + i * 16, 5));
        }
    }

    public void initCloud() {

        cloud = new Cloud(0, 200);
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);

        if (ingame) {

            drawObjects(g);

        } else {

            drawGameOver(g);
        }

        Toolkit.getDefaultToolkit().sync();
    }

    private void drawObjects(Graphics g) {

        g.setColor(Color.WHITE);
        g.setFont(monoFont);

        if (cloud.isVisible()) {
            g.drawImage(cloud.getImage(), cloud.getX(), cloud.getY(),
                    this);
        }

        if (chicken.isVisible()) {
            g.drawImage(chicken.getImage(), chicken.getX(), chicken.getY(),
                    this);
        }

        List<Egg> ms = chicken.getEggs();

        for (Egg egg : ms) {
            if (egg.isVisible()) {
                g.drawImage(egg.getImage(), egg.getX(),
                        egg.getY(), this);
            }
        }

        for (int i = 0; i < hearts_left; i++) {
            Heart heart = hearts.get(i);
            if (heart.isVisible()) {
                g.drawImage(heart.getImage(), heart.getX(),
                        heart.getY(), this);
            }
        }

        for (Cat cat : cats) {
            if (cat.isVisible()) {
                g.drawImage(cat.getImage(), cat.getX(), cat.getY(), this);
            }
        }

        g.setColor(Color.WHITE);
        g.drawString("Points: " + points, 5, 15);

        g.setColor(Color.WHITE);
        g.drawString("Level: " + level, 5, 290);

        for (Target target : targets) {
            if (target.isVisible()) {
                target.draw(g);
            }
        }
    }

    private void drawGameOver(Graphics g) {

        String msg = "Points: " + points;
        Font small = new Font("Helvetica", Font.BOLD, 14);
        FontMetrics fm = getFontMetrics(small);

        g.setColor(Color.white);
        g.setFont(small);
        g.drawString(msg, (B_WIDTH - fm.stringWidth(msg)) / 2,
                B_HEIGHT / 2);
    }

    @Override
    public void actionPerformed(ActionEvent e) {

        inGame();

        updateChickens();
        updateTargets();
        updateEggs();
        updateCloud();
        updateCats();

        checkCollisions();

        repaint();
    }

    private void inGame() {

        if (!ingame) {
            timer.stop();
        }
    }

    private void updateChickens() {

        if (chicken.isVisible()) {

            chicken.move();
        }
    }

    private void updateTargets() {
        for (int i = 0; i < targets.size(); i++) {
            Target a = targets.get(i);

            if (a.isVisible()) {
                a.move(level);
            } else {
                targets.remove(i);
            }
        }
        if (targets.size() == 0) {
            nextLevel();

        }
    }

    private void updateCloud() {

        if (cloud.isVisible()) {

            cloud.move(level);
        }
    }

    private void updateEggs() {

        List<Egg> ms = chicken.getEggs();

        for (int i = 0; i < ms.size(); i++) {

            Egg m = ms.get(i);

            if (m.isVisible()) {
                m.move();
            } else {
                ms.remove(i);
            }
        }
    }

    private void updateCats() {

        for (int i = 0; i < cats.size(); i++) {

            Cat a = cats.get(i);

            if (a.isVisible()) {
                a.move(level);
            } else {
                points++;
                a.init();
                a.setVisible(true);

            }
        }
    }

    public void checkCollisions() {

        Rectangle r3 = chicken.getBounds();

        for (Cat cat : cats) {

            Rectangle r2 = cat.getBounds();

            if (r3.intersects(r2)) {

                cat.setVisible(false);
                if (hearts_left == 0) {
                    chicken.setVisible(false);
                    ingame = false;
                }
                hearts_left--;
                break;
            }
        }

        List<Egg> ms = chicken.getEggs();

        for (Egg m : ms) {

            Rectangle r1 = m.getBounds();
            for (Target target : targets) {

                Rectangle r2 = target.getBounds();

                if (r1.intersects(r2)) {
                    m.setVisible(false);
                    target.setVisible(false);
                    points += target.getPoint();
                }
            }
        }
    }

    private class TAdapter extends KeyAdapter {

        @Override
        public void keyReleased(KeyEvent e) {
            chicken.keyReleased(e);
        }

        @Override
        public void keyPressed(KeyEvent e) {
            chicken.keyPressed(e);
        }
    }
}