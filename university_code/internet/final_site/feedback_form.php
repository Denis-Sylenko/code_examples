<?php
  session_start();
  $_SESSION["from"] = "Від кого:";
  $_SESSION["subject"] = "Тема:";
  $_SESSION["message"] = "Повідомлення:";

  $error_from = "";
  $error_subject = "";
  $error_message = "";
  $error = false;

  if(isset($_POST["send"])) {
    $from = htmlspecialchars($_POST["from"]);
    $to = "spaceadmin@gmail.com";
    $subject = htmlspecialchars($_POST["subject"]);
    $message = htmlspecialchars($_POST["message"]);
    $_SESSION["from"] = $from;
    $_SESSION["to"] = $to;
    $_SESSION["subject"] = $subject;
    $_SESSION["message"] = $message;

    if(strlen($from) == 0 || strpos ($from, "@") === False) {
      $error_from="Введіть коректний email";
      $error = true;
    }
    if(strlen($subject) == 0) {
      $error_subject="Введіть тему";
      $error = true;
    }
    if(strlen($message) == 0) {
      $error_message="Введіть повідомлення";
      $error = true;
    }
    if(!$error) {
      $headers = "From: $from\r\nReply-to: $from\r\nContent-type:text/plain; charset=utf-8\r\n";
      mail($to, $subject, trim($message), $headers);
      header("Location: main_page.html");
      exit;
    }
  }
?>

<!DOCTYPE html>
<head>
    <title>Зворотній зв'язок</title>
    <link rel="stylesheet" href="css/login_styles.css">
   	<link rel="stylesheet" href="css/styles.css">
</head>
<body>
  <ul class="menu">
  <li><input type="button" value="&#128072;" onClick="back_to_history()"></li>
  <li><a href="main_page.html">&#128640; Home</a></li>
  <li><a href="gallery.html">&#127912; Gallery</a></li>
  <li><a href="book/page_1.html">&#128218; Book</a></li>
  <li><a href="game.html">&#127918; Game</a></li>
  <li><a href="feedback_form.php">&#x1f4e7; Feedback</a></li>
  <li><a href="planets.php">&#127757; Planets</a></li>
  <li><a href="astronauts.php">👨‍🚀 Astronauts</a></li>
  </ul>
<div class="form">
<h2>Форма зворотнього зв'язку</h2>
<form name="feedback_form" action="" method="post">
<input type="text" name="from" placeholder="Від кого:" value="<?=$_SESSION["from"]?>"/>
<span style="color:red"><?=$error_from?></span><br>
<input type="text" name="subject" placeholder="Тема:" value="<?=$_SESSION["subject"]?>" />
<span style="color:red"><?=$error_subject?></span><br>
<textarea name="message" cols="40" rows="10"><?=$_SESSION["message"]?></textarea>
<span style="color:red"><?=$error_message?></span><br>
<button type="submit" name="send">Відправити</button>
</form>
</div>
</body>
</html>
