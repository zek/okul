

public class Heart extends Sprite {

    public Heart(int x, int y) {
        super(x, y);

        initBar();
    }

    private void initBar() {

        loadImage("src/images/heart.png");
        getImageDimensions();
    }
}