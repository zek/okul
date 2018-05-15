

public class Cloud extends Sprite {

    public Cloud(int x, int y) {
        super(x, y);

        initBar();
    }

    private void initBar() {

        loadImage("src/images/cloud.png");
        getImageDimensions();
    }

    public void move(int level) {
        y -= 0.5 + level * 0.5;

        if (y < -height) {
            y = 200;
        }
    }
}