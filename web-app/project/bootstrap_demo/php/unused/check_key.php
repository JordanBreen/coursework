<?php
require_once('key.php');
function check_key() {
	$key = $_GET['key'];
	return ($key===KEY) 
	or die("Invalid key '$key', Access Denied");
}
?>