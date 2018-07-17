#pragma once

#include "ofMain.h"

#define BULLET_NUM 10
#define BLOCK_NUM_X 10
#define BLOCK_NUM_Y 5

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        float player_x;   //プレイヤーのx座標
        float player_y;   //プレイヤーのy座標
        float player_width;   //プレイヤーの横幅
        float player_height;   //プレイヤーの縦幅
        float bullet_x;   //弾のx座標
        float bullet_y;   //弾のy座標
        float bullet_dx;   //弾のx座標変化量
        float bullet_dy;   //弾のy座標変化量
        float bullet_r;   //弾の半径
        float block[BLOCK_NUM_X][BLOCK_NUM_Y][2];   //ブロックの座標
        float block_width;   //ブロックの横幅
        float block_height;   //ブロックの縦幅
        ofColor block_color[BLOCK_NUM_X][BLOCK_NUM_Y];   //ブロックの色
        bool isSurvival[BLOCK_NUM_X][BLOCK_NUM_Y];
        bool isStarting;
        bool isPlaying;
        bool isFinished;
        int level;
        int rest;
        int life;
        int score;
};
