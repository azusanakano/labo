package info.a_iie.lib.map;

import java.util.HashMap;

/**
 * マップデータ管理
 * @author azusa nakano
 */
public class MapManager {

	// マップデータリスト
	private static final HashMap<Integer, Map> map = new HashMap<Integer, Map>();

	/**
	 * マップデータ作成
	 * @param filename ファイル名
	 * @param width 横幅（セル単位）
	 * @param height 縦幅（セル単位）
	 * @param chipsize セルサイズ（ドット単位）
	 * @param id マップID
	 * @return マップデータ
	 */
	public static Map createMapInstance(String filename, int width, int height, int chipsize, int id) {
		Map m = new Map(filename, width, height, chipsize);
		setMap(id, m);
		return m;
	}

	/**
	 * マップデータ取得
	 * @param i マップID
	 * @return マップデータ
	 */
	public static Map getMap(int i) {
		Map m = map.get(i);
		return m;
	}

	/**
	 * マップデータ設定
	 * @param i マップID
	 * @param m マップデータ
	 * @return 設定前のマップデータ
	 */
	public static Map setMap(int i, Map m) {
		return map.put(i, m);
	}
}
