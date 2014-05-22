package info.a_iie;

import java.awt.Button;
import java.awt.Component;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.image.ImageObserver;

/**
 * ゲーム部品
 * @author azusa nakano
 */
public abstract class GameComponent implements ImageObserver {

	protected static final GameApplet ga = GameApplet.getInstance();

	private boolean show = true;			// 表示されるかどうか
	private float width = 0.0f; 			// 横幅(ドット単位)
	private float height = 0.0f; 			// 縦幅(ドット単位)
	private float x = 0.0f;					// 描画横位置
	private float y = 0.0f;					// 描画縦位置
	private Component c = new Button();

	/**
	 * コンストラクタ
	 */
	public GameComponent() {
		super();
	}

	/**
	 * ゲーム処理
	 */
	public abstract void action();

	/**
	 * バッファを描画する
	 * @param gb グラフィックバッファ
	 * @param g グラフィックオブジェクト
	 */
	public abstract void paint(Graphics gb, Graphics g);

	/**
	 * ゲームメインスレッドに追加
	 * @return 成功したかどうか
	 */
	public boolean addRunListener() {
		return ga.add(this);
	}

	/**
	 * ゲームメインスレッドから削除
	 * @return 成功したかどうか
	 */
	public boolean removeRunListener() {
		return ga.remove(this);
	}

	/**
	 * ゲームキーイベントリスナーに追加
	 * @param o リスナーオブジェクト
	 * @return 成功したかどうか
	 */
	public boolean addGameKeyEventListener(GameKeyEventListener o) {
		return ga.addGameKeyEventListener(o);
	}

	/**
	 * ゲームキーイベントリスナーから削除
	 * @param o リスナーオブジェクト
	 * @return 成功したかどうか
	 */
	public boolean removeGameKeyEventListener(GameKeyEventListener o) {
		return ga.removeGameKeyEventListener(o);
	}

	/**
	 * イメージをメディアトラッカーに追加
	 * @param i イメージ
	 * @param id イメージID
	 */
	public void addImage(Image image, int id) {
		ga.getMediaTracker().addImage(image, id);
	}

	/**
	 * ロード待ち
	 */
	public void waitForAll() {
		try {
			ga.getMediaTracker().waitForAll();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	/**
	 * 表示されるかどうか判定
	 * @return 表示されるかどうか
	 */
	public boolean isShow() {
		return show;
	}

	/**
	 * 表示されるかどうか設定
	 * @param show 表示されるかどうか
	 */
	public void setShow(boolean show) {
		this.show = show;
	}

	/**
	 * 表示切り替え
	 */
	public void switchShow() {
		this.setShow(! this.isShow());
	}


	@Override
	/**
	 * ImageObserverの実装
	 * awtのButtonクラスの実装を借りる
	 */
	public boolean imageUpdate(Image img, int infoflags, int x, int y, int width, int height) {
		return c.imageUpdate(img, infoflags, x, y, width, height);
	}


	/**
	 * 横幅取得
	 * @return width 横幅(ドット単位)
	 */
	public float getWidth() {
		return width;
	}

	/**
	 * 横幅設定
	 * @param width 横幅(ドット単位)
	 */
	public void setWidth(float width) {
		this.width = width;
	}

	/**
	 * 縦幅取得
	 * @return height 縦幅(ドット単位)
	 */
	public float getHeight() {
		return height;
	}

	/**
	 * 縦幅設定
	 * @param height 縦幅(ドット単位)
	 */
	public void setHight(float height) {
		this.height = height;
	}

	/**
	 * 縦位置取得
	 * @return y 縦位置
	 */
	public float getY() {
		return y;
	}

	/**
	 * 縦位置設定
	 * @param y 縦位置
	 */
	public void setY(float y) {
		this.y = y;
	}

	/**
	 * 横位置取得
	 * @return x 横位置
	 */
	public float getX() {
		return x;
	}

	/**
	 * 横位置設定
	 * @param x 横位置設定
	 */
	public void setX(float x) {
		this.x = x;
	}



	/**
	 * 右端X座標を取得
	 * @return 右端X座標
	 */
	public float getRightEdge() {
		return (ga.getWidth() - getWidth() - ga.getWindowEdge().width);
	}

	/**
	 * 下端Y座標を取得
	 * @return
	 */
	public float getBottomEdge() {
		return (ga.getHeight() - getHeight() - ga.getWindowEdge().height);
	}


}
