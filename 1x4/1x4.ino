#include <HID-Project.h>

// 使用するピンの定義
#define PIN_A 20
#define PIN_1 18
#define PIN_2 22
#define PIN_3 5
#define PIN_4 3

// ROWピンのリスト
const int ROW[] = {PIN_1, PIN_2, PIN_3, PIN_4};
// COLピンのリスト
const int COL[] = {PIN_A};

// キーマップの定義
KeyboardKeycode KEYMAP[sizeof(ROW)/sizeof(ROW[0])][sizeof(COL)/sizeof(COL[0])] = {
    {KEY_A},{KEY_B},{KEY_C},{KEY_D}
};

// キーの状態を保持する2次元配列
bool keyState[sizeof(ROW)/sizeof(ROW[0])][sizeof(COL)/sizeof(COL[0])];
// 前回のキーの状態を保持する2次元配列
bool prevState[sizeof(ROW)/sizeof(ROW[0])][sizeof(COL)/sizeof(COL[0])];

void setup(){
    // ピンの初期化
    // ROWピンを出力に設定し、HIGHにする
    for (int i=0; i<sizeof(ROW)/sizeof(ROW[0]); i++){
        pinMode(ROW[i], OUTPUT);
        digitalWrite(ROW[i], HIGH);
    }
    // COLピンをINPUT_PULLUPに設定
    for (int i=0; i<sizeof(COL)/sizeof(COL[0]); i++){
        pinMode(COL[i], INPUT_PULLUP);
    }

    // keyStateを初期化
    for (int i=0; i<sizeof(ROW)/sizeof(ROW[0]); i++){
        for (int j=0; j<sizeof(COL)/sizeof(COL[0]); j++){
            keyState[i][j] = false;
            prevState[i][j] = false;
        }
    }

    // キーボードの初期動作
    BootKeyboard.begin();
}


void loop(){
    for (int i=0; i<sizeof(ROW)/sizeof(ROW[0]); i++){
        // ROWピンをLOWにする
        digitalWrite(ROW[i], LOW);
        for (int j=0; j<sizeof(COL)/sizeof(COL[0]); j++){
            //キーの状態をkeyStateに保存(押されてる場合はtrue, そうでない場合はfalse)
            keyState[i][j] = digitalRead(COL[j]) == LOW;
            if(keyState[i][j] != prevState[i][j]){
                // キーの状態が変化した場合
                if(keyState[i][j]){
                    // キーが押された場合
                    BootKeyboard.press(KEYMAP[i][j]);
                }else{
                    // キーが離された場合
                    BootKeyboard.release(KEYMAP[i][j]);
                }
            }
            // 現在のキーの状態をprevStateに保存
            prevState[i][j] = keyState[i][j];
        }
        // ROWピンをHIGHに戻す
        digitalWrite(ROW[i], HIGH);
    }
}