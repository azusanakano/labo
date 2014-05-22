package info.a_iie.lib.map;

import info.a_iie.lib.alg.Coordinates;

/**
 * マップ中心表示計算実装
 * @author azusa nakano
 */
public class MapCenterImpl extends MapObject implements MapCenter {

	/**
	 * コンストラクタ
	 * @param width 表示幅（横）(セル単位）
	 * @param height 表示幅（縦）（セル単位）
	 * @param map マップデータ
	 */
	public MapCenterImpl(int width, int height, Map map) {
		super(width, height, map);
	}

	/**
	 * 表示開始X座標取得
	 * @return 表示開始X座標
	 */
	public float getViewX() {
		return Coordinates.calcCenterDrawStart(ga.getWidth(), getWidth());
	}

	/**
	 * 表示開始Y座標取得
	 * @return 表示開始Y座標
	 */
	public float getViewY() {
		return Coordinates.calcCenterDrawStart(ga.getHeight(), getHeight());
	}

}
