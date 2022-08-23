<?php
require_once('check_auth.php');
require_once('check_key.php');
require_once('db_connect.php');
function show_table(string $table_name): void {
	session_start();
	check_key();
	//check_auth();
	$mysqli = db_connect();
	$result = $mysqli->query("SHOW COLUMNS FROM $table_name");
	echo "<!DOCTYPE html>";
	echo "<html>";
	echo  "<head>";
	echo    "<title>Show table</title>";
	echo    "<meta charset='utf-8'>";
	echo    "<meta name='viewport' content='width=device-width, initial-scale=1'>";
	echo    "<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css'>";
	echo    "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js'></script>";
	echo    "<script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js'></script>";
	echo  "</head>";
	echo  "<body>";
	echo    "<div class='container'>";
	echo 		"<h3 class='text-center'>table: $table_name</h3>";
	echo 		"<table class='table table-bordered'>";
	echo			"<thead>";
	echo				"<tr>";
	while($row=$result->fetch_row()) 
		echo "<th>".$row[0]."</th>";
	echo "</tr></thead><tbody>";
	$result->close();
	$result = $mysqli->query("SELECT * FROM $table_name");
	while($row=$result->fetch_row()){
		echo '<tr>';
		foreach ($row as $value)
			echo '<td>'.$value.'</td>';
		echo '</tr>';
	}
	echo "</tbody></table></div></body></html>";
	$result->close();
	$mysqli->close();
}
?>