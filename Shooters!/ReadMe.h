/*

これは定義やルールを書き込んでいくファイルです。
　参考：https://oxynotes.com/?p=8679
　↑たまに英語の発音がやばい(result＝レゾルト)

☆ファイル名
・最初は大文字(例：Sound.cpp, Sound.h)

☆変数名
・基本はスネーク記法で単語の区切り部分にアンダースコアを入れる(例:enemy_list)

☆関数名
・get, set, add, register(rgtr)等は小文字で2文字目からキャメル記法で記載する(例：addSoundList) 
・可能か、存在するか等はis～と記載する(isDead, isValid)

☆定数名
・1文字目からキャメル記法

☆マクロ定義
・全て大文字

☆列挙体
・列挙体自体の定義はen～
・Skill⇒sk～, ItemType⇒it～


◎対義語表
Begin ⇔ End
Start ⇔ Stop
Top ⇔ Bottom
High ⇔ Low
Big ⇔ Small
Create ⇔ Destroy
Previous ⇔ Next
Allocate ⇔ Free
Attach ⇔ Detach
Get ⇔ Set
Get ⇔ Put
Input ⇔ Output
Show ⇔ Hide
Go ⇔ Back
Up ⇔ Down
Upper ⇔ Lower


◎クラスの構造
・オブジェクトクラス
	当たり判定用の抽象クラス
	必要な要素
	pos(中央にするか左上にするか)
	width(円形ならrangeから自動算出)
	hegith
	box_flag(長方形でも正常に空間に登録できるのだろうか)

・プレイヤークラス：オブジェクト
	シューターネーム：shooter_name(参照だけなのでプレイヤー自体が持つ必要なし)
	//ショットタイプ：shot_type(これを元にいろいろ弄るのでプレイヤーが所持)
	ウェポンクラス：ショットタイプの別名称
	ショット：list<Shot>shots(ショットの派生クラスあり。変えるのはあくまでショットの挙動のみ)

・ショットクラス：オブジェクト

・ウェポンクラス
	ショットを作るクラス
*/