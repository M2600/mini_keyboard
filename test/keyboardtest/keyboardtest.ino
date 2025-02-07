
void setup() {
    pinMode(9, OUTPUT);
    pinMode(6, INPUT_PULLUP);
    // VCCピンの代わりにデジタルピンを電圧高に
    digitalWrite(9, HIGH);
}

void loop() {
    // プルアップの場合はスイッチが押された時にLOWになる
    if (digitalRead(6) == LOW){
        // ボタンが押されたときの処理
    }
}
