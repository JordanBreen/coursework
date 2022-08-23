<?php
require_once('check_key.php');
require_once('db_connect.php');
function create_table(string $table_name = NULL, string ...$fields) {
	session_start();
	check_key();
	//check_auth();
	$table_name or die ("Error, must have table name");
	$mysqli = db_connect();
	$sql = "
		CREATE TABLE $table_name (".implode(', ', $fields).");
	";
	$mysqli->query($sql) or die("Error ($mysqli->errno) $mysqli->error");
	$mysqli->close();
}
?>