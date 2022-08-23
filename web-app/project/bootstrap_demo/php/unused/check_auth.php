<?php
function check_auth() {
	if ($_SESSION['authenticated'] != true) {
		echo "<p><a href='login.php'>Login</a></p>";
		die("Access denied");
	}
}
?>