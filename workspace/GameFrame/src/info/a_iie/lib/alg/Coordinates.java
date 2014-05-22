package info.a_iie.lib.alg;


/**
 * 座標計算クラス
 * @author azusa nakano
 */
public class Coordinates {

	/**
	 * 開始点計算
	 * @param xx 基点座標
	 * @param width 幅
	 * @return 開始点
	 */
	public static float calcStart(float xx, float width) {
		return (xx - (width / 2.0f));
	}

	/**
	 * 終了点計算
	 * @param xx 基点座標
	 * @param width 幅
	 * @return 終了点
	 */
	public static float calcEnd(float xx, float width) {
		return (xx + (width / 2.0f));
	}

	/**
	 * 画面中央描画開始点計算
	 * @param ww ウィンドウ幅
	 * @param width オブジェクト幅
	 * @return 描画開始点
	 */
	public static float calcCenterDrawStart(int ww, float width) {
		return (ww / 2.0f - width);
	}

	/**
	 * 画面中央描画終了点計算
	 * @param ww ウィンドウ幅
	 * @param width オブジェクト幅
	 * @return 描画終了点
	 */
	public static float calcCenterDrawEnd(int ww, float width) {
		return (ww / 2.0f + width);
	}
}
