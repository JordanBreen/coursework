<?php
require_once('./constants/website.php');
?>
<!DOCTYPE html>
<html lang="en">
	<head>
	  <title><?php echo "$WEBSITE_NAME";?>: Home</title>
	  <meta charset="utf-8">
	  <meta name="viewport" content="width=device-width, initial-scale=1">
	  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
	  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
	  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script>
	</head>
	<body>
		<header>
			<nav class="navbar navbar-inverse">
				<div class="container-fluid">
					<div class="navbar-header">
						<a class="navbar-brand" href="home.php"><?php echo "$WEBSITE_NAME";?></a>
					</div>
					<ul class="nav navbar-nav navbar-left">
						<li class="nav-item active">
							<a class="nav-link" href="home.php">Home</a></li>
						<li class="nav-item">
							<a class="nav-link" href="about.php">About</a>
						</li>
					</ul>
					<ul class="nav navbar-nav navbar-right">
						<li class="nav-item dropdown">
							<a class="dropdown-toggle" data-toggle="dropdown">Sign-in<span class="caret"></span></a>
							<ul class="dropdown-menu">
								<li><a class="btn" href="./sign-in.php" target="_self">Sign-in</a></li>
								<li><span>New to <?php echo "$WEBSITE_NAME";?>? <a href="./create_account.php" target="_self">Start here.</a></span></li>
							</ul>
						</li>
					</ul>
				</div>
			</nav>
		</header>
		<main>
			<div class="container page-header">
				<h1>Welcome to <?php echo "$WEBSITE_NAME";?>!</h1><small>Subtext</small>
			</div>
			<div class="container">
				<p>This is our homepage!</p>
			</div>
		</main>
	</body>
</html>
