package info.a_iie.lib.map;

/**
 * マップ1マスのデータ
 * @author azusa nakano
 */
public class MapCell {

	private int graphic;	// グラフィックデータ
	private int event;		// イベント
	private boolean move;	// 通過可能

	/**
	 * コンストラクタ
	 * @param graphic グラフィックデータ
	 * @param event イベント
	 * @param move 通過可能
	 */
	public MapCell(int graphic, int event, boolean move) {
		this.graphic = graphic;
		this.event = event;
		this.move = move;
	}

	public int getGraphic() {
		return graphic;
	}

	public void setGraphic(int graphic) {
		this.graphic = graphic;
	}

	public int getEvent() {
		return event;
	}

	public void setEvent(int event) {
		this.event = event;
	}

	public boolean isMove() {
		return move;
	}

	public void setMove(boolean move) {
		this.move = move;
	}
}
