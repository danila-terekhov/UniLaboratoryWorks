<?php
echo 1;

$title = NULL;
$article = NULL;
if(isset($_POST["title"])){
    $title = $_POST["title"];
}
if(isset($_POST["article"])){
    $article = $_POST["article"];
}

$query = "insert into articles(title, content, date, price) values ('$title', '$article', now(), 0)";

$link=mysqli_connect("127.0.0.1", "user", "user", "lab");
$articles = mysqli_query($link, $query);
header("location: /index.php");
?>
