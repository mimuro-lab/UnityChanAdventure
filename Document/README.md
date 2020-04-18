# Doxygenの設定
[最近覚えた便利アプリ[doxygen]](https://qiita.com/wakaba130/items/faa6671bd5c954cb2d02#%E4%BD%BF%E3%81%84%E6%96%B9doxygen%E5%AE%9F%E8%A1%8C%E7%B7%A8)を参考にしている。

１、Step1の出力するドキュメントの置き場所を設定する。

２、Wizeard/Projectウィンドウでそのドキュメントの名前を入力し、ドキュメントを生成したい対象のソースコードがあるディレクトリを参照する。

３、Export/ProjectウィンドウでOUTPUT_LANGUAGEをJapaneseにし、Export/InputウィンドウでINPUT_ENCODINGをCP932に変更する。
また、Export/buildウィンドウでEXTRACT_PRIVATEにチェックを入れる（privateなメンバも出力する為）


４、RunウィンドウのRun doxygenをクリックする。

## Graphvizの設定
[Doxygen+Graphvizでクラス図を自動生成する](http://gomi-box.hatenablog.com/entry/20090209/1234193014)を参考にしている。

１、Graphvizを[公式ページ](https://graphviz.gitlab.io/download/)ダウンロードする。(WindowsのStable X.XX Windows install packagesからダウンロードする)

２、Doxygenを立ち上げ、ExportウィンドウのDotのHAVE_DOTにチェックする。

３、DOT_PATHをインストールしたGraphvizのbinフォルダに設定する。_