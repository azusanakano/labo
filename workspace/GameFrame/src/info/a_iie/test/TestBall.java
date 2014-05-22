package info.a_iie.test;

import info.a_iie.ImageMoveComponent;
import info.a_iie.lib.map.Map;
import info.a_iie.lib.map.obj.MapCenterMoveObject;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.KeyEvent;
import java.io.IOException;


public class TestBall extends MapCenterMoveObject {

	public TestBall(int width, int height, Map map) {
		super(width, height, map);
		try {
			this.loadImage("chara13.gif");
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		setX(20.0f);
		setY(20.0f);
		setSpeed(50);
		setWidth(width * map.getChipSize());
		setHight(height * map.getChipSize());
		setDir(ImageMoveComponent.RIGHT);
		setMoveKeyEnable(true);

		this.addRunListener();
		this.addGameKeyEventListener();
	}

	/**
	 * 描画処理
	 */
	public void paint(Graphics gb, Graphics g) {
		super.paint(gb, g);
		gb.setColor(Color.white);
		gb.drawString("動いてるよー。現在の座標は(" +(int)getX()+ "," +(int)getY()+ ")。", 20, 20);
	}

	@Override
	public void action() {
		super.action();
		/*
		switch (getDir()) {
			case UP:
				if (moveUp()) {
					setDir(RIGHT);
				}
				break;
			case DOWN:
				if (moveDown()) {
					setDir(LEFT);
				}
				break;
			case LEFT:
				if (moveLeft()) {
					setDir(UP);
				}
				break;
			case RIGHT:
				if (moveRight()) {
					setDir(DOWN);
				}
				break;
		}
		*/
	}

	public void onKeyPressed(KeyEvent e) {
		if (e.getKeyCode() == KeyEvent.VK_Z) {
			this.switchShow();
		}
	}
}
