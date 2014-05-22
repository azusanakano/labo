package info.a_iie;

import java.awt.Graphics;
import java.awt.event.KeyEvent;

/**
 * 移動するイメージオブジェクト
 * @author azusa nakano
 */
public abstract class ImageMoveComponent extends ImageGameComponent implements GameKeyEventListener {

	/**
	 * 移動方向
	 */
	public static final int UP = 1;		// 上
	public static final int DOWN = 2;	// 下
	public static final int LEFT = 3;	// 左
	public static final int RIGHT = 4;	// 右

	private float speed = 0.0f;	// 移動スピード
	private int dir = 0;		// 移動方向
	private boolean move = false;		// 移動中かどうか
	private boolean inWindowMove = false;	// 画面内の移動に制限するかどうか
	private boolean moveKeyEnable = false;	// キー移動が可能かどうか

	/**
	 * 設定移動キー
	 */
	private int moveUpKey = KeyEvent.VK_UP;
	private int moveDownKey = KeyEvent.VK_DOWN;
	private int moveLeftKey = KeyEvent.VK_LEFT;
	private int moveRightKey = KeyEvent.VK_RIGHT;

	/**
	 * コンストラクタ
	 */
	public ImageMoveComponent() {
		super();
	}


	@Override
	public abstract void action();

	@Override
	public void inputKey(KeyEventType type, KeyEvent e) {
		actionMoveKey();
	}

	@Override
	public void paint(Graphics gb, Graphics g) {
		super.paint(gb, g);
	}

	/**
	 * キーで操作
	 */
	public void actionMoveKey() {
		if (isMoveKeyEnable()) {
			setIsMove(false);
			if (KeyStateManager.getInstance().get(getMoveUpKey()) == KeyState.ON) {
				setIsMove(moveUp());
			}
			if (KeyStateManager.getInstance().get(getMoveDownKey()) == KeyState.ON) {
				setIsMove(moveDown());
			}
			if (KeyStateManager.getInstance().get(getMoveLeftKey()) == KeyState.ON) {
				setIsMove(moveLeft());
			}
			if (KeyStateManager.getInstance().get(getMoveRightKey()) == KeyState.ON) {
				setIsMove(moveRight());
			}
		}
	}

	/**
	 * 左に移動
	 */
	public boolean moveLeft() {
		setDir(LEFT);
		setX(getX() - getMoveDistance());

		if (isInWindowMove()) {
			if (getX() < 0) {
				setX(0);
				return false;
			}
		}
		return true;
	}

	/**
	 * 右に移動
	 */
	public boolean moveRight() {
		setDir(RIGHT);
		setX(getX() + getMoveDistance());

		if (isInWindowMove()) {
			if (getX() > getRightEdge()) {
				setX(getRightEdge());
				return false;
			}
		}
		return true;
	}


	/**
	 * 下に移動
	 */
	public boolean moveDown() {
		setDir(DOWN);
		setY(getY() + getMoveDistance());

		if (isInWindowMove()) {
			if (getY() > getBottomEdge()) {
				setY(getBottomEdge());
				return false;
			}
		}
		return true;
	}

	/**
	 * 上に移動
	 */
	public boolean moveUp() {
		setDir(UP);
		setY(getY() - getMoveDistance());

		if (isInWindowMove()) {
			if (getY() < 0) {
				setY(0);
				return false;
			}
		}
		return true;
	}

	/**
	 * 移動距離取得
	 * @return 移動距離
	 */
	public float getMoveDistance() {
		return (ga.getFrameTime() * getSpeed());
	}

	/**
	 * 速さ取得
	 * @return 速さ
	 */
	public float getSpeed() {
		return speed;
	}

	/**
	 * 速さ設定
	 * @param speed 速さ
	 */
	public void setSpeed(float speed) {
		this.speed = speed;
	}

	/**
	 * 移動方向取得
	 * @return 移動方向
	 */
	public int getDir() {
		return dir;
	}

	/**
	 * 移動方向設定
	 * @param dir 移動方向
	 */
	public void setDir(int dir) {
		this.dir = dir;
	}



	/**
	 * 上移動キー取得
	 * @return 上移動キー
	 */
	public int getMoveUpKey() {
		return moveUpKey;
	}

	/**
	 * 上移動キー設定
	 * @param 上移動キー
	 */
	public void setMoveUpKey(int moveUpKey) {
		this.moveUpKey = moveUpKey;
	}

	/**
	 * 下移動キー取得
	 * @return 下移動キー
	 */
	public int getMoveDownKey() {
		return moveDownKey;
	}

	/**
	 * 下移動キー設定
	 * @param 下移動キー
	 */
	public void setMoveDownKey(int moveDownKey) {
		this.moveDownKey = moveDownKey;
	}

	/**
	 * 左移動キー取得
	 * @return 左移動キー
	 */
	public int getMoveLeftKey() {
		return moveLeftKey;
	}

	/**
	 * 左移動キー設定
	 * @param 左移動キー
	 */
	public void setMoveLeftKey(int moveLeftKey) {
		this.moveLeftKey = moveLeftKey;
	}

	/**
	 * 右移動キー取得
	 * @return 右移動キー
	 */
	public int getMoveRightKey() {
		return moveRightKey;
	}

	/**
	 * 右移動キー設定
	 * @param 右移動キー
	 */
	public void setMoveRightKey(int moveRightKey) {
		this.moveRightKey = moveRightKey;
	}


	/**
	 * キーで操作可能かどうか
	 * @return 矢印キーで操作可能かどうか
	 */
	public boolean isMoveKeyEnable() {
		return moveKeyEnable;
	}

	/**
	 * キーで操作可能にするかどうか設定
	 * @param actionAllowKeyEnable 矢印キーで操作可能にするかどうか
	 */
	public void setMoveKeyEnable(boolean moveKeyEnable) {
		this.moveKeyEnable = moveKeyEnable;
	}

	/**
	 * 移動中かどうか取得
	 * @return 移動中かどうか
	 */
	public boolean isMove() {
		return move;
	}

	/**
	 * 移動中かどうか設定
	 * @param move 移動中かどうか
	 */
	public void setIsMove(boolean move) {
		this.move = move;
	}

	/**
	 * ゲームキーイベントリスナーに追加
	 * @return 成功したかどうか
	 */
	public boolean addGameKeyEventListener() {
		return ga.addGameKeyEventListener(this);
	}

	/**
	 * ゲームキーイベントリスナーから削除
	 * @return 成功したかどうか
	 */
	public boolean removeGameKeyEventListener() {
		return ga.removeGameKeyEventListener(this);
	}

	/**
	 * 画面内の移動に制限するかどうか取得
	 * @return 画面内の移動に制限するかどうか
	 */
	public boolean isInWindowMove() {
		return inWindowMove;
	}

	/**
	 * 画面内の移動に制限するかどうか設定
	 * @param inWindowMove 画面内の移動に制限するかどうか
	 */
	public void setInWindowMove(boolean inWindowMove) {
		this.inWindowMove = inWindowMove;
	}
}
