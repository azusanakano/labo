package info.a_iie;

import java.applet.Applet;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.MediaTracker;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * ゲーム表示画面
 * @author azusa nakano
 */
public class GameApplet extends Applet implements Runnable, KeyListener {

	// ゲームアプリケーションメインクラス
	private static final String appClassName = "info.a_iie.application.ApplicationMain";

	// Windows7 ウィンドウ端補正
	private static final Dimension WIN7_WINDOW_EDGE = new Dimension(15, 37);

	// キーイベントリスナー
	private static final List<GameKeyEventListener> gameKeyEventListener = new ArrayList<GameKeyEventListener>();

	// メディアトラッカー
	private static MediaTracker mediaT = null;


	private static GameApplet o = null;		// ゲーム表示画面
	private Image imageBuffer = null;		// イメージバッファ
	private Graphics graphicsBuffer = null;	// グラフィックバッファ
	private GameFrame parent = null;		// ゲームウィンドウ
	private List<GameComponent> components = new ArrayList<GameComponent>();	// ゲーム部品
	private float frameTime = 0.0f;	// 1フレームあたりの時間（秒）
	private long waitTime = 0;		// 現在時刻保存用
	private Dimension windowEdge = WIN7_WINDOW_EDGE;	// ウィンドウ端補正
	private Color bgColor = Color.black;		// 背景色
	private Object sync = new Object();	// 同期オブジェクト
	private Object syncKey = new Object();		// キーイベント同期オブジェクト


	/**
	 * privateコンストラクタ
	 * @param parent ゲームアプリケーション
	 */
	private GameApplet(GameFrame parent){
		super();
		if (parent == null) {
			try {
				throw new GameInitException();
			} catch (GameInitException e) {
				e.printStackTrace();
			}
		}
		this.parent = parent;
		mediaT = new MediaTracker(this);
	}

	/**
	 * インスタンス取得
	 * @return インスタンス
	 * @throws GameInitException
	 */
	public static final GameApplet getInstance() {
		if (o == null) {
			try {
				throw new GameInitException();
			} catch (GameInitException e) {
				e.printStackTrace();
			}
		}
		return o;
	}

	/**
	 * インスタンス作成
	 * @param parent ゲームウィンドウ
	 * @return インスタンス
	 */
	public static final GameApplet createInstance(GameFrame parent) {
		if (o == null) {
			o = new GameApplet(parent);
		}
		return o;
	}

	/**
	 * 初期化
	 */
	public void init () {
		super.init();

		// キーリスナーに登録
		addKeyListener(this);
		requestFocus();

		// ゲームアプリケーションメインオブジェクト作成
		try {
			Class.forName(appClassName).newInstance();
		} catch (ClassNotFoundException | InstantiationException | IllegalAccessException e) {
			e.printStackTrace();
		}
	}

	public void start() {
		// スレッド開始
		Thread thread = new Thread(this);
		thread.start();
		super.start();
	}

	/**
	 * ゲームメインループ
	 */
	public void run() {
		try {
			// 現在時刻保存
			waitTime = System.currentTimeMillis();

			while (true) {
				updateFrameTime();
				action();
				// update → paintの順に呼び出す
				repaint();
				Thread.sleep(10);
			}
		}
		catch (Throwable e) {
			e.printStackTrace();
		}
	}

	/**
	 * 1フレーム時間計算
	 */
	private void updateFrameTime()
	{
		frameTime = ((System.currentTimeMillis() - waitTime) / 1000.0f);
		waitTime = System.currentTimeMillis();
	}

	/**
	 * ゲーム処理
	 */
	public void action() {
		Iterator<GameComponent> i = components.iterator();
		synchronized (sync) {
			while (i.hasNext()) {
				GameComponent c = i.next();
				c.action();
			}
		}
	}

	/**
	 * 描画更新
	 */
	public void update(Graphics g) {
		this.updateBuffer();
		this.paint(g);
	}

	/**
	 * バッファ更新
	 */
	private void updateBuffer()
	{
		Dimension parentD = parent.getSize();
		Dimension d = getSize();

		// 初期化orサイスが変わったら
		if (d.equals(parentD) == false || imageBuffer == null) {
			setSize(parentD);
			d = getSize();

			// バッファ作成
			imageBuffer = createImage(d.width, d.height);
			// バッファのグラフィクスコンテキストを取得する
			graphicsBuffer = imageBuffer.getGraphics();
		}
	}

	/**
	 * バッファを描画する
	 */
	public void paint(Graphics g) {
		if (graphicsBuffer == null) {
			return;
		}
		Dimension d = getSize();
		graphicsBuffer.setColor(this.bgColor);
		graphicsBuffer.fillRect(0, 0, d.width, d.height);

		synchronized (sync) {
			Iterator<GameComponent> i = components.iterator();
			while (i.hasNext()) {
				GameComponent c = i.next();
				if (c.isShow()) {
					c.paint(graphicsBuffer, g);
				}
			}
		}

		// ウィンドウを更新する
		g.drawImage(getImageBuffer(), 0, 0, this);
	}

	/**
	 * キーイベント
	 * @param type イベントタイプ
	 * @param e キーイベント
	 */
	private void inputKey(KeyEventType type, KeyEvent e) {
		Iterator<GameKeyEventListener> i = gameKeyEventListener.iterator();
		synchronized (syncKey) {
			while (i.hasNext()) {
				GameKeyEventListener o = i.next();
				o.inputKey(type, e);

				if (type == KeyEventType.KEY_PRESSED) {
					o.onKeyPressed(e);
				}
				else if (type == KeyEventType.KEY_RELEASED) {
					o.onKeyReleased(e);
				}
				else if (type == KeyEventType.KEY_TYPED) {
					o.onKeyTyped(e);
				}
			}
		}
	}


	/**
	 * イメージバッファ取得
	 * @return イメージバッファ
	 */
	public Image getImageBuffer() {
		return imageBuffer;
	}

	/**
	 * イメージバッファ設定
	 * @param imageBuffer イメージバッファ
	 */
	public void setImageBuffer(Image imageBuffer) {
		this.imageBuffer = imageBuffer;
	}

	/**
	 * グラフィックバッファ取得
	 * @return グラフィックバッファ
	 */
	public Graphics getGraphicsBuffer() {
		return graphicsBuffer;
	}

	/**
	 * グラフィックバッファ設定
	 * @param graphicsBuffer グラフィックバッファ
	 */
	public void setGraphicsBuffer(Graphics graphicsBuffer) {
		this.graphicsBuffer = graphicsBuffer;
	}

	/**
	 * 背景色取得
	 * @return 背景色
	 */
	public Color getBgColor() {
		return bgColor;
	}

	/**
	 * 背景色設定
	 * @param bgColor 背景色
	 */
	public void setBgColor(Color bgColor) {
		this.bgColor = bgColor;
	}

	/**
	 * コンポーネント追加
	 * @param c コンポーネント
	 */
	public boolean add(GameComponent c) {
		synchronized (sync) {
			return this.components.add(c);
		}
	}

	/**
	 * コンポーネント削除
	 * @param c コンポーネント
	 */
	public boolean remove(GameComponent c) {
		synchronized (sync) {
			return this.components.remove(c);
		}
	}

	/**
	 * 1フレーム時間取得(秒)
	 * @return 1フレーム時間（秒）
	 */
	public float getFrameTime() {
		return frameTime;
	}

	/**
	 * ウィンドウエッジ取得
	 * @return ウィンドウエッジ補正
	 */
	public Dimension getWindowEdge() {
		return windowEdge;
	}

	/**
	 * メディアトラッカー取得
	 * @return メディアトラッカー
	 */
	public MediaTracker getMediaTracker() {
		return mediaT;
	}

	/**
	 * ゲームキーイベントリスナーに追加
	 * @param o リスナーオブジェクト
	 * @return 成功したかどうか
	 */
	public boolean addGameKeyEventListener(GameKeyEventListener o) {
		synchronized (syncKey) {
			return gameKeyEventListener.add(o);
		}
	}

	/**
	 * ゲームキーイベントリスナーから削除
	 * @param o リスナーオブジェクト
	 * @return 成功したかどうか
	 */
	public boolean removeGameKeyEventListener(GameKeyEventListener o) {
		synchronized (syncKey) {
			return gameKeyEventListener.remove(o);
		}
	}

	@Override
	public void keyTyped(KeyEvent e) {
		KeyStateManager.getInstance().set(KeyEventType.KEY_TYPED, e);
		inputKey(KeyEventType.KEY_TYPED, e);
	}

	@Override
	public void keyPressed(KeyEvent e) {
		KeyStateManager.getInstance().set(KeyEventType.KEY_PRESSED, e);
		inputKey(KeyEventType.KEY_PRESSED, e);
	}

	@Override
	public void keyReleased(KeyEvent e) {
		KeyStateManager.getInstance().set(KeyEventType.KEY_RELEASED, e);
		inputKey(KeyEventType.KEY_RELEASED, e);
	}

	/**
	 * サイズセット
	 */
	public void setSize(int width, int height) {
		parent.setSize(width, height);
		super.setSize(width, height);
	}
}


