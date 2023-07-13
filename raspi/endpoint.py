# サーバーには flask を使用

from flask import Flask
import serial
import time

app = Flask(__name__)

# Arduinoとのシリアル通信の設定
ser = serial.Serial("/dev/ttyACM0", 9600)  # シリアルポートとボーレート

ser.isOpen()  # シリアルポートを開く
time.sleep(2)  # Arduinoがリセットするのを待つ?


# Arduino は rotate を意味する'r'を受信するとサーボを回転させる
# 'r' を送信する関数
def send():
    ser.write(b"r")  # 'r' をバイト列として送信
    print("Signal sent: r")


@app.route("/send_signal", methods=["POST"])
def send_signal():
    try:
        # 'r' を送信
        send()
    except Exception as e:
        return f"Error: {str(e)}", 500

    return "Signal sent: r"


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
