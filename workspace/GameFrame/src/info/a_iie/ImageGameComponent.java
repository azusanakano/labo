package info.a_iie;

import info.a_iie.lib.alg.Coordinates;

import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

/**
 * イメージオブジェクト
 * @author azusa nakano
 */
public abstract class ImageGameComponent extends GameComponent {

	private BufferedImage image = null;		// イメージデータ
	private boolean centerPaint = false;	// 中央描画するかどうか


	/**
	 * コンストラクタ
	 */
	public ImageGameComponent() {
		super();
	}

	/**
	 * バッファを描画する
	 * @param gb グラフィックバッファ
	 * @param g グラフィックオブジェクト
	 */
	public void paint(Graphics gb, Graphics g) {
		draw(gb);
	}

	/**
	 * 通常描画処理
	 * @param gb グラフィックバッファ
	 */
	public void draw(Graphics gb) {
		System.out.println("draw");
		gb.drawImage(getImage(), (int)getDrawX(), (int)getDrawY(), this);
	}

	/**
	 * 生座標描画処理
	 * @param gb グラフィックバッファ
	 */
	public void rawDraw(Graphics gb) {
		gb.drawImage(getImage(), (int)getX(), (int)getY(), this);
	}

	/**
	 * 座標中心描画処理
	 * @param gb グラフィックバッファ
	 */
	public void centerDraw(Graphics gb) {
		gb.drawImage(getImage(), (int)getCenterDrawX(), (int)getCenterDrawY(), this);
	}

	/**
	 * 座標中心描画X座標取得
	 * @return 座標中心描画X座標
	 */
	public float getCenterDrawX() {
		return Coordinates.calcStart(getX(), getWidth());
	}

	/**
	 * 座標中心描画Y座標取得
	 * @return 座標中心描画Y座標
	 */
	public float getCenterDrawY() {
		return Coordinates.calcStart(getY(), getHeight());
	}

	/**
	 * 描画X座標取得
	 * @return 描画X座標
	 */
	public float getDrawX() {
		if (isCenterPaint()) {
			return getCenterDrawX();
		}
		return getX();
	}

	/**
	 * 描画Y座標取得
	 * @return 描画Y座標
	 */
	public float getDrawY() {
		if (isCenterPaint()) {
			return getCenterDrawY();
		}
		return getY();
	}

	/**
	 * 画像取得
	 * @return 画像
	 */
	public BufferedImage getImage() {
		return image;
	}

	/**
	 * 画像設定
	 * @param image 画像
	 */
	public void setImage(BufferedImage image) {
		this.image = image;
	}

	/**
	 * 画像ファイルロード
	 * @param filename ファイルパス
	 * @param id 画像ID
	 * @throws IOException
	 */
	public void loadImage(String filename, int id) throws IOException {
		setImage(ImageIO.read(new File(filename)));
		addImage(image, id);
		waitForAll();
	}

	/**
	 * 画像ファイルロード
	 * @param filename ファイルパス
	 * @throws IOException
	 */
	public void loadImage(String filename) throws IOException {
		loadImage(filename, 0);
	}

	/**
	 * 現在座標を中心に描画するかどうか
	 * @return 現在座標を中心に描画するかどうか
	 */
	public boolean isCenterPaint() {
		return centerPaint;
	}

	/**
	 * 現在座標を中心に描画するかどうか設定
	 * @return centerPaint 現在座標を中心に描画するかどうか
	 */
	public void setCenterPaint(boolean centerPaint) {
		this.centerPaint = centerPaint;
	}
}
