package info.a_iie;

import java.awt.event.KeyEvent;

/**
 * キー入力インタフェース
 * @author azusa nakano
 */
public interface GameKeyEventListener {

	/**
	 * キーが押された時
	 * @param e キーイベント
	 */
	public abstract void onKeyPressed(KeyEvent e);

	/**
	 * キーが離された時
	 * @param e キーイベント
	 */
	public abstract void onKeyReleased(KeyEvent e);

	/**
	 * アルファベットキーがタイプされた時
	 * @param e キーイベント
	 */
	public abstract void onKeyTyped(KeyEvent e);

	/**
	 * キーイベント
	 * @param type イベントタイプ
	 * @param e キーイベント
	 */
	public abstract void inputKey(KeyEventType type, KeyEvent e);
}
