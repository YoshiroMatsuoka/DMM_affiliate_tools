# DMM_affiliate_tools

DMMアフィリエイトを利用するための簡易クラスです。
利用用途的に書籍に限定していますが、改造でどうとでもなるかと。

書籍名や作者名などを引数に呼び出してやると
該当する書籍に関する情報群が配列に入って戻ってきます。

各define値に関しては、
利用時にご自分で取得してください。

〇ファイル構成
●Dmm_xml.php
 本体クラス。

 利用方法はこんな感じ。

$DMM = new Dmm_xml('書籍名');

//DMM APIへ対する生の呼び出しクエリ
echo $DMM->view_request();

●Isbn_Tools.inc
ISBNコードの10桁 13桁の相互変換関数。

//13桁を10桁に
function ISBN13to10($isbn)

//10桁を13桁に
function ISBN10to13($isbn)

