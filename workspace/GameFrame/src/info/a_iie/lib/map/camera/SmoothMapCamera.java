package info.a_iie.lib.map.camera;

import info.a_iie.lib.map.Map;
import info.a_iie.lib.map.obj.MapMoveObject;

import java.awt.Graphics;


/**
 * スムーズカメラ
 * @author azusa nakano
 */
public class SmoothMapCamera extends MapCamera {

	/**
	 * コンストラクタ
	 * @param width 表示幅（横）
	 * @param height 表示幅（縦）
	 * @param map マップデータ
	 */
	public SmoothMapCamera(int width, int height, Map map) {
		super(width, height, map);
	}

	@Override
	public void paint(Graphics gb, Graphics g) {
		dotUnitPaint(gb);
	}

	/**
	 * 中央表示オブジェクト設定
	 * @param centerObject 中央表示オブジェクト
	 */
	public void setCenterObject(MapMoveObject centerObject) {
		super.setCenterObject(centerObject);
		if (getCenterObject() != null) {
			this.getCenterObject().setCenterPaint(true);
		}
	}

	/**
	 * ドット単位で移動の場合の描画
	 * @param g 描画バッファのグラフィックコンテキスト
	 */
	private void dotUnitPaint(Graphics g) {
		System.out.println("getUnitStartX():" + getUnitStartX() + " getUnitEndX()" + getUnitEndX());
		for (int i = getUnitStartY(); i < getUnitEndY(); i++) {
			for (int j = getUnitStartX(); j < getUnitEndX(); j++) {
				int graphics = getMap().getGraphics(j, i);

				// マップチップからマップグラフィクスの位置を取得
				int xx = toDotUnit(graphics % getMap().getCellCount());
				int yy = toDotUnit(graphics / getMap().getCellCount());

				// マップ描画位置
				int dspX = toDotUnit(j);
				int dspY = toDotUnit(i);

				int xCompensation = 0;
				int yCompensation = 0;

				int dspXEnd = 0;
				int xxEnd = 0;
				if (getUnitStartX() == j) {
					dspX = getStartX();
					xCompensation = getStartX() % getMap().getChipSize();
					xx += xCompensation;
					dspXEnd = dspX + getMap().getChipSize() - xCompensation;
					xxEnd = xx + getMap().getChipSize() - xCompensation;
				}
				else if (getUnitEndX() - 1 == j) {
					xCompensation = getEndX() % getMap().getChipSize();
					if (isWidthEdge()) {
						xCompensation = getMap().getChipSize();
					}
					xxEnd = xx + xCompensation;
					dspXEnd = dspX + xCompensation;
				}
				else {
					xCompensation = getMap().getChipSize();
					xxEnd = xx + xCompensation;
					dspXEnd = dspX + xCompensation;
				}

				int dspYEnd = 0;
				int yyEnd = 0;
				if (getUnitStartY() == i) {
					dspY = getStartY();
					yCompensation = getStartY() % getMap().getChipSize();
					yy += yCompensation;
					dspYEnd = dspY + getMap().getChipSize() - yCompensation;
					yyEnd = yy + getMap().getChipSize() - yCompensation;
				}
				else if (getUnitEndY() - 1 == i) {
					yCompensation = getEndY() % getMap().getChipSize();
					if (isHeightEdge()) {
						yCompensation = getMap().getChipSize();
					}
					yyEnd = yy + yCompensation;
					dspYEnd = dspY + yCompensation;
				}
				else {
					yCompensation = getMap().getChipSize();
					yyEnd = yy + yCompensation;
					dspYEnd = dspY + yCompensation;
				}

				g.drawImage(getMap().getImage(), dspX, dspY, dspXEnd, dspYEnd, xx, yy, xxEnd, yyEnd, this);
			}
		}
	}

}
