<?php
require_once('check_auth.php');
require_once('check_key.php');
function drop_table($table_name) {
	session_start();
	check_key();
	//check_auth();
	$mysqli = db_connect();
	$sql = "DROP TABLE $table_name;";
	$mysqli->query($sql) or die("Error ($mysqli->errno) $mysqli->error");
	$mysqli->close();
}
?>