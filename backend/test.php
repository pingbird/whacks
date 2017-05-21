<?php require __DIR__ . '/vendor/autoload.php';
        error_log(file_get_contents('php://input'));
        $jsonDataAsArray = json_decode(file_get_contents('php://input'), true); // T
        //var_dump($jsonDataAsArray);
        $servername = "localhost";
        $username = "root";
        $password = "";

        // Create connection
        $conn = new mysqli($servername, $username, $password);
        if ($conn->connect_error) {
                die("Connection failed: " . $conn->connect_error);
        }
        mysqli_select_db($conn, "alexa");
        $alexaRequest = \Alexa\Request\Request::fromData($jsonDataAsArray);
        $response = new \Alexa\Response\Response;
        if ($alexaRequest instanceof \Alexa\Request\IntentRequest) {
                if ($alexaRequest->intentName == "ReportIntent") {
                        $sqlt = "INSERT INTO violations (type, timestamp) VALUES ('" . $alexaRequest->slots["violation"] . "'," . date_timestamp_get(date_create()) . ")";
                        if ($conn->query($sqlt) == false) {
                                $response->respond(mysqli_error($conn));
                        } else {
                                $response->respond($alexaRequest->slots["violation"] . " reported");
                        }
                } else if ($alexaRequest->intentName == "StatusIntent") {
                        if (isset($alexaRequest->slots["violation"]) && ($result = mysqli_query($conn, "SELECT COUNT(type) FROM violations WHERE type = '" . ($alexaRequest->slots["violation"]) . "'"))) {
                                $arr = $result->fetch_array();
                                $response->respond($arr[0] . " " . $alexaRequest->slots["violation"] . " Violations in the past 24 hours");
                                $result->close();
                        } else if ($result = mysqli_query($conn, "SELECT COUNT(type) FROM violations WHERE timestamp > " . (date_timestamp_get(date_create()) - 86400))) {
                                $arr = $result->fetch_array();
                                $response->respond($arr[0] . " Violations in the past 24 hours");
                                $result->close();
                        } else {
                                $response->respond(mysqli_error($conn));
                        }
                } else {
                        $response->respond($alexaRequest->intentName);
                }
        } else if ($alexaRequest instanceof \Alexa\Request\SessionEndedRequest) {

        }
        mysqli_close($conn);
        header('Content-Type: application/json');
                                                                                                                                                                                                                                    echo json_encode($response->render());
        exit;
?>
