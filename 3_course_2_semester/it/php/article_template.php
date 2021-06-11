<?php
$title = $_GET["title"];
$link=mysqli_connect("127.0.0.1", "user", "user", "lab");
$articles = mysqli_query($link, "select content from articles where title = '$title'");
$row = mysqli_fetch_row($articles);

?>
<!DOCKTYPE html>
<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
	<title>Article</title>
	<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
 
	<div class="wrapper">
	<div class="header"><?php echo $title; ?></div>
		<div class="right-sidebar">
			 <ul>
			  <li><a href="index.php">Return to main</a></li>
			</ul>
		</div>
		<div class="content">
			<?php
echo $row[0];
?>
		</div>
			<div class="clear"></div>
		<div class="footer">Footer</div>
	</div>
 
</body>
</html>
