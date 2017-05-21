<?php
        $servername = "localhost";
        $username = "root";
        $password = "";

        // Create connection
        $conn = new mysqli($servername, $username, $password);
        if ($conn->connect_error) {
                die("Connection failed: " . $conn->connect_error);
        }
        mysqli_select_db($conn, "alexa");
        $result = $conn->query("SELECT * FROM violations");
        $arr = array();
        if ($result->num_rows > 0) {
                // output data of each row
                while($row = $result->fetch_assoc()) {
                        array_push($arr, array($row["type"], $row["timestamp"], $row["distance"]));
                }
        }
        echo(json_encode($arr));
?>
