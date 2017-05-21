<?php
        $servername = "localhost";
        $username = "root";
        $password = "";

        // Create connection
        $conn = new mysqli($servername, $username, $password);
        if ($conn->connect_error) {
                die("Connection failed: " . $conn->connect_error);
        }
        print("Hello");
        mysqli_select_db($conn, "alexa");
        $sqlt = "INSERT INTO violations (type, timestamp, distance) VALUES ('speeding car'," . date_timestamp_get(date_create()) . "," . $_GET['x'] . ")";
        if ($conn->query($sqlt) == false) {
        }
?>
