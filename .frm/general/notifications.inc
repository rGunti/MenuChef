<?php
$notifications = Session::getAllNotifications();
//echo "<pre>" . print_r($notifications, true) . "</pre>";
if (count($notifications) >= 1) {
    echo "<div class='container notification-container'><!--<h2>Notifications</h2>-->";
    foreach (Session::getAllNotifications() as $notification) {
        $notification->render();
    }
    echo "</div>";
    ?>
    <script>
        $(".alert button.close").click(function(e) {
            console.log(e);
            $(this).parent().fadeOut('slow', function() {
                $(this).remove();
            });
        });
    </script>
<?php
    SessionNotification::handleNotificationsAfterRender();
}
