#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetCircleResolution(64);
    ofSetFrameRate(120);
    ofEnableAlphaBlending();
    
    player_y = ofGetHeight();
    player_height = 20;
    
    shot_bullet_width = 1;
    shot_bullet_height = 5;
    num_shot = 0;
    for (int i = 0; i < NUM_BULLET_SHOT; i++) {
        shot_bullet_y[i] = ofGetHeight();
        shot_bullet_dy[i] = 0;
        shot_bullet[i] = false;
    }
    
    bullet_x = 300;
    bullet_y = 300;
    bullet_r = 10;
    
    block_width = ofGetWidth() / BLOCK_NUM_X;
    block_height = 200 / BLOCK_NUM_Y;
    
    for (int i = 0; i < BLOCK_NUM_X; i++) {
        for (int j = 0; j < BLOCK_NUM_Y; j++) {
            isSurvival[i][j] = true;
        }
    }
    
    isStarting = true;
    isPlaying = true;
    isFinished = false;
    
    level = 1;
    life = 3;
    
    score = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    if (isStarting == true) {
        
        if (level == 1) player_width = 200;
        else if (level == 2) player_width = 150;
        else player_width = 50 + 150 / level;
        
        bullet_x = 300;
        bullet_y = 300;
        bullet_dx = 6 + level;
        bullet_dy = 6 + level;
        for (int i = 0; i < BLOCK_NUM_X; i++) {
            for (int j = 0; j < BLOCK_NUM_Y; j++) {
                if (isSurvival[i][j] == true) {
                    block[i][j][0] = i * ofGetWidth() / BLOCK_NUM_X;
                    block[i][j][1] = j * 200 / BLOCK_NUM_Y;
                    block_color[i][j].set(ofRandom(180,255), ofRandom(180,255), ofRandom(180,255));
                }
            }
        }
        isStarting = false;
    }
    
    if (isPlaying == true) {
        bullet_x += bullet_dx;
        bullet_y += bullet_dy;
        if (bullet_x > ofGetWidth() || bullet_x < 0) bullet_dx = -bullet_dx;
        if (bullet_y < 0) bullet_dy = -bullet_dy;
        if (bullet_y + bullet_r > ofGetHeight()) isPlaying = false;
        if ((bullet_y + bullet_r > player_y - player_height) && (bullet_x >= player_x - player_width / 2) && (bullet_x <= player_x + player_width / 2)) {
            float reflection_random = ofRandom(100);
            if (reflection_random < 90) {
                bullet_dy = -bullet_dy * ofRandom(0.9, 1.1);
            } else {
                bullet_dy *= -1.1;
                bullet_dx = -bullet_dx;
            }
        }
    }
    
    rest = 50;
    for (int i = 0; i < BLOCK_NUM_X; i++) {
        for (int j = 0; j < BLOCK_NUM_Y; j++) {
            if ((bullet_x >= block[i][j][0]) && (bullet_x <= block[i][j][0] + block_width) && (bullet_y - bullet_r < block[i][j][1] + block_height) && (bullet_y + bullet_r > block[i][j][1] + block_height)) {
                bullet_dy = -bullet_dy;
                isSurvival[i][j] = false;
                block[i][j][0] = -1000;
                block[i][j][1] = -1000;
            } else if ((bullet_x - bullet_r < block[i][j][0] + block_width) && (bullet_x + bullet_r > block[i][j][0] + block_width) && (bullet_y > block[i][j][1]) && (bullet_y < block[i][j][1] + block_height)) {
                bullet_dx = -bullet_dx;
                isSurvival[i][j] = false;
                block[i][j][0] = -1000;
                block[i][j][1] = -1000;
            } else if ((bullet_x > block[i][j][0]) && (bullet_x <= block[i][j][0] + block_width) && (bullet_y + bullet_r > block[i][j][1]) && (bullet_y - bullet_r < block[i][j][1])) {
                bullet_dy = -bullet_dy;
                isSurvival[i][j] = false;
                block[i][j][0] = -1000;
                block[i][j][1] = -1000;
            } else if ((bullet_x + bullet_r > block[i][j][0]) && (bullet_x - bullet_r < block[i][j][0]) && (bullet_y > block[i][j][1]) && (bullet_y < block[i][j][1] + block_height)) {
                bullet_dx = -bullet_dx;
                isSurvival[i][j] = false;
                block[i][j][0] = -1000;
                block[i][j][1] = -1000;
            }
            if (isSurvival[i][j] == false) rest--;
        }
    }
    
    score = level * 50 - rest;
    
    if (rest == 0) {
        isPlaying = false;
        isFinished = true;
        for (int i = 0; i < BLOCK_NUM_X; i++) {
            for (int j = 0; j < BLOCK_NUM_Y; j++) {
                isSurvival[i][j] = true;
            }
        }
        rest = 0;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    if (isPlaying == true && isFinished == false) {
        ofDrawBitmapString("level : " + ofToString(level), 300, 280);
        ofDrawBitmapString("score : " + ofToString(score), 300, 300);
        ofDrawBitmapString("life : " + ofToString(life), 300, 320);
    } else if (isPlaying == false && isFinished == false) {
        if (life == 0) ofDrawBitmapString("GameOver", 400, 400);
        else ofDrawBitmapString("Do you want to restart ?", 400, 400);
    } else if (isPlaying == false && isFinished == true) {
        ofDrawBitmapString("Finished!", 400, 400);
    }
    
    ofSetColor(255, 0, 0);
    ofDrawRectangle(player_x - player_width / 2, player_y - player_height / 2, player_width, player_height);
    ofSetColor(0, 0, 255);
    ofDrawCircle(bullet_x, bullet_y, bullet_r);
    for (int i = 0; i < BLOCK_NUM_X; i++) {
        for (int j = 0; j < BLOCK_NUM_Y; j++) {
            if (isSurvival[i][j] == true) {
                ofSetColor(block_color[i][j]);
                ofDrawRectangle(block[i][j][0], block[i][j][1], block_width, block_height);
            }
        }
    }
    
    for (int i = 0; i < NUM_BULLET_SHOT; i++) {
        ofSetColor(255);
        ofDrawRectangle(shot_bullet_x[i], shot_bullet_y[i] - 10 * i, shot_bullet_width, shot_bullet_height);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (life != 0) {
        if (key == 's') {
            if (isFinished == true) {
                level++;
                if (level >= 2) {
                    life++;
                }
            }
            if (isFinished == false && isPlaying == false) {
                life--;
            }
            isStarting = true;
            isPlaying = true;
            isFinished = false;
        }
    } else if (life == 0) {
        if (key == 's') {
            if (isFinished == true) {
                level++;
                if (level >= 2) {   //レベルが上がるごとにライフ追加
                    life++;
                }
            }
        }
    }
    if (key == 'b') {
        if (num_shot <= 9) {
            shot_bullet[num_shot] = true;
            num_shot++;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    player_x = x;
    //player_y = y;
    for (int num_shot = 0; num_shot < NUM_BULLET_SHOT; num_shot++) {
        if (shot_bullet[num_shot] == false) shot_bullet_x[num_shot] = x;
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
