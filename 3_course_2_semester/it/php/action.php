<!DOCKTYPE html>
<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
	<title>Main page</title>
	<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
	<div class="wrapper">
	<div class="header">Header</div>
	<div class="content">
<?php
$email = NULL;
$password = NULL;
if(isset($_POST["email"])){
    $email = $_POST["email"];
}
if(isset($_POST["password"])){
    $password = $_POST["password"];
}

$link=mysqli_connect("127.0.0.1", "user", "user", "lab");
$pass = md5($pass);

setcookie("logged_in", 1);
if (!mysqli_connect_errno()) {
#	echo " Подключение к БД успешно<br>";
	$res = mysqli_query($link, "select password from users where mail = '$email'");
	if ($res->num_rows != 1)
		echo "Нет такого пользователя!<br>";
		#return false;
	else {
		$row = mysqli_fetch_row($res);
		$real_pass = $row[0];
		echo $real_pass."<br>";
		echo $pass."<br>";
		if ($pass === $real_pass) {
			echo "You are logged in!<br>";
		} else
			echo "Wrong password!<br>";
	}
} else {
	echo " не могу подключиться к бд";
}

?>
</div>
		<div class="right-sidebar">
			 <ul>
			  <li><a href="index.php">Main</a></li>
		          <li><a href="add_article.php">Add article</a></li>
			</ul>
		</div>
<div class="clear"></div>
<div class="footer">Footer</div>
</body>
</html>
