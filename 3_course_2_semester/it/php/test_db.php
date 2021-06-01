<html> <head>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
		<meta http-equiv="Content-Language" content="ru">
		<title>Первая программа</title>
	</head><body>
<?php
$host="127.0.0.1";
$user="user";
$pass="user";
#try {
#	  $dbh = new PDO('mysql:host='.$host.';dbname=lab', $user, $pass);
#} catch (PDOException $e) {
#	  print "Error!: " . $e->getMessage();
#	    #die();
#}
#mysqli_report(MYSQLI_REPORT_INDEX);
#$conn = new mysqli($host, $user, $pass);
$link=mysqli_connect($host, $user, $pass);
echo "  Хост  ". $host."; Пользователь  ".$user." ; Пароль ".$pass."<br>";
echo mysqli_connect_errno()."<br>";
if (!mysqli_connect_errno()) {
echo " Подключение к БД успешно";  }
else {
echo "Не удалось установить подключение к базе данных!";
}   

?>
</body> </html>
