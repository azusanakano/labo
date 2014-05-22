package info.a_iie;

import java.awt.Frame;

/**
 * ゲームウィンドウ
 * @author azusa nakano
 *
 */
public class GameFrame extends Frame {

	private static GameApplet gameApplet = null;

	/**
	 * コンストラクタ
	 */
	public GameFrame() {
		super();
	}

	/**
	 * インスタンス取得
	 * @return インスタンス
	 */
	public static final GameApplet getGameApplet() {
		return gameApplet;
	}

	/**
	 * 初期化
	 * @param args　引数
	 */
	public void init(String[] args)
	{
		setVisible(true);
		setSize(200, 100);
		gameApplet = GameApplet.createInstance(this);
		add(gameApplet);
		gameApplet.init();
	}

	/**
	 * 開始
	 */
	public void start()
	{
		gameApplet.start();
	}


	/**
	 * メイン
	 * @param args　引数
	 */
	public static void main(String[] args) {
		GameFrame f = new GameFrame();
		System.out.println("game start");
		f.init(args);
		System.out.println("game start 1");
		f.start();
		System.out.println("game start 2");
		return;
	}
}
