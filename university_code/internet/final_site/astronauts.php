
<!DOCTYPE html>
 <head lang = ru >
	<link rel="stylesheet" href="css/styles.css">
  <script src="js/history.js"></script>
	<title>Main page</title>
	<meta charset = "utf-8">
	<meta name="Keywords" content="Space, Rocket, Stars, NASA">
	<meta name="description" content="Site for my university project (1st lab). Denis Sylenko, student of DNU">
 </head>
 <body class="book">
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
 <form align="center" method="post">
 <button name="all">Всі атронавти</button>
 <button name="planets">Ті, що були на інших планетах</button>
 <button name="year">Сортувати за роком вильоту</button>
 <button name="surname">За фамілією</button>
 <input name="sur" type="text" >
 <button name="Ukraine">З України </button>
 <button name="USA">З Америки </button>
 <button name="USSR">З СРСР </button>
</form>
 </body>


 <?php
 $mysqli = new mysqli ("localhost", "root", "", "space_bd");
 $mysqli->query ("SET NAMES 'utf-8'");
   function printResult($result_set) {
     $i = 1;
     while(($row = $result_set->fetch_assoc())!= false) {
     echo ('
     <h1 align="middle">' . $i .'. '.  $row["name"] . '</h1>
     <img width="50%" height="90%" src=' . $row["image"] . '>
     <h3> Рік подорожі: ' .  $row["year"] . '</h3>
     <h3> Країна : ' .  $row["country"] . '</h3>
     '
     );
     $i++;
     }
   }

   if(array_key_exists("all", $_POST)) {
     $result_set = $mysqli->query("SELECT * FROM `astronauts`");
     printResult($result_set);
   }
   if(array_key_exists("planets", $_POST)) {
     $result_set = $mysqli->query("SELECT *
                                   FROM `planets`
                                   INNER JOIN `astronauts` ON planets.id = astronauts.planet_id ");
     printResult($result_set);
   }
   if(array_key_exists("year", $_POST)) {
     $result_set = $mysqli->query("SELECT * FROM `astronauts` ORDER BY `year` ASC");
     printResult($result_set);
   }
   if(array_key_exists("Ukraine", $_POST)) {
     $result_set = $mysqli->query("SELECT * FROM `astronauts` WHERE `country`='Ukraine'");
     printResult($result_set);
   }
   if(array_key_exists("USA", $_POST)) {
     $result_set = $mysqli->query("SELECT * FROM `astronauts` WHERE `country`='USA'");
     printResult($result_set);
   }
   if(array_key_exists("USSR", $_POST)) {
     $result_set = $mysqli->query("SELECT * FROM `astronauts` WHERE `country`='USSR'");
     printResult($result_set);
   }
   if(array_key_exists("surname", $_POST)) {
     $surname='%' . $_POST["sur"] . '%';
     $result_set = $mysqli->query("SELECT * FROM `astronauts` WHERE `name` LIKE '$surname'");
     printResult($result_set);
   }
    $mysqli->close();
 ?>
