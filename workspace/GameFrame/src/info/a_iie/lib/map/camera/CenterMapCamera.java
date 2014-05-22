package info.a_iie.lib.map.camera;

import info.a_iie.lib.map.Map;
import info.a_iie.lib.map.MapCenter;
import info.a_iie.lib.map.MapCenterImpl;

import java.awt.Graphics;

/**
 * 中央表示マップカメラ
 * @author azusa nakano
 */
public class CenterMapCamera extends MapCamera implements MapCenter {

	/**
	 * 中心計算オブジェクト
	 */
	private MapCenter center = null;

	/**
	 * コンストラクタ
	 * @param width 横幅（セル単位）
	 * @param height 縦幅（セル単位）
	 * @param map マップデータ
	 */
	public CenterMapCamera(int width, int height, Map map) {
		super(width, height, map);
		center = new MapCenterImpl(width, height, map);
	}


	/**
	 * 表示開始X座標取得
	 * @return 表示開始X座標
	 */
	public int getStartX() {
		updateX();
		int xx = getCellX() - getCellWidth();
		if (xx < 0) {
			xx = 0;
		}
		return xx;
	}

	/**
	 * 表示開始Y座標取得
	 * @return 表示開始Y座標
	 */
	public int getStartY() {
		updateY();
		int yy = getCellY() - getCellHeight();
		if (yy < 0) {
			yy = 0;
		}
		return yy;
	}

	/**
	 * 表示終了X座標取得
	 * @return 表示終了X座標
	 */
	public int getEndX() {
		int xx = getCellX() + getCellWidth();
		if (xx > getMap().getCellWidth()) {
			xx = getMap().getCellWidth();
		}
		int startX = getCellX() - getCellWidth();
		if (startX <= 0) {
			xx += startX * -1;
		}
		return xx;
	}

	/**
	 * 表示終了Y座標取得
	 * @return 表示終了Y座標
	 */
	public int getEndY() {
		int yy = getCellY() + getCellHeight();
		if (yy > getMap().getCellHeight()) {
			yy = getMap().getCellHeight();
		}
		int startY = getCellY() - getCellHeight();
		if (startY <= 0) {
			yy += startY * -1;
		}
		return yy;
	}

	@Override
	public void paint(Graphics gb, Graphics g) {
		dotUnitPaint(gb);
	}

	/**
	 * ドット単位で移動の場合の描画
	 * @param g 描画バッファのグラフィックコンテキスト
	 */
	private void dotUnitPaint(Graphics g) {
		try {
			System.out.println("x getStartX():" + getStartX() + " getEndX():" + getEndX());
			System.out.println("x getStartY():" + getStartY() + " getEndY():" + getEndY());

			int startX = getStartX();
			int startY = getStartY();
			int endX = getEndX();
			int endY = getEndY();

			for (int i = startY; i < endY; i++) {
				for (int j = startX; j < endX; j++) {
					int graphics = getMap().getGraphics(j, i);

					// マップチップからマップグラフィクスの位置を取得
					int xx = toDotUnit(graphics % getMap().getCellCount());
					int yy = toDotUnit(graphics / getMap().getCellCount());

					// マップ描画位置
					int dspX = (int)(getViewX() + toDotUnit(j - startX));
					int dspY = (int)(getViewY() + toDotUnit(i - startY));

					g.drawImage(getMap().getImage(), dspX, dspY, dspX + getMap().getChipSize(), dspY + getMap().getChipSize(), xx, yy, xx + getMap().getChipSize(), yy + getMap().getChipSize(), this);
				}
			}
		} catch (Throwable e) {
			e.printStackTrace();
		}
	}

	/**
	 * 表示X座標取得
	 * @return 表示X座標
	 */
	public float getViewX() {
		return center.getViewX();
	}

	/**
	 * 表示Y座標取得
	 * @return 表示Y座標
	 */
	public float getViewY() {
		return center.getViewY();
	}
}
