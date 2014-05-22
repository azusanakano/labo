package info.a_iie.lib.map.camera;

import info.a_iie.lib.alg.Coordinates;
import info.a_iie.lib.map.Map;
import info.a_iie.lib.map.obj.MapMoveObject;


/**
 * マップカメラ
 * @author azusa nakano
 */
public class MapCamera extends MapMoveObject {

	private MapMoveObject centerObject = null;	// センターオブジェクト
	private int cellWidth = 0;				// 表示幅（横）（セル単位）
	private int cellHeight = 0;				// 表示幅（縦）（セル単位）

	/**
	 * コンストラクタ
	 * @param width 表示幅（横）(セル単位）
	 * @param height 表示幅（縦）（セル単位）
	 * @param map マップデータ
	 */
	public MapCamera(int width, int height, Map map) {
		super(width, height, map);
		setCellWidth(width);
		setCellHeight(height);
	}

	/**
	 * 中央表示オブジェクトに合わせてX位置を合わせる
	 */
	public void updateX() {
		if (getCenterObject() != null) {
			setX(getCenterObject().getX());
		}
	}

	/**
	 * 中央表示オブジェクトに合わせてY位置を合わせる
	 */
	public void updateY() {
		if (getCenterObject() != null) {
			setY(getCenterObject().getY());
		}
	}

	/**
	 * 中央表示オブジェクト取得
	 * @return centerObject 中央表示オブジェクト
	 */
	public MapMoveObject getCenterObject() {
		return centerObject;
	}

	/**
	 * 中央表示オブジェクト設定
	 * @param centerObject 中央表示オブジェクト
	 */
	public void setCenterObject(MapMoveObject centerObject) {
		this.centerObject = centerObject;
		this.centerObject.setMapCamera(this);
	}

	/**
	 * 表示開始X座標取得
	 * @return 表示開始X座標
	 */
	public int getStartX() {
		updateX();
		int xx = (int)(getX() - getWidth());
		if (xx < 0) {
			xx = 0;
		}

		return xx;
	}

	/**
	 * 表示開始X座標取得
	 * @return 表示開始X座標
	 */
	public int getUnitStartX() {
		return toCellUnit(getStartX());
	}

	/**
	 * 表示開始Y座標取得
	 * @return 表示開始Y座標
	 */
	public int getStartY() {
		updateY();
		int yy = (int)(getY() - getHeight());
		if (yy < 0) {
			yy = 0;
		}
		return yy;
	}

	/**
	 * 表示開始Y座標取得
	 * @return 表示開始Y座標
	 */
	public int getUnitStartY() {
		return toCellUnit(getStartY());
	}

	/**
	 * 表示終了X座標取得
	 * @return 表示終了X座標
	 */
	public int getEndX() {
		updateX();
		float xx = (getX() + getWidth() + getMap().getChipSize());
		if (xx > getMap().getWidth() + getMap().getChipSize() - 1) {
			xx = getMap().getWidth() + getMap().getChipSize() - 1;
		}

		return (int)xx;
	}

	/**
	 * 表示終了X座標取得
	 * @return 表示終了X座標
	 */
	public int getUnitEndX() {
		return toCellUnit(getEndX());
	}

	/**
	 * 表示終了Y座標取得
	 * @return 表示終了Y座標
	 */
	public int getEndY() {
		updateY();
		float yy = (getY() + getHeight() + getMap().getChipSize());
		if (yy > getMap().getHeight() + getMap().getChipSize() - 1) {
			yy = getMap().getHeight() + getMap().getChipSize() - 1;
		}
		return (int)yy;
	}

	/**
	 * 表示終了Y座標取得
	 * @return 表示終了Y座標
	 */
	public int getUnitEndY() {
		return toCellUnit(getEndY());
	}

	/**
	 * 表示幅（横）（セル単位）取得
	 * @return 表示幅（横）（セル単位）
	 */
	public int getCellWidth() {
		return cellWidth;
	}

	/**
	 * 表示幅（横）（セル単位）設定
	 * @param cellWidth 表示幅（横）（セル単位）
	 */
	public void setCellWidth(int cellWidth) {
		this.cellWidth = cellWidth;
	}

	/**
	 * 表示幅（縦）（セル単位）取得
	 * @return 表示幅（縦）（セル単位）
	 */
	public int getCellHeight() {
		return cellHeight;
	}

	/**
	 * 表示幅（縦）（セル単位）設定
	 * @param cellHeight 表示幅（縦）（セル単位）
	 */
	public void setCellHeight(int cellHeight) {
		this.cellHeight = cellHeight;
	}

	/**
	 * マップの左端かどうか取得
	 * @return マップの左端かどうか
	 */
	public boolean isMapLeftEdge() {
		return (getStartX() <= 0);
	}

	/**
	 * @center
	 * マップ描画左端座標取得
	 * @return マップ描画左端座標
	 */
	public float getMapLeftEdge() {
		return Coordinates.calcCenterDrawStart(ga.getWidth(), getWidth());
	}

	/**
	 * マップの右端かどうか取得
	 * @return マップの右端かどうか
	 */
	public boolean isMapRightEdge() {
		return (getEndX() >= getMapRightEdge());
	}

	/**
	 * @center
	 * マップ描画右端座標取得
	 * @return マップ描画右端座標
	 */
	public float getMapRightEdge() {
		return Coordinates.calcCenterDrawEnd(ga.getWidth(), getWidth());
	}


	/**
	 * マップの上端かどうか取得
	 * @return マップの上端かどうか
	 */
	public boolean isMapTopEdge() {
		return (getEndX() <= 0);
	}

	/**
	 * @center
	 * マップ描画上端座標取得
	 * @return マップ描画上端座標
	 */
	public float getMapTopEdge() {
		return Coordinates.calcCenterDrawStart(ga.getHeight(), getHeight());
	}

	/**
	 * マップの下端かどうか取得
	 * @return マップの下端かどうか
	 */
	public boolean isMapBottomEdge() {
		return (getEndY() >= getMapBottomEdge());
	}

	/**
	 * @center
	 * マップ描画下端座標取得
	 * @return マップ描画下端座標
	 */
	public float getMapBottomEdge() {
		return Coordinates.calcCenterDrawEnd(ga.getHeight(), getHeight());
	}



	/**
	 * マップの横の端かどうか
	 * @return マップの横の端かどうか
	 */
	public boolean isWidthEdge() {
		return (isMapLeftEdge() || isMapRightEdge());
	}

	/**
	 * マップの縦の端かどうか取得
	 * @return
	 */
	public boolean isHeightEdge() {
		return (isMapTopEdge() || isMapBottomEdge());
	}
}

