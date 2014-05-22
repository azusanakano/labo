package info.a_iie.lib.map.obj;

import info.a_iie.lib.map.Map;
import info.a_iie.lib.map.MapObject;
import info.a_iie.lib.map.camera.MapCamera;


/**
 * マップを移動するオブジェクト
 * @author azusa nakano
 */
public class MapMoveObject extends MapObject {

	private MapCamera mapCamera = null;	// マップカメラ

	/**
	 * コンストラクタ
	 * @param width 表示幅（横）(セル単位）
	 * @param height 表示幅（縦）（セル単位）
	 * @param map マップデータ
	 */
	public MapMoveObject(int width, int height, Map map) {
		super(width, height, map);
		this.setMoveKeyEnable(true);
	}

	/**
	 * マップカメラ設定
	 * @param mapCamera マップカメラ
	 */
	public void setMapCamera(MapCamera mapCamera) {
		this.mapCamera = mapCamera;
	}

	/**
	 * マップカメラ取得
	 * @return マップカメラ
	 */
	public MapCamera getMapCamera() {
		return this.mapCamera;
	}
}
