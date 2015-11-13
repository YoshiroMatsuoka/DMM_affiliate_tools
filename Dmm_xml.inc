<?php

require_once "Isbn_Tools.inc";

//Enter your IDs

define("ApiUrls","***");
define("Access_Key_ID", "**********");
define("Associate_tag", "**********");

/*
 *DMMから作者名などをキーに情報を得るクラス 書籍限定
 */
class Dmm_xml {
	var $obj;
	var $Request;

	function __construct($keyword) {
		if(count($keyword) == 0) {
			echo "error";
			exit;
		}
		//$isbn = Isbn_Tools::ISBN13to10($isbn);
		$this->obj = $this->ApiSearch($keyword);
	}

	function ApiSearch($keyword){
		//Define the request
		$params = array();
		$params['api_id'] = Access_Key_ID;
		$params['affiliate_id'] = Associate_tag;

		$params['operation'] = "ItemList";
		$params['version'] = "2.00";
		$params['timestamp'] = urlencode(gmdate('Y-m-d\TH:i:s\Z'));
		$params['site']      = "DMM.co.jp";
		$params['service'] = "book";
		$params['floor']   = "book";

		$params['keyword'] = urlencode($keyword);

		// URL を作成します
		$strings_arr = array();
		foreach($params as $k => $v)  {
			if($v != "" && $k != "") {
				$strings_arr[] = $k."=".$v;		
			}
		}
		$canonical_string = join('&',$strings_arr);

		$request = ApiUrls.'?'.$canonical_string;

		$this->Request = $request;

		$response = file_get_contents($request);
		return $parsed_xml = simplexml_load_string($response);
	}

	function getRequestSQL() {
		return $this->Request;
	}

	public function get_data() {
		$count = count($this->obj->result->items->item);

		$output = array();
		for ($i=0;$i<$count;$i++) {
			$output[$i] = $this->obj2arr($this->obj->result->items->item[$i]);
		}
		return $output;
	}

	public function obj2arr($obj) {
		if (!is_object($obj)) {
			if(!is_array($obj)) {
				return $obj;
			} else {
				$arr = $obj;
			}
		} else {
			$arr = (array) $obj;
		}

		foreach ( $arr as &$a ) {
			$a = $this->obj2arr($a);
		}
		return $arr;
	}

	public function view_request() {
		return $this->Request;
	}

}
/*
$DMM = new Dmm_xml($_GET['isbn']);
$DMM = new Dmm_xml('アンスリウム');
var_dump($DMM);
 */

?>
