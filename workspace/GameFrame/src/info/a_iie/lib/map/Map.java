package info.a_iie.lib.map;

import info.a_iie.ImageGameComponent;

import java.awt.Graphics;
import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;

/**
 * マップデータ
 * @author azusa nakano
 */
public class Map extends ImageGameComponent {

	private ArrayList<MapCell> cell = new ArrayList<MapCell>();
	private int[][] mapData = null;
	private int maxCellGraphics = 0;	// このマップのセルのグラフィック最大番号
	private int chipSize = 0;


	/**
	 * コンストラクタ
	 *
	 * @param filename ファイルパス
	 * @param width マップ幅(セル単位)
	 * @param height マップ高さ(セル単位)
	 * @param chipSize 1マスサイズ
	 */
	public Map(String filename, int width, int height, int chipsize) {
		readDataFile(filename, width, height, chipsize);
	}

	/**
	 * セル追加
	 * @param c マップセルデータ
	 * @return
	 */
	public boolean addCell(MapCell c) {
		if (c.getGraphic() > maxCellGraphics) {
			maxCellGraphics = c.getGraphic();
		}
		return cell.add(c);
	}

	/**
	 * このマップのセルのグラフィック最大番号取得
	 * @return このマップのセルのグラフィック最大番号
	 */
	public int getMaxCellGraphics() {
		return maxCellGraphics;
	}

	/**
	 * 登録セル数取得
	 * @return 登録セル数
	 */
	public int getCellCount() {
		return cell.size();
	}

	/**
	 * 配列取得
	 * @return マップ配列
	 */
	public MapCell[] getCellArray() {
		MapCell[] r = new MapCell[cell.size()];
		return (MapCell[])cell.toArray(r);
	}

	/**
	 * 幅取得(セル単位）
	 * @return 幅（セル単位）
	 */
	public int getCellWidth() {
		return (int)getWidth() / getChipSize();
	}

	/**
	 * 高さ取得（セル単位）
	 * @return 高さ（セル単位）
	 */
	public int getCellHeight() {
		return (int)getHeight() / getChipSize();
	}

	/**
	 * マップデータ取得
	 * @return マップデータ
	 */
	public int[][] getMapData() {
		return mapData;
	}

	/**
	 * データファイル読み込み
	 *
	 * @param filename ファイルパス
	 * @param width マップ幅(セル単位)
	 * @param height マップ高さ(セル単位)
	 * @param chipSize 1マスサイズ
	 */
	public void readDataFile(String filename, int width, int height, int chipSize) {
		int x;
		int y;
		int i;

		this.chipSize = chipSize;
		setWidth(width * getChipSize());
		setHight(height * getChipSize());

		mapData = new int[width][height];

		try {
			InputStream is = new BufferedInputStream(new FileInputStream(new File(filename)));

			x = 0;
			y = 0;
			while ((i = is.read()) !=  -1) {
				mapData[x][y] = i;
				x++;
				if (x == width) {
					y++;
					x = 0;

					if (y == height) {
						break;
					}
				}
			}

			is.close();

		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	/**
	 * グラフィックデータ取得
	 * @param x X座標
	 * @param y Y座標
	 * @return グラフィックデータ
	 */
	public int getGraphics(int x, int y) {
		return this.getCellArray()[this.getMapData()[x][y]].getGraphic();
	}

	/**
	 * 1マスサイズ取得
	 * @return 1マスサイズ
	 */
	public int getChipSize() {
		return chipSize;
	}

	@Override
	public void action() {
		// 何もしない
	}

	@Override
	public void paint(Graphics gbuffer, Graphics g) {
		// 何もしない
	}
}
