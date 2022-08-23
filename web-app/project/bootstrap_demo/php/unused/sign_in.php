<?php 
require_once('./functions/db_connect.php');
session_start();
$error  = false;
if ($_POST['action'] == "Login") {
	$submitted_username = $_POST['username'];
	$submitted_password = $_POST['password'];
	$mysqli = db_connect();
	$sql = "
		SELECT 	password 
		FROM 	placeholder_table_name
		WHERE 	username='$submitted_username'
	";	
	$result = $mysqli->query($sql);
	$row = $result->fetch_row();
	$stored_password = $row[0];
	
	$mysqli->close(); 
	
	if ($stored_password != null && password_verify($submitted_password, $stored_password)) {
	   $_SESSION['authenticated'] = true;
       header("Location: http://www.sienasellbacks.com/jm23bree/bootstrap_demo/home.php");
	   die();
	}
	else {
		 $error = true;
	}
}
?>

<!DOCTYPE html>
<html>
	<head>
		<title>Mock Website - Login</title>
		<meta charset="utf-8">
		<meta name="viewport" content="width=device-width, initial-scale=1">
		<link rel="stylesheet" type="text/css" href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css">
	    <link rel="stylesheet" type="text/css" href="https://cdn.jsdelivr.net/npm/bootstrap-icons@1.8.0/font/bootstrap-icons.css" integrity="sha384-ejwKkLla8gPP8t2u0eQyL0Q/4ItcnyveF505U0NIobD/SMsNyXrLti6CWaD0L52l" crossorigin="anonymous">
		<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js"></script>
		<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
		<script src="./js/navbar.js" async></script>
	</head>
  	<body>
  		<form method="POST" action="sign_in.php">
    		<h2>Login</h2>
    		<label class="form_label">Username: <input class="form_control" type="text"     name="username" required></label>
    		<label class="form_label">Password: <input class="form_control" type="password" name="password" required></label>
    		<input type="submit" name="action" value="Login"> 
    		<? if($error) echo '<p>Login failed</p>'; ?>
  		</form>
	</body>
</html>