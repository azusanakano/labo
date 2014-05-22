package info.a_iie;

import java.awt.event.KeyEvent;
import java.util.HashMap;

/**
 * キー入力状態管理
 * @author azusa nakano
 */
public class KeyStateManager {

	private static final KeyStateManager o = new KeyStateManager();
	private HashMap<Integer, KeyState> m = new HashMap<Integer, KeyState>();

	/**
	 * プライベートコンストラクタ
	 */
	private KeyStateManager() {
	}

	/**
	 * インスタンス取得
	 * @return インスタンス
	 */
	public static KeyStateManager getInstance() {
		return o;
	}

	/**
	 * キー状態設定
	 * @param type イベントタイプ
	 * @param e キーイベント
	 */
	public void set(KeyEventType type, KeyEvent e) {
		if (type == KeyEventType.KEY_PRESSED) {
			m.put(e.getKeyCode(), KeyState.ON);
		}
		else if (type == KeyEventType.KEY_RELEASED) {
			m.put(e.getKeyCode(), KeyState.OFF);
		}
		else if (type == KeyEventType.KEY_TYPED) {
			m.put(e.getKeyCode(), KeyState.TYPED);
		}
	}

	/**
	 * キー状態取得
	 * @param keyCode キーコード
	 * @return キー状態
	 */
	public KeyState get(int keyCode) {
		KeyState s = m.get(keyCode);
		if (s == null) {
			return KeyState.OFF;
		}
		return s;
	}

	/**
	 * キー状態取得
	 * @param e キーイベント
	 * @return キー状態
	 */
	public KeyState get(KeyEvent e) {
		if (e == null) {
			return KeyState.OFF;
		}
		return get(e.getKeyCode());
	}
}
