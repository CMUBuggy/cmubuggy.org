<?php

//echo json_encode(array("loginId"=>$_GET['userId']));
include "functions.php";

echo json_encode(array("registered"=>registerConfirm($_GET['randomNum'])));

?>