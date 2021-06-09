
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
		<div class="right-sidebar">
			 <ul>
<?php
if (isset($_COOKIE['logged_in']))
	$profile="action.php";
else
	$profile="login.php";
echo			  "<li><a href=\"".$profile."\">Profile</a></li>" ;

?>
			  <li><a href="test_db.php">TestDB</a></li>
			</ul>
		</div>
		<div class="content">
			Какой-то текст, много текста, какой-то текст, много текста,<br>
			Какой-то текст, много текста, какой-то текст, много текста,<br>
			Какой-то текст, много текста, какой-то текст, много текста,<br>
		</div>
			<div class="clear"></div>
		<div class="footer">Footer</div>
	</div>
 
</body>
</html>
