package info.a_iie.lib.map.camera;

import info.a_iie.lib.map.Map;

import java.awt.Graphics;


/**
 * セル単位表示のマップカメラ
 * @author azusa nakano
 */
public class CellMapCamera extends MapCamera {

	/**
	 * コンストラクタ
	 * @param width 表示幅（横）
	 * @param height 表示幅（縦）
	 * @param map マップデータ
	 */
	public CellMapCamera(int width, int height, Map map) {
		super(width, height, map);
	}

	@Override
	public void paint(Graphics gb, Graphics g) {
		cellUnitPaint(gb);
	}

	/**
	 * セル単位で移動の場合の描画
	 * @param g 描画バッファのグラフィックコンテキスト
	 */
	private void cellUnitPaint(Graphics g) {
		for (int i = getUnitStartY(); i < getUnitEndY(); i++) {
			for (int j = getUnitStartX(); j < getUnitEndX(); j++) {
				int graphics = getMap().getGraphics(j, i);
				Map map = getMap();

				// マップチップからマップグラフィクスの位置を取得
				int xx = toDotUnit(graphics % map.getCellCount());
				int yy = toDotUnit(graphics / map.getCellCount());

				// マップ描画位置
				int dspX = toDotUnit(j);
				int dspY = toDotUnit(i);

				g.drawImage(map.getImage(), dspX, dspY, dspX + map.getChipSize(), dspY + map.getChipSize(), xx, yy, xx + map.getChipSize(), yy + map.getChipSize(), this);
			}
		}
	}
}
