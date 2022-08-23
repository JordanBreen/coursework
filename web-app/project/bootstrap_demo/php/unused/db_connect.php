<?php
function db_connect( ) {
	$conn = new mysqli(
		"localhost", 		// $servername
		"sienasel_sbxusr",  // $username
		"Sandbox@)!&",		// $password
		"sienasel_sandbox"	// $dbname
	);
	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	}
	return $conn;
}
?>