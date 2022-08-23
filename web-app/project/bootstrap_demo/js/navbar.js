// creates a navbar for home.html and about.html, author: Jordan Breen
$(document).ready(function() {
	let output = `
	<nav class='navbar navbar-expand-sm navbar-dark bg-dark'>
		<div class='container-fluid'>
			<a class='navbar-brand' href='home.html'>Mock Website</a>
			<ul class='navbar-nav'>
				<li class='nav-item active'>
					<a class='nav-link' href='home.html'>Home</a>
				</li>
				<li class='nav-item'>
					<a class='nav-link' href='about.html'>About</a>
				</li>
			</ul>`;
	if (!sessionStorage.getItem('authenticated')) {
		output += `
		<ul class='navbar-nav float-end'>
			<li class='nav-item'>
				<button type='button' class='btn btn-dark' data-bs-toggle='modal' data-bs-target='#login-modal'><i class='bi-person-fill'></i> Login</button>
			</li>
		</ul>`;
	}
	else {
		output += `
		<ul class='navbar-nav float-end'>
			<li class='nav-item'>
				<button type='button' class='btn btn-dark'><i class='bi-person-circle'></i> Account</button>
			</li>
		</ul>`;
	}
	output += `
		</div>
	</nav>`;
	if (!sessionStorage.getItem('authenticated')) {
		output += `
		<div class='modal fade' id='login-modal' role='dialog'>
			<div class='modal-dialog'>
				<div class='modal-content bg-light bg-gradient'>
					<div class='modal-header'>
						<h4 style='color:red;'><i class='bi-lock'></i> Login</h4>
						<button type='button' class='close btn' data-bs-dismiss='modal'><i class='bi-x-lg'></i></button>
					</div>
					<div class='modal-body'>
						<form role='form' method='POST' action='#'<!--'./php/sign_in.php'--> target='_self'>
							<div class='form-group'>
								<label for='username'><i class='bi-person'></i> Username</label>
								<input type='text' class='form-control' id='username' name='username' required>
							</div>
							<div class='form-group'>
								<label for='password'><i class='bi-eye-fill'></i> Password</label>
								<input type='password' class='form-control' id='password' name='password' required>
							</div>
							<div class='checkbox'>
								<input class='form-check-input' input type='checkbox' value='' id='remember_me' name='remember_me' checked>
								<label class='form-check-label' for='remember_me'>Remember me</label>
							</div>
							<button type='submit' name='action' class='btn btn-success float-end'>Login</button>
						</form>
					</div>
					<div class='modal-footer justify-content-between'>
						<p>Not a member? <a href='./php/sign_up.php'>Sign Up</a></p>
						<p>Forgot <a href='./php/recover_password.php'>Password?</a></p>
					</div>
				</div>
			</div>
		</div>`;
	}
	$('header').html(output);
});
