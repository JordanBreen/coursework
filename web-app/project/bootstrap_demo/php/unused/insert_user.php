<?php
require_once("functions.php");
check_get_key();
/** PHP POSTBACK INVOKED SECTION **/
if ($_SERVER["REQUEST_METHOD"] == "POST") {
	if ($_POST['action'] == "Insert") {
		$mysqli = db_connect();
		define('USERNAME_INDEX', 0);
        define('PASSWORD_INDEX', 1);

        $input_data = [
            'username_entry' => $_POST['username_entry'],
            'password_entry' => $_POST['password_entry']
        ];
		
		$escaped_values = (array) null;
		// VALIDATE AND ESCAPE THE $_POST DATA ///////
		foreach($input_data as $key => $value)
			if($value === "")
				die("Error: field $key is unfilled");
			else
				$escaped_values[] = $mysqli->real_escape_string($value);
        
        $escaped_values[PASSWORD_INDEX] = password_hash($escaped_values[PASSWORD_INDEX], PASSWORD_BCRYPT);         
        
        // INSERT INTO USER TABLE 29292 //////////////
		$sql = "
			INSERT INTO $USER_TABLE_NAME (user_name, password) 
			VALUES ('".implode("', '", $escaped_values)."');
		";
        // HANDLE QUERY'S RETURN VALUE ///////////////
		$result = $mysqli->query($sql) or die("Error ($mysqli->errno) $mysqli->error");

		// SHOW_DATA SECTION: //
		$border_style = 'style="border:2px solid grey"';
		
		$result = $mysqli->query("SHOW COLUMNS FROM $USER_TABLE_NAME") or die("Error, Could not show columns from $USER_TABLE_NAME: ($mysqli->errno) $mysqli->error");
		while($row = $result->fetch_row())
			echo "<tr $border_style>";;
		echo "<h1>$USER_TABLE_NAME</h1>";
		echo "<table>";
		echo "<tr $border_style>";
		while($row = $result->fetch_row())
			echo "<th $border_style>".$row[0]."</th>";
		echo '</tr>';
		$result->close();

		$result = $mysqli->query("SELECT * FROM $USER_TABLE_NAME") or die("Error, Could not get rows from $USER_TABLE_NAME: ($mysqli->errno) $mysqli->error");
		while($row = $result -> fetch_row()) {
			echo "<tr $border_style>";
			foreach ($row as $value)
				echo "<td $border_style>$value</td>";
			echo '</tr>';
		}
		echo '</table>';
		echo '<p><a href="insert_user.php">Insert another user</a></p>';
		$result->close();
		$mysqli->close();
	}
}
?>

<!-- STATIC HTML SECTION -->
<!DOCTYPE html>
<html lang='en'>
	<head>
        <title>Insert User</title>
		<meta charset='UTF-8'>
		<meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fir=no'>
		<link rel='stylesheet' href='http://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.6/css/bootstrap.min.css'>
	</head>
	<body>
	<?php // GENRATED BEFORE POSTBACK (ON INITIAL LOAD)
	if(!isset($_POST['action'])) {
		echo ("
			<form id='insert_user_form' method='POST' action='insert_user.php' target='_blank'>
				<fieldset form='insert_user_form'>
					<label for='username_entry'>Username
					<br>
					<input  id='username_entry' name='username_entry' class='entry' type='text'>
					</label>
					<br>
					<label for='password_entry'>Password
					<br>
					<input  id='password_entry'  name='password_entry' class='entry' type='password'>
					</label>
					<input type='submit' id='user_insert_btn' name='action' value='Insert'>
				</fieldset>
			</form>
			<script src='https://code.jquery.com/jquery-3.1.1.slim.min.js'></script>
			<script src='https://cdnjs.cloudflare.com/ajax/libs/tether/1.4.0/js/tether.min.js'></script>
			<script src='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.6/js/bootstrap.min.js'></script>
		");
	}
	?>
	</body>
</html>