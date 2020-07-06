<?php
  function get_passwords_from_database (){
  $mysqli = new mysqli ("localhost", "root", "", "space_bd");
  $mysqli->query ("SET NAMES 'utf-8'");
  $tmp_array = $mysqli->query("SELECT * FROM `users`");
  $login_array = array();
  $password_array = array();
  while(($row = $tmp_array->fetch_assoc())!= false) {
  array_push($login_array, $row["login"]);
  array_push($password_array, $row["password"]);
  }
  $mysqli->close();
  return array_combine($login_array,$password_array);
  }

  function authorize_user($login, $password) {
    $login_passwords_array = get_passwords_from_database();
    if (array_key_exists($login, $login_passwords_array)) {
      if($login_passwords_array[$login] === secured_string($password)) {
        echo '<script language="javascript">';
        echo 'alert("Login successfully!")';
        echo '</script>';
        return true;
      }
    }
    echo '<script language="javascript">';
    echo 'alert("Login error")';
    echo '</script>';
    return false;
  }

  function register_user($login, $password) {
      $login_passwords_array = get_passwords_from_database();
      if (array_key_exists($login, $login_passwords_array)) {
        echo '<script language="javascript">';
        echo 'alert("User alsready exist")';
        echo '</script>';
        return false;
      }
      if (strlen($password) < 5) {
        echo '<script language="javascript">';
        echo 'alert("Password to short")';
        echo '</script>';
        return false;
      }
      if(preg_match("/@/", $password)) {
        echo '<script language="javascript">';
        echo 'alert("Unallowed characters on password")';
        echo '</script>';
         return false;
      }
      $login_passwords_array[$login] = secured_string($password);

      $mysqli = new mysqli ("localhost", "root", "", "space_bd");
      $mysqli->query ("SET NAMES 'utf-8'");
      $tmp_array = $mysqli->query("INSERT INTO `users` (`login`, `password`, `reg_date`)
                                   VALUES ('$login', '".md5("$password")."', '".time()."')");
      $mysqli->close();
      echo '<script language="javascript">';
      echo 'alert("Registered successfully!")';
      echo '</script>';
      return true;
  }

  function secured_string($password) {
    return md5($password);
  }

  if(array_key_exists("login_bt", $_POST)) {
    authorize_user($_POST["username"], $_POST["password"]);
  }
  if(array_key_exists("logon_bt", $_POST)) {
    register_user($_POST["username"], $_POST["password"]);
  }
?>


<!DOCTYPE html>
 <head lang = "en">
	<title>Login page</title>
	<link rel="stylesheet" href="css/login_styles.css">
  <script src="js/login.js"></script>
 </head>
 <body>

	<section>
		<img src="images/space_background.jpg" id = "space_bg">
		<img src="images/moon.png" id = "moon">
		<img src="images/mountain.png" id = "mountain">
		<img src="images/field.png" id = "field">
		<h1 id="text"> Welcome to my space </h1>
	</section>
	<script type="text/javascript">
	let space_bg = document.getElementById("space_bg");
	let moon = document.getElementById("moon");
	let mountain = document.getElementById("mountain");
	let field = document.getElementById("field");
	let text = document.getElementById("text");

	window.addEventListener('scroll', function() {
		var value = window.scrollY;

		space_bg.style.top = value * 0.5 + 'px';
		moon.style.left = - value * 0.5 + 'px';
		mountain.style.top = - value * 0.2 + 'px';
		field.style.top = value * 0.2 + 'px';
		text.style.top = value + 'px';
	})
	</script>
	<div class="form">
		<form id="login_form" method="post">
			<h2>Login</h2>
			<input type="text" name="username" id="username" placeholder="Username" required >
			<input type="password" name="password" id="password"  placeholder="Password" required >
			<button name="login_bt" type="submit" id="submit">Login</button>
      <button name="logon_bt" type="submit" id="submit">Logon</button>
      <a href="main_page.html">&#128640;</a>
		</form>
	</div>
 </body>
