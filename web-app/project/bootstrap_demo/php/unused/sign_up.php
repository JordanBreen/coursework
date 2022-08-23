<?php
	require_once('./metadata/website.php');
	require_once('./scripts/make_modal.php');
	require_once('./metadata/password.php');
?>
<!DOCTYPE html>
<html lang="en">
	<head>
	  <title><?php echo "$WEBSITE_NAME";?>: Create Account</title>
	  <meta charset="utf-8">
	  <meta name="viewport" content="width=device-width, initial-scale=1">
	  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
	  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
	  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script>
	</head>
	<body>
		<header>
			<div class="container">
				<div class="container text-center">
					<a class="btn" href="home.php"><?php echo "$WEBSITE_NAME";?></a>
				</div>
			</div>
		</header>
		<main>
			<div class="panel panel-default" style="width:50%; margin:auto">
				<div class="panel-heading">
					<h1>Create account</h1>
				</div>
				<div class="panel-body">
					<form action="./scripts/insert_user.php" target="_self">
						<div class="form-group">
							<label for="name_input">Your Name</label><br>
							<input type="text" class="form-control" name="name_input" id="name_input" required>
						</div>
						<div class="form-group">
							<label for="email_input">Email</label><br>
							<input type="email" class="form-control" name="email_input" id="email_input" required>
						</div>
						<div class="form-group">
							<label for="password_input">Password</label><br>
							<input type="password" class="form-control" name="password_input" id="password_input" minlength=<?php echo "$PASSWORD_MIN_LENGTH";?> maxlength=<?php echo "$PASSWORD_MAX_LENGTH";?> required>
							<small id="password_help" class="form-text text-muted">Passwords must be <?php echo "$PASSWORD_MIN_LENGTH - $PASSWORD_MAX_LENGTH";?> characters.</small>
						</div>
						<div class="form-group">
							<label for="re-enter_password_input">Re-enter password</label><br>
							<input type="password" class="form-control" name="re-enter_password_input" id="re-enter_password_input" minlength="6" maxlength="32" required>
						</div>
						<button type="submit" class="btn btn-primary" style="width:100%; margin:auto" name="continue">Continue</button>
					</form>
				</div>
				<div class="panel-footer">
					<br>
					<div class="container-fluid">
						<small>
							<span>By creating an account, you agree to <?php echo "$WEBSITE_NAME";?>'s</span>
							<?php conditions_of_use_modal_link(); ?>
							<span>and</span>
							<?php privacy_notice_modal_link(); ?><span>.</span>
						</small>
					</div>
					<br>
					<div class="container-fluid">
						<small>
							<span>Already have an account? </span>
							<a href="sign-in.php">
								Sign-In <span class="glyphicon glyphicon-triangle-right"></span>
							</a>
						</small>
					</div>
					<br>
				</div>
			</div>
		</main>
		<?php 
			conditions_of_use_modal();
			privacy_notice_modal();
		?>
	</body>
</html>
