package info.a_iie.lib.map.obj;

import info.a_iie.lib.map.Map;
import info.a_iie.lib.map.MapCenter;
import info.a_iie.lib.map.MapCenterImpl;

import java.awt.Graphics;


/**
 * マップ中心移動オブジェクト
 * @author azusa nakano
 */
public class MapCenterMoveObject extends MapMoveObject implements MapCenter {

	/**
	 * 中心計算オブジェクト
	 */
	private MapCenter center = null;

	/**
	 * コンストラクタ
	 * @param width 表示幅（横）(セル単位）
	 * @param height 表示幅（縦）（セル単位）
	 * @param map マップデータ
	 */
	public MapCenterMoveObject(int width, int height, Map map) {
		super(width, height, map);
		this.setCenterPaint(true);
		center = new MapCenterImpl(width, height, map);
	}

	/**
	 * 表示X座標取得
	 * @return 表示X座標
	 */
	public float getViewX() {
		float xx = center.getViewX();

		// カメラが左端の場合
		if (getMapCamera().isMapLeftEdge()) {

			xx = getCenterDrawX() + getMapCamera().getMapLeftEdge();
			if (xx > center.getViewX()) {
				xx = center.getViewX();
			}
			if (xx < getMapCamera().getMapLeftEdge()) {
				xx = getMapCamera().getMapLeftEdge();
			}
		}
		// カメラが右端の場合
		else if (getMapCamera().isMapRightEdge()) {

			xx = getCenterDrawX() + getMapCamera().getMapRightEdge();
			if (xx > center.getViewX()) {
				xx = center.getViewX();
			}
			if (xx < getMapCamera().getMapLeftEdge()) {
				xx = getMapCamera().getMapLeftEdge();
			}
		}

		return xx;
	}

	/**
	 * 表示Y座標取得
	 * @return 表示Y座標
	 */
	public float getViewY() {
		return center.getViewY();
	}

	@Override
	public void paint(Graphics gb, Graphics g) {
		viewDraw(gb);
	}

	/**
	 * 表示座標を使用した通常描画処理
	 * @param gb グラフィックバッファ
	 */
	public void viewDraw(Graphics gb) {
		gb.drawImage(getImage(), (int)getViewX(), (int)getViewY(), this);
	}


}
