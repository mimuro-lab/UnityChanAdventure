# StartDxGame
&emsp;このプロジェクトはVisual Studio2019でDxlibを用いてゲームを作成したいときに便利なブランチである。
ソースコードの構成は[龍神録2プログラミングの館 第４章](https://dixq.net/rp2/04.html)を参考にしている。

# ソリューション名の変更方法
&emsp;これを使用するにあたってソリューション名を変更したい場合があると想定される。以下にソリューション名の変更手順を示しておく。
（参考：[http://masatoy.hatenablog.jp/entry/2017/05/09/235033](http://masatoy.hatenablog.jp/entry/2017/05/09/235033)

1,　visual studio上のソリューションエクスプローラーからソリューション名とプロジェクト名を任意の名前に変更;
2,　ソリューションエクスプローラーのフォルダビューを.slnからStartDxGameに変更;
3,　StartDxGame.vcxproj、StartDxGame.vcxproj.filters、StartDxGame.vcxproj.userを拡張子を変えずに任意の名前に変更;

例：
|変更前|変更後|
|------|------|
|StartDxGame.vcxproj|new.vcxproj|
|StartDxGame.vcxproj.filters|new.vcxproj.filters|
|StartDxGame.vcxproj.user|new.vcxproj.user|

