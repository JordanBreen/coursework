<?php
	require_once('./php/website.php');
?>
<!DOCTYPE html>
<html>
	<head>
		<title><?php echo Website::NAME ?>: About</title>
		<meta charset="UTF-8">
		<meta name="viewport" content="width=device-width, initial-scale=1">
		<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet">
		<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js"></script>
		<script src="./scripts/navbar.js" defer></script>
	</head>
	<body id="about_body" name="about_body">
		<header>
		</header>
		<main id="about_main" name="about_main">
			<p id="summary" name="summary"></p>
			<p id="credit_to_author" name="credit_to_author">
				Made by, <?php 
					foreach(Website::AUTHORS as $author_name)
						echo "<span name='author'>$author_name </span>";
				?>
				<span id="publish_year" name="publish_year">2022</span>
			</p>
		</main>
	</body>
</html>