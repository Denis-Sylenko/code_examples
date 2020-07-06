
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
 <button name="all">Всі планети</button>
 <button name="astronauts">На які ступали люди</button>
 <button name="by_distance">Сортувати за віддаленістю</button>
 <button name="by_period">Сортувати за періодом</button>
 <button name="satellites">Супутників більше, ніж: </button>
 <input name="sat" type="text" >
</form>
 </body>


 <?php
 $mysqli = new mysqli ("localhost", "root", "", "space_bd");
 $mysqli->query ("SET NAMES 'utf-8'");
   function printResult($result_set) {
     $i = 1;
     while(($row = $result_set->fetch_assoc())!= false) {

     //echo ('
     //<h1 align="middle">' . $i .'. '.  $row["name"] . '</h1>
     //<img width="50%" height="90%" src=' . $row["image"] . '>
     //<h3> Кількість супутників: ' .  $row["satellites"] . '</h3>
     //<h3> Відстань до сонця : ' .  $row["distance"] . ' km</h3>
     //<h3> Маса планети: ' .  $row["weight"] . '</h3>
    // <h3> Період обертання навколо сонця: ' .  $row["time"] . ' доби</h3>
    // '
    // );

     echo ('
     <table border = "1px">
      <tr>
      <td><h1 align="middle">' . $i .'. '.  $row["name"] . '</h1></td>
      <td><img width="100vw" height="100vh" src=' . $row["image"] . '></td>
      <td><h3> Кількість супутників: ' .  $row["satellites"] . '</h3></td>
      <td> <h3> Відстань до сонця : ' .  $row["distance"] . ' km</h3></td>
      <td> <h3> Маса планети: ' .  $row["weight"] . '</h3> </td>
      <td> <h3> Період обертання навколо сонця: ' .  $row["time"] . ' доби</h3></td>
      </tr>
     </table>'
     );
     $i++;
     }
   }

   if(array_key_exists("all", $_POST)) {
     $result_set = $mysqli->query("SELECT * FROM `planets`");
     printResult($result_set);
   }
   if(array_key_exists("astronauts", $_POST)) {
     $result_set = $mysqli->query("SELECT DISTINCT planets.name, planets.image, planets.satellites, planets.distance, planets.weight, planets.time
                                   FROM `astronauts`
                                   INNER JOIN `planets` ON planets.id = astronauts.planet_id ");
     printResult($result_set);
   }
   if(array_key_exists("by_distance", $_POST)) {
     $result_set = $mysqli->query("SELECT * FROM `planets` ORDER BY `distance` DESC");
     printResult($result_set);
   }
   if(array_key_exists("by_period", $_POST)) {
     $result_set = $mysqli->query("SELECT * FROM `planets` ORDER BY `time` ASC");
     printResult($result_set);
   }
   if(array_key_exists("satellites", $_POST)) {
     $count=$_POST["sat"];
     if(strlen($count) == 0) {
       $count=-1;
     }
     $result_set = $mysqli->query("SELECT * FROM `planets` WHERE `satellites` > $count");
     printResult($result_set);
   }
    $mysqli->close();
 ?>
