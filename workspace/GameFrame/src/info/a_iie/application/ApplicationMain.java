package info.a_iie.application;

import info.a_iie.GameComponent;
import info.a_iie.lib.map.Map;
import info.a_iie.lib.map.MapCell;
import info.a_iie.lib.map.MapManager;
import info.a_iie.lib.map.camera.CenterMapCamera;
import info.a_iie.lib.map.camera.MapCamera;
import info.a_iie.test.TestBall;

import java.awt.Graphics;
import java.io.IOException;

/**
 * ゲーム・アプリケーションメイン
 */
public class ApplicationMain extends GameComponent {

	private int mapID = 0;
	private Map map = MapManager.getMap(0);

	private TestBall ball = null;
	private MapCamera mapCamera = null;

	public ApplicationMain() {

		map = MapManager.createMapInstance("map00.dat", 20, 15, 32, 0);

		map.addCell(new MapCell(0, 0, false)); // 草原
		map.addCell(new MapCell(1, 0, true)); // 芝生A
		map.addCell(new MapCell(2, 0, true)); // 芝生B
		map.addCell(new MapCell(3, 0, false)); // 家
		map.addCell(new MapCell(4, 0, false)); // 木A

		map.addCell(new MapCell(5, 0, true)); // 木B
		map.addCell(new MapCell(6, 1, true)); // 城
		map.addCell(new MapCell(7, 2, true)); // 海
		map.addCell(new MapCell(8, 3, true)); // 塔の上
		map.addCell(new MapCell(9, 4, true)); // 塔の下

		map.addCell(new MapCell(10, 0, true)); // 洞窟
		map.addCell(new MapCell(11, 0, true)); // 岩山
		map.addCell(new MapCell(12, 5, true)); // 宇宙A
		map.addCell(new MapCell(13, 5, true)); // 宇宙B
		map.addCell(new MapCell(14, 5, true)); // クリスタル

		try {
			map.loadImage("map_chip.gif");
			addImage(map.getImage(), 0);
		} catch (IOException e) {
			e.printStackTrace();
		}
		waitForAll();

		addRunListener();

		mapCamera = new CenterMapCamera(3, 3, map);
		mapCamera.setSpeed(512);
		mapCamera.addRunListener();
		mapCamera.addGameKeyEventListener();
		mapCamera.setX(4 * 32);
		mapCamera.setY(6 * 32);

		ball = new TestBall(1, 1, map);
		ball.setSpeed(512);
		ball.setX(4 * 32);
		ball.setY(6 * 32);

		mapCamera.setCenterObject(ball);

		ga.setSize(496, 678);

	}

	@Override
	public void action() {
		// TODO 自動生成されたメソッド・スタブ

	}

	@Override
	public void paint(Graphics gbuffer, Graphics g) {
		// TODO 自動生成されたメソッド・スタブ

		/*
		for (int i = 0; i < map.getWidth(); i++) {
			for (int j = 0; j < map.getHeight(); j++) {
				int cellData = map.getMapData()[i][j];
				int grahics = map.getCellArray()[cellData].getGraphic();

				int x = (grahics % 16) * 32;
				int y = (grahics / 16) * 32;

				gbuffer.drawImage(map.getImage(), j * 32, i * 32, (j + 1) * 32, (i + 1) * 32, x, y, x + 32, y + 32, this);
			}
		}
		*/

		//System.out.println(ga.getParent().getWidth() + "," + ga.getParent().getHeight());

	}



}
