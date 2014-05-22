package info.a_iie.lib.map;

import info.a_iie.ImageMoveComponent;

import java.awt.event.KeyEvent;

/**
 * マップ上のオブジェクト
 * @author azusa nakano
 */
public class MapObject extends ImageMoveComponent  {

	private Map map;	// マップデータ

	/**
	 * コンストラクタ
	 * @param width 表示幅（横）(セル単位）
	 * @param height 表示幅（縦）（セル単位）
	 * @param map マップデータ
	 */
	public MapObject(int width, int height, Map map) {
		this.setMap(map);
		this.setWidth(toDotUnit(width));
		this.setHight(toDotUnit(height));
	}

	/**
	 * マップデータ取得
	 * @return マップデータ
	 */
	public Map getMap(){
		return map;
	}

	/**
	 * マップデータ設定
	 * @param map マップデータ
	 */
	public void setMap(Map map) {
		this.map = map;
	}

	/**
	 * セルX座標取得
	 * @return セルX座標
	 */
	public int getCellX() {
		return toCellUnit(getX());
	}

	/**
	 * セルY座標取得
	 * @return セルY座標
	 */
	public int getCellY() {
		return toCellUnit(getY());
	}

	/**
	 * ドット単位に変換
	 * @param i セル単位
	 * @return ドット単位
	 */
	public int toDotUnit(int i) {
		return toDotUnit(i, getMap().getChipSize());
	}

	/**
	 * セル単位に変換
	 * @param f ドット単位
	 * @return セル単位
	 */
	public int toCellUnit(float f) {
		return toCellUnit(f, getMap().getChipSize());
	}

	/**
	 * ドット単位に変換
	 * @param i セル単位
	 * @param size セルサイズ
	 * @return ドット単位
	 */
	public int toDotUnit(int i, int size) {
		return (i * size);
	}

	/**
	 * セル単位に変換
	 * @param f ドット単位
	 * @param size セルサイズ
	 * @return セル単位
	 */
	public int toCellUnit(float f, int size) {
		return (int)(f / size);
	}

	@Override
	public void action() {
		// 何もしない
	}

	@Override
	public void onKeyPressed(KeyEvent e) {
		// 何もしない
	}

	@Override
	public void onKeyReleased(KeyEvent e) {
		// 何もしない
	}

	@Override
	public void onKeyTyped(KeyEvent e) {
		// 何もしない
	}
}
